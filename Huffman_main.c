#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "Huffman_hashtable.c"
#include "Huffman_heap.c"
#include "Huffman_buffers.c"

//function that returns size (in amount of characters) of text file
int fileLength(char* fileName){
    FILE* p = fopen(fileName,"r");
    int acc = 0;
    if (!p){
        printf("File not found\n");
        return -1;
    }
    while (fgetc(p) != EOF){
        if (feof(p)) break;
        ++acc;
    }
    return acc;
}

//function to read file and create hashtable containing the file's characters
//and their occurences
hashTable readFile(char* fileName){
    FILE* p = fopen(fileName, "r");
    assert(p != NULL); 
    hashTable h = creation_hashTable(fileLength(fileName));
    int c;
    while ((c = fgetc(p)) != EOF){
        if (feof(p)) break;
        char* current = malloc(2);
        current[0] = c;
        current[1] = 0;
        if (!presence_test_hashTable(h,current))
            insertion_hashTable(&h,current);
        increment_hashTable(&h,current);
    }
    fclose(p);
    return h;
}

//function to create Huffman heap based on a hashtable input
huffmanHeap heapMake(char* fileName){
    hashTable h = readFile(fileName);
    huffmanHeap* heap = malloc(sizeof(huffmanHeap));
    bool tag = false;
    for (int i = 0; i < h.capacity; ++i){
        node* p = h.cells[i].head;
        while(p){
            if (!tag){
                *heap = create_huffmanHeap(p->symbol, p->weight);
                tag = true;
            }
            else insert_huffmanHeap(heap, p->symbol, p->weight);
            p = p->succ;
        }
    }
    return *heap;
}

//function to create Huffman tree based on heap input
basicTree huffmanTreeMake(char* fileName){
    huffmanHeap h = heapMake(fileName);
    while (h.heapLeft){
        if(!h.heapLeft->heapLeft){
            huffmanHeap temp = *h.heapLeft;
            char* charNew = malloc(strlen(h.heapSymbol)+strlen(temp.heapSymbol)+1);
            strcat(charNew, h.heapSymbol);
            strcat(charNew, temp.heapSymbol);
            charNew[strlen(h.heapSymbol)+strlen(temp.heapSymbol)] = 0;
            basicTree t = {
                .treeSymbol = charNew,
                .treeWeight = h.heapWeight + temp.heapWeight,
                .treeLeft = h.heapTree,
                .treeRight = temp.heapTree
            };
            return t;
        }
        basicTree* leftChild = malloc(sizeof(basicTree));
        basicTree* rightChild = malloc(sizeof(basicTree));
        basicTree* new = malloc(sizeof(basicTree));

        *leftChild = extract_huffmanHeap(&h);
        *rightChild = extract_huffmanHeap(&h);

        char* charNew = malloc(strlen(leftChild->treeSymbol)+strlen(rightChild->treeSymbol)+1); //+1? 
        strcat(charNew, leftChild->treeSymbol);
        strcat(charNew, rightChild->treeSymbol);
        charNew[strlen(leftChild->treeSymbol)+strlen(rightChild->treeSymbol)] = 0;

        basicTree t = {
            .treeSymbol = charNew,
            .treeWeight = leftChild->treeWeight + rightChild->treeWeight,
            .treeLeft = leftChild,
            .treeRight = rightChild
        };
        *new = t;
        insert_tree_huffmanHeap(&h, *new);
    }
    return *h.heapTree; //never comes up
}

//function to test whether a char array is in a basic tree
bool search_char_tree(basicTree t, char* c){
    bool acc = !strcmp(t.treeSymbol, c);
    if (t.treeLeft) acc = acc || search_char_tree(*t.treeLeft, c);
    if (t.treeRight) acc = acc || search_char_tree(*t.treeRight, c);
    return acc;
}

//depth-first search to get code
void charCode_traverse(basicTree huffmanTree, char* c, int* rep){
    if (huffmanTree.treeLeft && search_char_tree(*huffmanTree.treeLeft,c)){
        *rep*=10;
        charCode_traverse(*huffmanTree.treeLeft,c,rep);
    }
    if (huffmanTree.treeRight && search_char_tree(*huffmanTree.treeRight,c)){
        *rep = *rep*10+1;
        charCode_traverse(*huffmanTree.treeRight,c,rep);
    }
}

//function to return code (as an int) corresponding to a character for compression
// !!! adds an extra 2 in front !!!
int charCode(basicTree huffmanTree, char* c){
    assert(search_char_tree(huffmanTree,c));
    int rep = 2;
    charCode_traverse(huffmanTree,c,&rep);
    return rep;
}

//function to return hashtable containing codes for compression
hashTable hashtableCodes(char* fileName){
    basicTree t = huffmanTreeMake(fileName);
    hashTable h = creation_hashTable(fileLength(fileName));
    FILE* p = fopen(fileName, "r");
    char c;
    while ((c = fgetc(p)) != EOF){
        if (feof(p)) break;
        char* ins = malloc(2);
        ins[0] = c;
        ins[1] = 0;
        if (!presence_test_hashTable(h, ins))
            insertion_hashTable(&h, ins);
        modify_hashTable(&h,ins,charCode(t,ins));
    }
    return h;
}

//function to go through Huffman tree and create "compressed" file
void huffmanCompress(char* fileName){
    FILE* out = fopen(fileName, "r");
    FILE* in = fopen("compressed.bin", "wb");
    hashTable h = hashtableCodes(fileName);
    int buffer = 0, fullness = 0;
    char c;
    while ((c = fgetc(out)) != EOF){
        if (feof(out)) break;
        char* temp = malloc(2);
        temp[0] = c;
        temp[1] = 0;
        node* trav = h.cells[hashFunction(temp, h.capacity)].head;
        while (strcmp(trav->symbol, temp))
            trav = trav->succ;
        int intCode = trav->weight;
        char* code = itoa(intCode); 
        write_byte(in, code, &buffer, &fullness);
    }
    if (fullness > 0){
        fputc(buffer, in);
        fullness = 0;
        buffer = 0;
    }
    fclose(out);
    fclose(in);
}

//function to go through compressed Huffman file and return a decompressed version of the file
void huffmanDecompress(char* compressed, char* origin){
    FILE* in = fopen(compressed, "rb");
    FILE* out = fopen("decompressed.txt", "w");
    basicTree* t;
    *t = huffmanTreeMake(origin);
    char* buffer = malloc(2);
    buffer[1] = 0;
    int len = findSize("compressed.bin")*8;
    char* ans = malloc(len+1);
    ans[len] = 0;
    int acc = 7;
    fread(buffer,1,1,in);
    while (acc < len){
        int temp = acc;
        int trav = 0;
        for (int i = temp - 7; i < temp+1; ++i){
            ans[temp-trav] = (*buffer & 1) + '0';
            *buffer = *buffer >> 1;
            ++trav;
        }
        acc+=8;
        fread(buffer,1,1,in);
    }
    int trav = 0;
    while (trav < len-3){
        while (t->treeLeft || t->treeRight){
            if (ans[trav] == '1')
                t = t->treeRight;
            else
                t = t->treeLeft;
            ++trav;
        }
        fputs(t->treeSymbol, out);
        *t = huffmanTreeMake(origin);
    }
    fclose(in);
    fclose(out);
}

//depth-first traversal of a tree
void dfsPrint(basicTree t){
    printf("%s %i\n", t.treeSymbol, t.treeWeight);
    if (t.treeLeft) dfsPrint(*t.treeLeft);
    if (t.treeRight) dfsPrint(*t.treeRight);
}

int main(){


    exit(0);
}



