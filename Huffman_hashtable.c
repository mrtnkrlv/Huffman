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
    linkedList* cells = malloc(sizeof(linkedList)*capacity);
    linkedList base = {.head = NULL};
    for (int i = 0; i < capacity; ++i){
        cells[i] = base; 
    }
    hashTable rep = {.cells = cells, .capacity = capacity};
    return rep;
}

//need function to test if a key isn't already in hashtable 

//hashtable insertion
void insertion_hashTable(hashTable h, char* s, int n){
    node ins = {.symbol = s, .weight = n, .succ = NULL};
    insertion_linkedList(&h.cells[hashFunction(s, h.capacity)], ins);
}

/*void insertion_linkedList(linkedList* l, node n){
    node** p = &l->head; //double pointer for hashtable insertion function
    if (*p == NULL){
        *p = &n;
    }
    else{
        while ((*p)->succ != NULL){
            *p = (*p)->succ;
        }
    }
    (*p)->succ = &n;
}*/

//need modify value function

int main(){
    int cap = 100;
    hashTable h = creation_hashTable(cap);

    insertion_hashTable(h,"b",4);
    //insertion_hashTable(h,"a",1);
    insertion_hashTable(h, "c", 2);

    printf("%s\n", h.cells[hashFunction("b",h.capacity)].head->symbol);

    exit(0);
}