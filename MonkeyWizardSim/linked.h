#ifndef _LINKED_H_
#define _LINKED_H_

class Unit;
class Game;

#include "node.h"


class LinkedList {

  friend class Game;
  
 public:
  LinkedList();
  ~LinkedList();
  
  void Add(Unit *uPtr);
  void AddNode(Node *ptr);

  Node *Pop();
  Node *Remove(Unit *uPtr);
  void ShallowCopy(LinkedList& B);
  
  unsigned int Size();

 private:
  unsigned int m_size;
  Node *m_head;
};

#endif
