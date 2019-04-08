#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "hashtable2.hh"

/*Make a hash table*/
HASHTABLE* makeHashTable(int n){
  HASHTABLE* h = (HASHTABLE*)malloc(sizeof(HASHTABLE));

  NODE** e = (NODE**)malloc(sizeof(NODE*)*n);
  NODE* temp = NULL;

  for(int i = 0; i < n; i++){
    temp = (NODE*)malloc(sizeof(NODE));
    e[i] = temp;
    temp->value = -1;
    temp->next = NULL;
  }

  h->elements = e;

  return h;
}

/*Hash a key*/
int hash(int n, int key){
  /*int p = (int)(log(n)/log(2));
  int w = 32;
  int A = 3300000013; 

  return (int)(fmod((A * key) , pow(2,w)) / (2*((w - p))));*/

  double A = (sqrt(5)-1)/2;
  return (int)(n*fmod((key * A), 1));

}

/*insert an element*/
int insert(HASHTABLE* h, int n, int key, int data){

  int index = hash(n, key);
  NODE* node = h->elements[index];
  NODE* parent = NULL;
  int i = 0;
  
  if(node->value == -1){
    node->value = data;
    node->key = key;
    return i;
  }

  while(node != NULL){
    parent = node;
    node = node->next;
    i++;
  }

  node = parent;
  NODE* temp = (NODE*)malloc(sizeof(NODE));
  temp->key = key;
  temp->value = data;
  temp->next = NULL;
  node->next = temp;

  return i;
}

/*finds an element with a key*/
int get(HASHTABLE* h, int n, int key){
  
  int index = hash(n, key);
  NODE* node = h->elements[index];

  while(node != NULL){
    if(node->value == -1){
      break;
    }

    if(node->key == key){
      return node->value;
    }

    node = node->next;
  }

  return -1;
}

/*Finds an element with a key, removes it, and returns it*/
int remove(HASHTABLE* h, int n, int key){
  int index = hash(n, key);
  int i = 0;
  int temp = 0;
  NODE* node = h->elements[index];
  NODE* parent = node;

  while(node != NULL){
    if(node->value <= -1){
      break;
    }

    if(node->key == key){
      temp = node->value;

      //If the node is part of the original hashtable.
      if(i == 0){
        //If there are no other nodes linked to this one, dont delete it, just "empty" it.
        if(node->next == NULL){
          node->value = -2;
          return temp;
        }
        else{
          h->elements[index] = node->next;
          free(node);
          return temp;
        }
      }
      parent->next = node->next;
      free(node);
      return temp;
    }

    parent = node;
    node = node->next;
    i++;
  }

  return -1;
}


/*Returns the number of probes required to find an element*/
int probe(HASHTABLE* h, int n, int key){
  int index = hash(n, key);
  int i = 0;
  NODE* node = h->elements[index];

  while(node != NULL){
    if(node->value == -1){
      break;
    }

    if(node->key == key){
      return i;
    }

    node = node->next;
    i++;
  }

  return -1;
}


//Delete Hash Tables
void deleteHashTable(HASHTABLE* h, int n){
  NODE* node = NULL;
  NODE* temp = NULL;

  for(int i=0; i < n; i++){
    node = h->elements[i];
    while(node != NULL){
      temp = node;
      node = node->next;
      free(temp);
    }
  }

  free(h);
}

