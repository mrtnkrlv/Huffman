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
    basicTree t = {.treeSymbol = symbol, .treeWeight = weight, .treeLeft = NULL, .treeRight = NULL};
    *pTree = t;
    huffmanHeap ans = {.heapSymbol = symbol, .heapWeight = weight, .heapTree = pTree, .heapLeft = NULL, .heapRight = NULL};
    return ans;
}

//heap insertion function
void insert_huffmanHeap(huffmanHeap* h, char* symbol, int weight){
    assert(h);
    huffmanHeap* p = h;
    while(p->heapWeight <= weight && p->heapLeft)
        p = p->heapLeft;
    if (!p->heapLeft){
        basicTree* pTree = malloc(sizeof(basicTree));
        basicTree t = {
            .treeSymbol = symbol,
            .treeWeight = weight,
            .treeLeft = NULL,
            .treeRight = NULL
        };
        *pTree = t;
        huffmanHeap* ins = malloc(sizeof(huffmanHeap));
        huffmanHeap temp = {
            .heapSymbol = symbol,
            .heapWeight = weight,
            .heapTree = pTree,
            .heapLeft = NULL,
            .heapRight = NULL
        };
        *ins = temp;
        p->heapLeft = ins;
    }
    else{
        //play around with pointers here if segfault in Huffman_main
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
            //exchange
            temp_int1 = temp_int2;
            temp_char1 = temp_char2;

            p = p->heapLeft;
        }
        //play around with malloc-ing the temp_chars if segfault in Huffman_main
        temp_int2 = p->heapWeight;
        temp_char2 = p->heapSymbol;
        p->heapWeight = temp_int1;
        p->heapSymbol = temp_char1;
        temp_int1 = temp_int2;
        temp_char1 = temp_char2;

        basicTree t = {
            .treeSymbol = temp_char1,
            .treeWeight = temp_int1,
            .treeLeft = NULL,
            .treeRight = NULL
        };
        huffmanHeap* ins = malloc(sizeof(huffmanHeap));
        huffmanHeap temp = {
            .heapSymbol = temp_char1,
            .heapWeight = temp_int1,
            .heapTree = &t,
            .heapLeft = NULL,
            .heapRight = NULL
        };
        *ins = temp;
        p->heapLeft = ins;
    }
}

//heap extraction function (finish)
/*huffmanHeap* extract_huffmanHeap(huffmanHeap h){
    assert(&h);
}*/

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Need balancing functions for heaps (right rotations)
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


int main(){
    huffmanHeap h = create_huffmanHeap("a", 1);
    insert_huffmanHeap(&h, "c", 2);
    /*insert_huffmanHeap(&h, "d", 4);
    insert_huffmanHeap(&h, "f", 5);
    insert_huffmanHeap(&h, "e", 3);
    insert_huffmanHeap(&h, "g", 0);*/

    huffmanHeap* p = &h;
    while (p){
        printf("%s %i\n", h.heapSymbol, h.heapWeight);
        p = p->heapLeft;
    }
    
    //exit for now so that I don't have to worry about freeing
    exit(0);
}