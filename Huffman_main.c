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
        printf("c %c\n", c);
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



/*//function to create Huffman tree based on heap input

basicTree create_HuffmanTree(huffmanHeap heap){

}

//function to go through Huffman tree and return "compressed" file
//left: read a 1, right: read a 0

FILE* HuffmanCompress(basicTree tree){

}*/

// NEXT UP: decompression

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


    exit(0);
}

