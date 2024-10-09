#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void push(stack *s, node *new_node)
{
    add_first(&s->top, new_node);
}

node* pop(stack *s)
{
    return remove_first(&s->top);
}

int empty(stack *s)
{
    return s->top == NULL;
}

void clear_stack(stack *s)
{
    while(s->top != NULL){
        node *n = remove_first(&s -> top);
        if (n != NULL)
            free(n);
    }
}