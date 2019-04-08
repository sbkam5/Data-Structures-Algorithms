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

  int length1 = 22, length2 = 16;
  char s1[24] = " electrical engineering";
  char s2[18] = " computer science";

  /*int length1 = 6, length2 = 6;
  char s1[8] = " goober";
  char s2[8] = " gligar";*/
  

  int tot_cost = distance(s1, s2, length1, length2);
  LIST* l = makeList(length1+1);
  copyString(l, s1, length1+1);

  printf("String1: \n");

  NODE* temp = l->first;
  while(temp != NULL){
    printf("%c", temp->ch);
    temp= temp->next;
  }
  printf("\n\n");
  printf("String2: \n");
  printf("%s", s2);
  printf("\n\n");


  /*char s1[9] = " Fuucckk";
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
  FILE* output = fopen("Output.txt", "w");
  char s[10];
  int input = 0, input2 = 0;
  int s2count = 0;

  printf("Total Minimum Cost: %d \n\n", tot_cost);

  printf("Operations:\n");
  int count = 0;
  while(fgets(s, 10, instr) != NULL){
    sscanf(s, "%d %d", &input, &input2);
    if(count !=0){
      printf("%d", input);
    }
    count = 1;

    if(input == 0){
      l->current = l->current->next;
      s2count++;
      fprintf(output, "right  ");
    }
    else if(input == 3){
      addChar(l, s2[s2count]);
      s2count++;
      fprintf(output, "add %c  ", s2[s2count-1]);
    }
    else if(input == 2){
      deleteChar(l);
      fprintf(output, "delete  ");
    }
    else{
      replaceChar(l, s2[s2count]);
      s2count++;
      fprintf(output, "replace with %c  ", s2[s2count-1]);
    }

    //Print out current s1
    temp = l->first;
    while(temp != NULL){
      fprintf(output, "%c", temp->ch);
      temp = temp->next;
    }
    fprintf(output, "  %d  %d", input, input2);
    fprintf(output, "\n");

  }

  printf("\n\n");
  printf("Output: \n");
   
  temp = l->first;
  while(temp != NULL){
    printf("%c", temp->ch);
    temp= temp->next;
  }
  printf("\n\n");


  printf("\n\n");
  fclose(instr);
  fclose(output);

  stopwatch_destroy (timer);
  return 0;
}

/* eof */
