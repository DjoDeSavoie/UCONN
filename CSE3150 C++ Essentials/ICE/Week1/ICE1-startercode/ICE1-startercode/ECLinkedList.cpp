#include "ECLinkedList.h"
#include <stdio.h>
#include <stdlib.h>

/* get the length of the linked list: how many nodes in the linked list */
/* pHead: head node pointer to the linked list */
/* return the number of nodes of the linked list pointed by pHead */
int ECGetLinkedListLength(struct ECLinkedListNode *pHead)
{
  /* your code here */
  if (pHead == NULL) //if empty list
  {
    return 0;
  }

  return 1 + ECGetLinkedListLength(pHead->pNext); // Recursive case
}

/* delete all nodes with a specific value from the linked list */
/* input: pHead: head node pointer to the linked list which to be processed */
/* input: val: all nodes with value equal to val should be deleted */
/* output: the pointer to the head ndoe of the linked list after the delete operation */
struct ECLinkedListNode *ECLinkedListDeleteVal(struct ECLinkedListNode *pHead, int val)
{
  if (pHead == NULL)
  {
    return NULL; // base case: empty list
  }

  // Recursively process the rest of the list
  pHead->pNext = ECLinkedListDeleteVal(pHead->pNext, val);

  // If current node has the target value, delete it
  if (pHead->value == val)
  {
    struct ECLinkedListNode *temp = pHead; // save current node to free memory
    pHead = pHead->pNext;                   // move the head to the next node
    free(temp);                            // free the deleted node
  }

  return pHead; // return the updated head
}