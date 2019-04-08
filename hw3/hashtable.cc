#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "hashtable.hh"

/*Make a hash table*/
HASHTABLE* makeHashTable(int n){
  HASHTABLE* h = (HASHTABLE*)malloc(sizeof(HASHTABLE));

  NODE* e = (NODE*)malloc(sizeof(NODE)*n);
  for(int i = 0; i < n; i++){
    e[i].value = -1;
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
  int i = 0;
  
  for(i = 0; i < n; i++){
    int temp = (index + i) % n;

    /*-2 represents a recently opened up slot, while -1 represents a fully empty slot.
     * In both instances, however, it is safe to insert an element into there*/
    if(getWithIndex(h, temp) >= 0){
      continue;
    }
    else{
      h->elements[temp].value = data;
      h->elements[temp].key = key;
      break;
    }
  }

  return i;
}

/*finds an element with a key*/
int get(HASHTABLE* h, int n, int key){
  
  int index = hash(n, key);
  int i = 0, value=0;

  for(i = 0; i < n; i++){
    int temp = (index + i) % n;

    if(getWithIndex(h, temp) == -1){
      return -1;
    }
    else if(getKeyWithIndex(h, temp) != key){
      continue;
    }
    else{
      return getWithIndex(h, temp);
    }
  }

  return -1;
}

/*Finds an element with a key, removes it, and returns it*/
int remove(HASHTABLE* h, int n, int key){

  int index = hash(n, key);
  int i = 0, value=0;

  for(i = 0; i < n; i++){
    int temp = (index + i) % n;

      if(getWithIndex(h, temp) == -1){
          return -1;
      }
      else if(getKeyWithIndex(h, temp) != key){
        continue;
      }
      else{
        /*-2 is used to symbolize that an element was recently emptied*/
        int x = getWithIndex(h, temp);
        h->elements[temp].value = -2; 
        return x;
      }
  }

  return -1;
}


/*Returns the number of probes required to find an element*/
int probe(HASHTABLE* h, int n, int key){
  int index = hash(n, key);
  int i = 0;

  for(i = 0; i < n; i++){
    int temp = (index + i) % n;

    if(getWithIndex(h, temp) == -1){
      return -1;
    }
    else if(getKeyWithIndex(h, temp) != key){
      continue;
    }
    else{
      return i;
    }
  }

  return -1;
}

/*get an element via an index*/
int getWithIndex(HASHTABLE* h, int i){

  return h->elements[i].value;

}

int getKeyWithIndex(HASHTABLE* h, int i){
  
  return h->elements[i].key;
}

//Delete Hash Tables
void deleteHashTable(HASHTABLE* h){
  free(h->elements);
  free(h);
}
