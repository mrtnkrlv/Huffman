#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Huffman_linked_list.c"

//hashtable 
struct hashTable{
    linkedList* cells;
    int capacity;
};
typedef struct hashTable hashTable;

//hash function
//good enough for now
int hashFunction(char* s, int capacity){
    size_t rep = s[0];
    for (size_t i = 0; i < strlen(s); ++i){
        rep = (24593*rep*rep+s[i] + 49157) % 6151;
    }
    return (int) rep%capacity;
}

//hashtable creation
hashTable creation_hashTable(int capacity){
    hashTable rep = {.cells = NULL, .capacity = capacity};
    return rep;
}

//hashtable insertion
void insertion_hashTable(hashTable h, char* s, int n){
    node ins = {.symbol = s, .weight = 0, .succ = NULL};
    insert_linkedList(h.cells[hashFunction(s, h.capacity)], ins);
}

int main(){

    exit(0);
}