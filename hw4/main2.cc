/**
 *  \file driver.cc
 *  \brief HW 1: OpenMP
 *
 *  This program
 *
 *  - creates an input array of keys to sort, where the caller gives
 *    the array size as a command-line input;
 *
 *  - sorts it using quicksort, noting the execution time;
 *
 *  - sorts it using YOUR sorting implementation, also noting the
 *    execution time;
 *
 *  - checks that the two sorts produce the same result;
 *
 *  - outputs the execution times and effective sorting rate (i.e.,
 *    keys per second).
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include "timer.c"

#include "dist.hh"
#include "list.hh"

/* ============================================================
 */

int
main (int argc, char* argv[])
{
  int N = -1;
  int t =-1;

  /*if (argc == 3) {
    N = atoi (argv[1]);
    t = atoi (argv[2]);
    assert (N > 0);
  } else {
    fprintf (stderr, "usage: %s <n>\n", argv[0]);
    fprintf (stderr, "where <n> is the length of the list to sort.\n");
    return -1;
  }*/

  stopwatch_init ();
  struct stopwatch_t* timer = stopwatch_create (); assert (timer);

  /*randomize seed*/
  srand(time(NULL));

  int length1 = 0, length2 = 0;
  char strlength[10];
  char *s1, *s2;
  FILE* inputFile = fopen("input2.txt", "r");

  fgets(strlength, 100, inputFile);
  sscanf(strlength, "%d", &length1);
  s1 = (char*)malloc(sizeof(char)*(length1+2));
  s1[0] = ' ';
  fgets(&(s1[1]), length1+1, inputFile);

  fgets(strlength, 100, inputFile);
  fgets(strlength, 100, inputFile);
  sscanf(strlength, "%d", &length2);
  s2 = (char*)malloc(sizeof(char)*(length2+2));
  s2[0] = ' ';
  fgets(&(s2[1]), length2+1, inputFile);

  fclose(inputFile);

  int tot_cost = distance(s1, s2, length1, length2);
  LIST* l = makeList(length1+1);
  copyString(l, s1, length1+1);

  /*printf("String1: \n");

  NODE* temp = l->first;
  while(temp != NULL){
    printf("%c", temp->ch);
    temp= temp->next;
  }
  printf("\n\n");
  printf("String2: \n");
  printf("%s", s2);
  printf("\n\n");


  char s1[9] = " Fuucckk";
  char s2[6] = " Fuck";
  
  int tot_cost = distance(s1, s2, 7, 4);

  LIST* l = makeList(8);
  copyString(l, s1, 8);

  printf("String: \n");

  NODE* temp = l->current;
  while(temp != NULL){
    printf("%c", temp->ch);
    temp= temp->next;
  }

  printf("\n\n");*/

  FILE* instr = fopen("instructions.txt", "r");
  char s[10];
  int input = 0;
  int s2count = 0;

  printf("Total Minimum Cost: %d \n\n", tot_cost);

  /*printf("Operations:\n");
  int count = 0;
  while(fgets(s, 10, instr) != NULL){
    sscanf(s, "%d", &input);
    if(count !=0){
      printf("%d", input);
    }
    count = 1;

    if(input == 0){
      l->current = l->current->next;
      s2count++;
    }
    else if(input == 3){
      addChar(l, s2[s2count]);
      s2count++;
    }
    else if(input == 2){
      deleteChar(l);
    }
    else{
      replaceChar(l, s2[s2count]);
      s2count++;
    }

  }

  printf("\n\n");
  printf("Output: \n");
   
  temp = l->first;
  while(temp != NULL){
    printf("%c", temp->ch);
    temp= temp->next;
  }
  printf("\n\n");


  printf("\n\n");*/
  fclose(instr);

  stopwatch_destroy (timer);
  return 0;
}

/* eof */
