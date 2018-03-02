#include <stdlib.h>
#include <iostream>
using namespace std;

#include "linked.h"

//Default Constructor
LinkedList::LinkedList(){
  m_head = new Node();
  m_size = 0;
}

//Destructor
LinkedList::~LinkedList() {
  Node *current, *next;

  current = m_head;

  //Delete all remaining troops and nodes
  while(current != NULL){
    next = current->m_next;
    current->m_next = NULL;
    delete current;
    current = next;
  }
}

//Add a new Unit onto the list
void LinkedList::Add(Unit *uPtr){
  Node *newNode = new Node();
  newNode->m_ptr = uPtr;
  newNode->m_next = m_head->m_next;
  m_head->m_next = newNode;
  m_size++;
}

//Adds a node to the end of the list to preserve order
void LinkedList::AddNode(Node *ptr){
  Node *current = m_head;
  while(current->m_next != NULL){
    current = current->m_next;
  }
  current->m_next = ptr;
  ptr->m_next = NULL;         ;
  m_size++;
}

//Pop Node from the front of list.
Node *LinkedList::Pop(){
  Node *ptr;
  
  if(m_head->m_next == NULL){
    return NULL;
  }

  ptr = m_head->m_next;
  m_head->m_next = ptr->m_next;
  ptr->m_next = NULL;
  m_size--;

  return ptr;
}

void LinkedList::ShallowCopy(LinkedList& B){
  Node *current, *next;

  //Delete the current list
  current = m_head->m_next;
  while(current != NULL){
    next = current->m_next;
    current->m_next = NULL;
    delete current;
    current = next;
  }

  //Point head of list to the first element of new list
  m_head->m_next = B.m_head->m_next;
  m_size = B.m_size;

  //Null out the new list to be destroyed
  B.m_head->m_next = NULL;
  B.m_size = 0;
  
}

//Return the size of the list
unsigned int LinkedList::Size(){
  return m_size;
}
