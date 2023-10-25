#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct node{
    char* symbol;
    int weight;
    struct node* succ;
};
typedef struct node node;

struct linkedList{
    node* head;
};
typedef struct linkedList linkedList;

linkedList create_linkedList(){
    linkedList rep = {.head = NULL};
    return rep;
}

void insert_linkedList(linkedList l, node n, char* s){
    node 

}

int main(){

    return 0;
}