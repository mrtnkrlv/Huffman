#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct huffmanHeap{
    char symbol;
    int weight;
    struct huffmanHeap* left_child;
    struct huffmanHeap* right_child;
};
typedef struct huffmanHeap biheap;

//when inserting I care about symbol and weight (?)
//when exracting I don't care about symbol (?)

biheap fileFrequency(char* fileName){
    FILE* fp = fopen(fileName, "r");
    

}

biheap heapInsertion(biheap heap, )

int main(){
    

    return 0;
}





