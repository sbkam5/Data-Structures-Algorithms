#include <stdlib.h>
#include <stdio.h>
#include "list.hh"

NODE* makeNode(int n){
  NODE* temp = (NODE*)malloc(sizeof(NODE));

  temp->value = n;
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
    node = makeNode(i+1);
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

  return temp;

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
void addFront(LIST* l, int i){
  NODE* tempFirst = l->first;
  NODE* newNode = makeNode(i);

  newNode->next = tempFirst;
  tempFirst->prev = newNode;
  l->first = newNode;
  l->length = l->length + 1;
}

//Add an element to the back of list
void addBack(LIST *l, int i){
  NODE* tempLast = l->last;
  NODE* newNode = makeNode(i);

  newNode->prev = tempLast;
  tempLast->next = newNode;
  l->last = newNode;
  l->length = l->length + 1;
}

//Returns the value of the first node
int returnFrontNode(LIST *l){
  return l->first->value;
}

//returns the value of the last node
int returnLastNode(LIST *l){
  return l->last->value;
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

//returns the value of the previous node given the pointer to a current one
int returnPrevNode(NODE* n){
  return n->prev->value;
}

//returns the value of the next node given the pointer to a current node
int returnNextNode(NODE* n){
  return n->next->value;
}

//returns the index of a Node with a desired value.
NODE* findNode(LIST* l, int val){
  int index = 0;
  NODE* n = l->first;

  while(n != NULL){
    //if current node has desired value, return its index
    if(n->value == val){
      return n;
    }
    else{
      //otherwise, move on to the next node.
      index++;
      n = n->next;
    }
  }

  //If the program reaches this point, it means the desired value is not in the array.  Thus, a negative number is returned.
  return NULL;
}

//returns the value of the prev node from a specified index.
int returnPrevNode(LIST* l, int i){
  NODE* current = l->first;
  while(i>0 && current!=NULL){
    current = current->next;   //get address of node of specified index
    i--;
  }

  if(current == NULL){   //If node is ever equal to null, return -1.
    return -1;
  }
  current = current->prev;
  if(current == NULL){
    return -1;
  }
  return current->value;
}

//returns the value of the next node from a specified index.
int returnNextNode(LIST* l, int i){
  NODE* current = l->first;
  while(i>0 && current!=NULL){
    current = current->next;  //get address of node of specified index
    i--;
  }

  if(current == NULL){       //If node is ever equal to null return -1.
    return -1;
  }
  current = current->next;
  if(current == NULL){
    return -1;
  }
  return current->value;

}


