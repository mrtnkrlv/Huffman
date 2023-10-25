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

linkedList head_linkedList(linkedList l){
    return l.head
}

int main(){

    return 0;
}