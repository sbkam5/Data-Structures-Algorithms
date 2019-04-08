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
#include "mst.hh"


/* ============================================================
 */

int
main (int argc, char* argv[])
{
  /*int N = -1;

  if (argc == 2) {
    N = atoi (argv[1]);
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
  int random = 0;
  int index = 0;

  printf("\n\n");

  stopwatch_start (timer);                                  //Start timer at beginning of operation
    

  //---------------------Create sparse read file-----------------------------------
  /*FILE* readFile = fopen("read.txt", "w");
  float f;
  fprintf(readFile, "%d\n", 100000);

  for(int i = 0; i < 100000-1; i++){
    f = (float)rand()/(float)(RAND_MAX/5.0);
    fprintf(readFile, "%d %d %f\n", i, i+1, f);
  }

  fclose(readFile);*/
  //---------------------Create dense read file------------------------------------
  /*FILE* readFile2 = fopen("read2.txt", "w");
  fprintf(readFile2, "%d\n", 100000);
  float f;

  for(int i = 0; i < 100000-1; i++){
    for(int j = i; j < i+1000; j++){
      if(j != i){
        f = (float)rand()/(float)(RAND_MAX/5.0);
        fprintf(readFile2, "%d %d %f\n", i, j%100000, f);
      }
    }
  }
  fclose(readFile2);*/

  FILE* inputFile = fopen("sparse_100000.txt", "r");
  int vertices = 0, x = 0, y = 0;
  float distance = 0.0;

  fscanf(inputFile, "%d", &vertices);
  GRAPH* graph = makeGraph(vertices);
  char s[100];
  fgets(s, 100, inputFile);

  while(fgets(s, 100, inputFile) != NULL){
    sscanf(s, " %d %d %f ", &x, &y, &distance);
    addEdge(graph, x, y, distance);
  }
  
  /*printf("Vertices: %d\n", vertices);
  for(int i=0; i < vertices; i++){
    for(int j=0; j < vertices; j++){
      printf("%.2f  ", graph[i*vertices + j]);
    }
    printf("\n");
  }*/

  MST(graph, 0);

  long double t_ms = stopwatch_stop (timer);
  printf("Operation took %Lg seconds\n", t_ms);             //Stop timer at end of operation
  printf("\n\n");

  fclose(inputFile);
  stopwatch_destroy (timer);
  return 0;
}

/* eof */
