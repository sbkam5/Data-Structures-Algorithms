#include <stdlib.h>
#include <stdio.h>
#include "list.hh"

NODE* makeNode(char c){
  NODE* temp = (NODE*)malloc(sizeof(NODE));

  temp->ch = c;
  temp->prev = NULL;
  temp->next = NULL;

  return temp;
}

LIST* makeList(int n){
  LIST* temp = (LIST*)malloc(sizeof(LIST));
  temp->first = NULL;
  temp->last = NULL;
  NODE* node = NULL;
  temp->length = 0;

  for(int i=0; i < n ; i++){
    node = makeNode('c');
    if(i==0){
      temp->first = node;  //if just starting out, both first and last point to same node
      temp->last = node;
    }
    else{
      temp->last->next = node;  //Otherwise, the "last" pointer will then expand to the new node
      node->prev = temp->last;
      temp->last = node;
    }
    temp->length = temp->length + 1;  //length of list grows with every successful add.
  }
  temp->current = temp->first;

  return temp;

}

void copyString(LIST* l, char*s, int length){
  NODE* temp = l->first;

  for(int i = 0; i < length; i++){
    temp->ch = s[i];
    temp = temp->next;
  }
}

/*This function deletes a node*/
void deleteNode(NODE* n){
  n->prev = NULL;
  n->next = NULL;
  free(n);
}

void deleteList(LIST* l){
  int length = l->length;
  NODE* temp1 = l->first;
  NODE* temp2 = NULL;

  while((length > 0) && (temp1 != NULL)){  //while length > 0, this means there are still nodes to call deleteNode on.
    temp2 = temp1;
    temp1 = temp1->next;
    deleteNode(temp2);
    length--;
  }

  free(l);
}

/*--------------------------------Miscellaneous methods--------------------------*/
//Add an element to frint of list
void addFront(LIST* l, char i){
  NODE* tempFirst = l->first;
  NODE* newNode = makeNode(i);

  newNode->next = tempFirst;
  tempFirst->prev = newNode;
  l->first = newNode;
  l->length = l->length + 1;
}

//Add an element to the back of list
void addBack(LIST *l, char i){
  NODE* tempLast = l->last;
  NODE* newNode = makeNode(i);

  newNode->prev = tempLast;
  tempLast->next = newNode;
  l->last = newNode;
  l->length = l->length + 1;
}

//Does the add operation
void addChar(LIST* l, char c){
  NODE* current = l->current;
  if(current == NULL){
    return;
  }
  NODE* prev = current->prev;
  NODE* next = current->next;
  NODE* newNode = makeNode(c);
  
  newNode->next = current;
  newNode->prev = current->prev;
  current->prev = newNode;
  
  if(prev != NULL){
    prev->next = newNode;
  }
}

//Does the replace operation
void replaceChar(LIST* l, char c){
  NODE* current = l->current;
  if(current == NULL){
    return;
  }
  
  l->current = current->next;
  current->ch = c;
}

//Does the delete char operation
void deleteChar(LIST* l){
  NODE* current = l->current;
  if(current == NULL){
    return;
  }
  NODE* prev = current->prev;
  NODE* next = current->next;
  
  if(prev != NULL){
    prev->next = next;
  }
  
  if(next != NULL){
    next->prev = prev;
  }
  
  l->current = current->next;
  deleteNode(current);
}

//Returns the value of the first node
char returnFrontNode(LIST *l){
  return l->first->ch;
}

//returns the value of the last node
char returnLastNode(LIST *l){
  return l->last->ch;
}

//removes the node at a specified index
void removeNode(LIST* l, NODE* n){

  if(n == NULL){
    return;
  }

  NODE* prevNode = NULL;
  NODE* nextNode = NULL;

  //Make the temporary pointers equal to the next and previous nodes.
  prevNode = n->prev;
  nextNode = n->next;
  //Link the previous and next nodes together.  Afterward, delete the current node.
  if(prevNode != NULL && nextNode != NULL){
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
  }
  else if(prevNode != NULL && nextNode == NULL){
    prevNode->next = NULL;
  }
  else if(prevNode == NULL && nextNode != NULL){   //This condition can only happen when the index is 0
    nextNode->prev = NULL;
    l->first = nextNode;
  }
  else{
    //do nothing
  }

  //once the node is succesfully deleted, correct the length of the list.
  deleteNode(n);
  l->length = l->length - 1;
}
