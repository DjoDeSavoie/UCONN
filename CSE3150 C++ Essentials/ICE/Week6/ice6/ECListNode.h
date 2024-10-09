#ifndef _EC_LIST_NODE_H
#define _EC_LIST_NODE_H

#include <iostream>

class ECListNode
{
public:
  ECListNode() : pn(nullptr), val(0) {}

  ECListNode(int v) : pn(nullptr), val(v) {}

  ECListNode *GetNext() const { return pn; }

  void SetNext(ECListNode *pn1) { pn = pn1; }

  int GetValue() const { return val; }

  void SetValue(int v) { val = v; }

private:
  ECListNode *pn;
  int val;
};

#endif
