#include <stdio.h> 

typedef struct node_tag{
    int v; // data
    struct node_tag * next; // a pointer to this type of struct
} node; // define a type, easier to use

node * head; // head is a pointer not a node
head = NULL; //at beginning, it's emptt

node * new_node(int v){ //create a node for value v
    node *p = malloc(sizeof(node)); //allocate memory
    assert(p != NULL); //you can be nicer

    //Set the value in the node
    p->v = v; // you could do (*p).v
    p->next = NULL;
    return p;
}

//prepend means adding something in the beginning
node * prepend(node * head, node * newnode){
    newnode->next = head; //works even if the list is empty
    return newnode; //head changed!!
}

node * find_last(node * head){
    if(head != NULL){ //only if list is not empty
        while(head->next != NULL){
            head = head->next;
        }
    }
    return head;
}

node * append(node * head, node * newnode){
    node *last = find_last(head); //finde the last one
    if(last == NULL){
        return newnode;
    }
    last->next = newnode;
    newnode->next =NULL;
    return head;//return the unchaged head
}