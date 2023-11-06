#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

//binary tree structure (without internal tree)
struct basicTree{
    char* treeSymbol;
    int treeWeight;
    struct basicTree* treeLeft;
    struct basicTree* treeRight;
};
typedef struct basicTree basicTree;

//element of the priority queue (with internal tree)
struct huffmanHeap{
    char* heapSymbol;
    int heapWeight;
    struct basicTree* heapTree;
    struct huffmanHeap* heapLeft;
    struct huffmanHeap* heapRight;
};
typedef struct huffmanHeap huffmanHeap;

//for insertion into an empty heap
huffmanHeap create_huffmanHeap(char* symbol, int weight){
    basicTree* pt = malloc(sizeof(basicTree));
    basicTree t = {.treeSymbol = symbol, .treeWeight = weight, .treeLeft = NULL, .treeRight = NULL};
    *pt = t;
    huffmanHeap ans = {.heapSymbol = symbol, .heapWeight = weight, .heapTree = pt, .heapLeft = NULL, .heapRight = NULL};
    return ans;
}

//heap insertion function
void insert_huffmanHeap(huffmanHeap* h, char* symbol, int weight){
    assert(h);
    huffmanHeap* p = h;
    while(p->heapWeight <= weight && p->heapLeft)
        p = p->heapLeft;
    if (!p->heapLeft){
        if (weight >= p->heapWeight){
            basicTree* pt = malloc(sizeof(basicTree));
            basicTree t = {
                .treeSymbol = symbol,
                .treeWeight = weight,
                .treeLeft = NULL,
                .treeRight = NULL
            };
            *pt = t;
            huffmanHeap* ins = malloc(sizeof(huffmanHeap));
            huffmanHeap temp = {
                .heapSymbol = symbol,
                .heapWeight = weight,
                .heapTree = pt,
                .heapLeft = NULL,
                .heapRight = NULL
            };
            *ins = temp;
            p->heapLeft = ins;
        }
        else{
            int temp_int = p->heapWeight;
            char* temp_char = p->heapSymbol;

            p->heapWeight = weight;
            p->heapSymbol = symbol;

            p->heapTree->treeWeight = weight;
            p->heapTree->treeSymbol = symbol;

            basicTree* pt = malloc(sizeof(basicTree));
            basicTree t = {
                .treeSymbol = temp_char,
                .treeWeight = temp_int,
                .treeLeft = NULL,
                .treeRight = NULL
            };
            *pt = t;
            huffmanHeap* ins = malloc(sizeof(huffmanHeap));
            huffmanHeap temp = {
                .heapSymbol = temp_char,
                .heapWeight = temp_int,
                .heapTree = pt,
                .heapLeft = NULL,
                .heapRight = NULL
            };
            *ins = temp;
            p->heapLeft = ins;
        }
    }
    else{
        int temp_int1 = weight, temp_int2;
        char* temp_char1 = symbol;
        char* temp_char2;
        while(p->heapLeft){
            //save 
            temp_int2 = p->heapWeight;
            temp_char2 = p->heapSymbol;
            //change
            p->heapWeight = temp_int1;
            p->heapSymbol = temp_char1;
            //change tree
            p->heapTree->treeWeight = temp_int1;
            p->heapTree->treeSymbol = temp_char1;
            //exchange
            temp_int1 = temp_int2;
            temp_char1 = temp_char2;

            p = p->heapLeft;
        }
        temp_int2 = p->heapWeight;
        temp_char2 = p->heapSymbol;
        
        p->heapWeight = temp_int1;
        p->heapSymbol = temp_char1;

        p->heapTree->treeWeight = temp_int1;
        p->heapTree->treeSymbol = temp_char1;

        temp_int1 = temp_int2;
        temp_char1 = temp_char2;

        basicTree* pt = malloc(sizeof(basicTree));
        basicTree t = {
            .treeSymbol = temp_char1,
            .treeWeight = temp_int1,
            .treeLeft = NULL,
            .treeRight = NULL
        };
        *pt = t;
        huffmanHeap* ins = malloc(sizeof(huffmanHeap));
        huffmanHeap temp = {
            .heapSymbol = temp_char1,
            .heapWeight = temp_int1,
            .heapTree = pt,
            .heapLeft = NULL,
            .heapRight = NULL
        };
        *ins = temp;
        p->heapLeft = ins;
    }
}

//heap tree insertion function 
void insert_tree_huffmanHeap(huffmanHeap* h, basicTree t){
    insert_huffmanHeap(h, t.treeSymbol, t.treeWeight);
    huffmanHeap* p = h;
    while (true){
        if (!strcmp(p->heapSymbol, t.treeSymbol)){
            *p->heapTree = t;
            return;
        }
        p = p->heapLeft;
    }
}

//heap extraction function: returns a tree for easier
//Huffman tree creation in Huffmain_main
basicTree extract_huffmanHeap(huffmanHeap* h){
    assert(&h);
    basicTree t = *h->heapTree;
    *h = *h->heapLeft; //OK for now
    return t;
}