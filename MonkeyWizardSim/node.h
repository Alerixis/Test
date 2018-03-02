#ifndef _NODE_H_
#define _NODE_H_

#include "Unit.h"

class Unit;


class Node {

 public:
  Node();
  ~Node();
  
  //Pointers to the Unit this node of the list holds
  //and the next node in the list
  Unit *m_ptr;
  Node *m_next;
  
};

#endif
