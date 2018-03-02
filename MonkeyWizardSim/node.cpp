#include <iostream>
using namespace std;

#include "node.h"
#include "Unit.h"

Node::Node(){
  m_next = NULL;
  m_ptr = NULL;
}

Node::~Node(){
  m_next = NULL;
  delete m_ptr;
  m_ptr = NULL;
}
