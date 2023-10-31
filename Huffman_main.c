#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "Huffman_hashtable.c"
//#include "Huffman_heap.c"

// !!! NOTE TO SELF: the symbol of new nodes in priority queue !!!
// !!! can be concatenation of symbols of children             !!!

//function that returns size (in amount of characters) of text file

int fileLength(char* fileName){
    FILE* p = fopen(fileName,"r");
    int acc = 0;
    if (p == NULL){
        printf("File not found\n");
        return -1;
    }
    while (fgetc(p) != EOF){
        if (feof(p)) break;
        ++acc;
    }
    return acc;
}

//function to read file, store in hashtable, and create initial heap

hashTable readFile(char* fileName){
    FILE* p = fopen(fileName, "r");
    assert(p != NULL); 
    hashTable* h = malloc(sizeof(hashTable));
    *h = creation_hashTable(fileLength(fileName));
    int c;
    while ((c = fgetc(p)) != EOF){
        if (feof(p)) break;
        char* current = malloc(2);
        current[0] = c;
        current[1] = 0;
        if (!presence_test_hashTable(*h,current))
            insertion_hashTable(h,current);
        increment_hashTable(h,current);
    }
    fclose(p);

    return *h;
}

/*//function to create Huffman tree based on heap input

basicTree create_HuffmanTree(huffmanHeap heap){

}

//function to go through Huffman tree and return "compressed" file
//left: read a 1, right: read a 0

FILE* HuffmanCompress(basicTree tree){

}*/

// NEXT UP: decompression

int main(){
    /*int sum = 0;
    hashTable h = readFile("li_def.txt");
    for (int i = 0; i < h.capacity; ++i){
        node* p = h.cells[i].head;
        while (p){
            sum+=p->weight;
            printf("%s %i\n", p->symbol, p->weight);
            p = p->succ;
        }
    }
    printf("%i", sum);*/



    exit(0);
}

