#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "Huffman_hashtable.c"
#include "Huffman_heap.c"
#include "Huffman_buffers.c"

// !!! NOTE TO SELF: the symbol of new nodes in priority queue !!!
// !!! can be concatenation of symbols of children             !!!

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
        char* current = malloc(2); //look into whether I should free here or not
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
    //printf("%i\n", acc);
    if (t.treeLeft) acc = acc || search_char_tree(*t.treeLeft, c);
    if(t.treeRight) acc = acc || search_char_tree(*t.treeRight, c);
    return acc;
}

//depth-first search for next function
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
    //iteratively, go through the tree and test if c is in left or right subtree
    //add a 0 when you go left and a 1 when you go right
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
    //go through file char by char and insert (char, char_code) in h
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
        //printf("code %s\n", code);
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

// NEXT UP: decompression

//depth-first traversal of a tree
void dfsPrint(basicTree t){
    printf("%s %i\n", t.treeSymbol, t.treeWeight);
    if (t.treeLeft) dfsPrint(*t.treeLeft);
    if (t.treeRight) dfsPrint(*t.treeRight);
}

int main(){
    /*hashTable h = readFile("li_def.txt");
    int sum = 0;
    for (int i = 0; i < h.capacity; ++i){
        node* trav = h.cells[i].head;
        while (trav){
            sum+=trav->weight;
            printf("%s %i\n", trav->symbol, trav->weight);
            trav = trav->succ;
        }
    }
    printf("sum: %i\n", sum);*/

    //huffmanHeap h = heapMake("def.txt");
    //huffmanHeap* p = &h;

    /*while (p){
        printf("%s %i\n", p->heapTree->treeSymbol, p->heapTree->treeWeight);
        p = p->heapLeft;
    }*/

    //basicTree t = huffmanTreeMake("def.txt");
    //dfsPrint(t);

    //printf("%i\n", charCode(t,"E"));

    /*hashTable h = hashtableCodes("def.txt");
    for (int i = 0; i < h.capacity; ++i){
        node* p = h.cells[i].head;
        while (p){
            printf("%s %i\n", p->symbol, p->weight);
            p = p->succ;
        }
    }*/

    huffmanCompress("def.txt");

    exit(0);
}



