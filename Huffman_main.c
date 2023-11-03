#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "Huffman_hashtable.c"
#include "Huffman_heap.c"

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


//function to go through Huffman tree and return "compressed" file
//left: read a 0, right: read a 1

/*FILE* HuffmanCompress(basicTree tree){

}*/

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

    exit(0);
}



