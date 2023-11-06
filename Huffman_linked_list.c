#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

//node of a linked list
struct node{
    char* symbol;
    int weight;
    struct node* succ;
};
typedef struct node node;

//linked list structure
struct linkedList{
    node* head;
};
typedef struct linkedList linkedList;

//linked list creation
linkedList creation_linkedList(){
    linkedList ans = {.head = NULL};
    return ans;
}

//searches for an element in a linked list
bool search_linkedList(linkedList l, char* s){
    node* p = l.head;
    while (p != NULL){
        if (!strcmp(s,p->symbol)) return true;
        p = p->succ;
    }
    return false;
}

//inserts to the back of a linked list
void insertion_linkedList(linkedList *l, node n){                                                                                  
    node *new = malloc(sizeof(node));
    *new = n;
    if (l->head == NULL)
        l->head = new;
    else{                             
        node *current = l->head;                                                  
        while (current->succ)                 
            current = current->succ;                                                                                
        current->succ = new;
    }
}

//traverse linked list and print elements
void print_linkedList(linkedList l){
    node* p = l.head;
    while (p != NULL){
        printf("%s ", p->symbol);
        p = p->succ;
    }
}