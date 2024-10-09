#include "ECListNode.h"
#include "ECList.h"

// Linked list
ECList ::ECList() : pHead(nullptr), numNodes(0)
{
}

// Insert node with value val after a node
// If pre node is NULL, insert to the front
void ECList ::Insert(int val, ECListNode *pPre)
{
    ECListNode *p1 = new ECListNode(val);
    if (pPre != nullptr)
    {
        p1->SetNext(pPre->GetNext());
        pPre->SetNext(p1);
    }
    else
    {
        p1->SetNext(pHead);
        pHead = p1;
    }
    numNodes++;
}

// Delete a node
void ECList ::Delete(ECListNode *pNode)
{
    if (pNode == nullptr)
        return;

    ECListNode *pPre = nullptr;
    ECListNode *pc = pHead;
    while (pc != nullptr)
    {
        if (pc == pNode)
        {
            // Find the node, delete it
            if (pPre != nullptr)
            {
                pPre->SetNext(pc->GetNext());
            }
            else
            {
                pHead = pHead->GetNext();
            }

            // Deallocate the node to prevent memory leaks
            delete pc;
            --numNodes;
            return;
        }
        else
        {
            pPre = pc;
            pc = pc->GetNext();
        }
    }
}

// Get a node with value; if multiple nodes with the same value, return the first from head
ECListNode *ECList::GetNode(int val)
{
    ECListNode *pc = pHead;
    while (pc != nullptr)
    {
        if (pc->GetValue() == val)
        {
            return pc;
        }
        pc = pc->GetNext();
    }
    return nullptr;
}

// Get the number of nodes in the list
int ECList::GetSize() const
{
    return numNodes;
}
