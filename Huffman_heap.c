#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

//tree structure (without internal tree)
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

//heap insertion function
void insert_huffmanHeap(huffmanHeap* heap, char* symbol, int weight){
    huffmanHeap* p = malloc(sizeof(huffmanHeap));
    p = heap;
    while (p->heapWeight <= weight && p->heapLeft){
        //printf("heap weight: %i     weight: %i \n", p->heapWeight, weight);
        p = p->heapLeft;
    }
    if (!p->heapLeft){
        huffmanHeap* temp = malloc(sizeof(huffmanHeap));
        temp->heapLeft = NULL;
        temp->heapRight = NULL;
        basicTree t = {.treeSymbol = symbol, .treeWeight = weight, .treeLeft = NULL, .treeRight = NULL};
        temp->heapTree = &t;
        temp->heapSymbol = symbol;
        temp->heapWeight = weight;
        p->heapLeft = temp;
    }
    else{
        int* int_buff1 = malloc(sizeof(int));

        char* char_buff1 = malloc(strlen(p->heapSymbol));
        while (p->heapLeft){
            *int_buff1 = p->heapWeight;
            strcpy(char_buff1, p->heapSymbol);
            p->heapSymbol = symbol;
            p->heapWeight = weight;

            p->heapTree->treeSymbol = symbol; 
            p->heapTree->treeWeight = weight;
            
            p = p->heapLeft;
        }
        int* int_buff2 = malloc(sizeof(int));
        char* char_buff2 = malloc(strlen(p->heapSymbol));

        *int_buff2 = p->heapWeight;
        strcpy(char_buff2, p->heapSymbol);

        p->heapSymbol = char_buff1;
        p->heapWeight = *int_buff1;

        p->heapTree->treeSymbol = char_buff1; 
        p->heapTree->treeWeight = *int_buff1;

        basicTree t = {.treeSymbol = char_buff2, .treeWeight = *int_buff2, .treeLeft = NULL, .treeRight = NULL};
        huffmanHeap* new = malloc(sizeof(heap));
        new->heapSymbol = char_buff2;
        new->heapWeight = *int_buff2;
        new->heapTree = &t;
        new->heapLeft = NULL;
        new->heapRight = NULL;

        p->heapLeft = new;
    }
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Need balancing functions for heaps (right rotations)
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


int main(){
    /*basicTree t3 = {.treeSymbol = "c", .treeWeight = 4, .treeLeft = NULL, .treeRight = NULL};
    basicTree t2 = {.treeSymbol = "b", .treeWeight = 3, .treeLeft = NULL, .treeRight = NULL};
    basicTree t1 = {.treeSymbol = "a", .treeWeight = 1, .treeLeft = NULL, .treeRight = NULL};

    huffmanHeap h3 = {.heapSymbol = "c", .heapWeight = 4, .heapTree = &t3, .heapLeft = NULL, .heapRight = NULL};
    huffmanHeap h2 = {.heapSymbol = "b", .heapWeight = 3, .heapTree = &t2, .heapLeft = &h3, .heapRight = NULL};
    huffmanHeap h1 = {.heapSymbol = "a", .heapWeight = 1, .heapTree = &t1, .heapLeft = &h2, .heapRight = NULL};
        
    insert_huffmanHeap(&h2, "d", 2);

    printf("node 1: %s, %i\n", h1.heapSymbol, h1.heapWeight);
    printf("node 2: %s, %i\n", h1.heapLeft->heapSymbol, h1.heapLeft->heapWeight);
    printf("node 3: %s, %i\n", h1.heapLeft->heapLeft->heapSymbol, h1.heapLeft->heapLeft->heapWeight);
    printf("node 4: %s, %i\n", h1.heapLeft->heapLeft->heapLeft->heapSymbol, h1.heapLeft->heapLeft->heapLeft->heapWeight);*/



    //exit for now so that I don't have to worry about freeing
    exit(0);
}





