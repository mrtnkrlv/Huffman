#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "Huffman_heap.c"

// !!! NOTE TO SELF: the symbol of new nodes in priority queue !!!
// !!! can be concatenation of symbols of children             !!!

//function that returns size (in characters) of text file
//actually returns 1 more than the "visible" file length (in characters)

int fileLength(char* fileName){
    FILE* p = fopen(fileName,"r");
    int acc = 0;
    if (p == NULL){
        printf("File not found\n");
        return -1;
    }
    while(!feof(p)){
        ++acc;
        fgetc(p);
    }
    return acc;
}

//function to read file, store in hashtable, and create initial heap

hashTable readFile(char* fileName){
    FILE* p = fopen(fileName, "r");
    assert(p != NULL); //good enough for now
    hashTable* h = malloc(sizeof(hashTable));
    *h = creation_hashTable(fileLength(fileName));
    char* current = malloc(2);
    current[1] = '\0';
    while (!feof(p)){
        current[0] = (char) fgetc(p);
        printf("%c", current[0]);
        insertion_hashTable(*h, current);
        increment_hashTable(*h, current);
    }
    fclose(p);

    return *h;
}

/*void insertion_hashTable(hashTable h, char* s){
    if (!presence_test_hashTable(h,s)){ //don't raise error for Huffman_main 
    node ins =  {.symbol = s, .weight = 0, .succ = NULL};
    insertion_linkedList(&h.cells[hashFunction(s,h.capacity)], ins);
    }
}*/


/*

//function to create Huffman tree based on heap input

basicTree create_HuffmanTree(huffmanHeap heap){

}

//function to go through Huffman tree and return "compressed" file
//left: read a 1, right: read a 0
FILE* HuffmanCompress(basicTree tree){

}

// NEXT UP: decompression

*/

int main(){
    /*
    hashTable h = readFile("li_def.txt");
    printf("\n");
    for (int i = 0; i < h.capacity; ++i){
        if (h.cells[i].head != NULL)
            printf("%s %i\n", h.cells[i].head->symbol, h.cells[i].head->weight);
    }
    */
    
    /*int acc = 0;
    for (int i = 0; i < h.capacity; ++i) ++acc;
    printf("acc %i\n", acc);*/

    exit(0);
}