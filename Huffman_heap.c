#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "Huffman_hashtable.c"

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



/*int main(){
    

    //exit for now so that I don't have to worry about freeing
    exit(0);
}*/





