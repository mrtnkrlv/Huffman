#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
linkedList create_linkedList(){
    linkedList rep = {.head = NULL};
    return rep;
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
void insert_linkedList(linkedList l, node n){
    node* p = l.head;
    if (p == NULL){
        p = &n;
    }
    while (p->succ != NULL){
        p = p->succ;
    }
    p->succ = &n; 
}

//traverse linked list and print elements
void print_linkedList(linkedList l){
    node* p = l.head;
    while (p != NULL){
        printf("%s ", p->symbol);
        p = p->succ;
    }
}

/*int main(){
 

    //exit for now so that I don't have to worry about freeing
    exit(0);
}*/
