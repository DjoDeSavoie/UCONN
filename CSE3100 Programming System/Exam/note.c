struct Node {
    int data;
    struct Node* next;
};

struct Node* getLast(struct Node* head) {
    if (head == NULL) return NULL; // Empty list
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    return temp; // Last element
}


struct Node* reverseList(struct Node* head) {
    struct Node* prev = NULL;
    struct Node* curr = head;
    struct Node* next = NULL;
    
    while (curr != NULL) {
        next = curr->next; // Store next
        curr->next = prev; // Reverse the pointer
        prev = curr; // Move prev and curr forward
        curr = next;
    }
    return prev; // New head of the reversed list
}


void removeDuplicates(struct Node* head) {
    struct Node* current = head;
    struct Node* temp, *dup;

    while (current != NULL && current->next != NULL) {
        temp = current;
        while (temp->next != NULL) {
            if (current->data == temp->next->data) {
                dup = temp->next;
                temp->next = temp->next->next;
                free(dup); // Remove and free duplicate
            } else {
                temp = temp->next;
            }
        }
        current = current->next;
    }
}


struct Node* insertAtBeginning(struct Node* head, int newData) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = newData;
    newNode->next = head;
    return newNode;
}


struct Node* insertAtEnd(struct Node* head, int newData) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = newData;
    newNode->next = NULL;

    if (head == NULL) return newNode;

    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}



void insertAfter(struct Node* prevNode, int newData) {
    if (prevNode == NULL) return;
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = newData;
    newNode->next = prevNode->next;
    prevNode->next = newNode;
}


struct Node* deleteByValue(struct Node* head, int key) {
    struct Node* temp = head;
    struct Node* prev = NULL;

    if (temp != NULL && temp->data == key) {
        head = temp->next; // Key found at head
        free(temp);
        return head;
    }

    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return head; // Key not found

    prev->next = temp->next;
    free(temp);
    return head;
}



struct Node* deleteByPosition(struct Node* head, int position) {
    if (head == NULL) return NULL;

    struct Node* temp = head;

    if (position == 0) { // Head node to be deleted
        head = temp->next;
        free(temp);
        return head;
    }

    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) return head;

    struct Node* next = temp->next->next;
    free(temp->next);
    temp->next = next;
    return head;
}


struct Node* mergeSortedLists(struct Node* l1, struct Node* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    if (l1->data < l2->data) {
        l1->next = mergeSortedLists(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeSortedLists(l1, l2->next);
        return l2;
    }
}


int countNodes(struct Node* head) {
    int count = 0;
    struct Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}






//double linked list

struct DNode {
    int data;
    struct DNode* next;
    struct DNode* prev;
};

struct DNode* getLastD(struct DNode* head) {
    if (head == NULL) return NULL;
    struct DNode* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    return temp;
}


struct DNode* reverseDoubly(struct DNode* head) {
    struct DNode* temp = NULL;
    struct DNode* curr = head;

    while (curr != NULL) {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev; // Move to the next node (prev is now next)
    }

    if (temp != NULL) head = temp->prev; // Update head to the new front
    return head;
}


void removeDuplicatesD(struct DNode* head) {
    struct DNode* current = head;
    struct DNode* temp;

    while (current != NULL) {
        temp = current->next;
        while (temp != NULL) {
            if (current->data == temp->data) {
                temp->prev->next = temp->next;
                if (temp->next != NULL) {
                    temp->next->prev = temp->prev;
                }
                free(temp); // Free the duplicate node
            }
            temp = temp->next;
        }
        current = current->next;
    }
}


struct DNode* insertAtEndD(struct DNode* head, int newData) {
    struct DNode* newNode = (struct DNode*)malloc(sizeof(struct DNode));
    struct DNode* last = head;
    newNode->data = newData;
    newNode->next = NULL;

    if (head == NULL) {
        newNode->prev = NULL;
        return newNode;
    }

    while (last->next != NULL) last = last->next;

    last->next = newNode;
    newNode->prev = last;

    return head;
}


void bubbleSort(struct Node* head) {
    int swapped;
    struct Node* ptr1;
    struct Node* lptr = NULL;

    if (head == NULL) return;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}



void splitList(struct Node* head, struct Node** front, struct Node** back) {
    struct Node* slow = head;
    struct Node* fast = head->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = head;
    *back = slow->next;
    slow->next = NULL;
}




