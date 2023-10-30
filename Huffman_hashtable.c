#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "Huffman_linked_list.c"

//hashtable 
struct hashTable{
    linkedList* cells;
    int capacity;
};
typedef struct hashTable hashTable;

//hash function 
//(good enough)
int hashFunction(char* s, int capacity){
    size_t val = s[0];
    for (size_t i = 0; i < strlen(s); ++i){
        val = (24593*val*val+s[i] + 49157) % 6151;
    }
    return (int) val%capacity;
}

//hashtable creation
hashTable creation_hashTable(int capacity){
    linkedList* cells = malloc(sizeof(linkedList)*capacity);
    linkedList base = {.head = NULL};
    for (int i = 0; i < capacity; ++i){
        cells[i] = base; 
    }
    hashTable temp = {.cells = cells, .capacity = capacity};
    hashTable* ans = malloc(sizeof(hashTable));
    *ans = temp;
    return *ans;
}

//tests if a character is in a hashtable 
bool presence_test_hashTable(hashTable h, char* s){
    node* test = h.cells[hashFunction(s,h.capacity)].head;
    while (test != NULL){
        if (!strcmp(s,test->symbol))
            return true;
        test = test->succ;
    }
    return false;
}

//hashtable insertion
//(inserts 0 as default value, which can be incremented with the next function)
void insertion_hashTable(hashTable* h, char* s){
    assert(!presence_test_hashTable(*h,s));
    node ins =  {.symbol = s, .weight = 0, .succ = NULL};
    insertion_linkedList(&h->cells[hashFunction(s,h->capacity)], ins);
}

//increments value at key s: no need for a value modification function
//because I'll only change values that I don't know about when making heaps
void increment_hashTable(hashTable* h, char* s){
    assert(presence_test_hashTable(*h,s));
    node* mod = h->cells[hashFunction(s,h->capacity)].head;
    while(strcmp(s,mod->symbol))
        mod = mod->succ;
    int* temp = malloc(sizeof(int));
    ++mod->weight;
}

/*int main(){

    //exit for now so that I don't have to worry about freeing
    exit(0);
}*/