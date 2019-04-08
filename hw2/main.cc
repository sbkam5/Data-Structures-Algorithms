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

#include "main.hh"

/* ============================================================
 */

int
main (int argc, char* argv[])
{
  int N = -1;
  int t =-1;

  if (argc == 3) {
    N = atoi (argv[1]);
    t = atoi (argv[2]);
    assert (N > 0);
  } else {
    fprintf (stderr, "usage: %s <n>\n", argv[0]);
    fprintf (stderr, "where <n> is the length of the list to sort.\n");
    return -1;
  }

  stopwatch_init ();
  struct stopwatch_t* timer = stopwatch_create (); assert (timer);

  /*randomize seed*/
  srand(time(NULL));


  /* Create an input array of length N, initialized to random values 
  keytype* A_in = newKeys (N);
  for (int i = 0; i < N; ++i)
    A_in[i] = lrand48 ();*/

  QUEUE* queue = makeQueue(N);
  QUEUE_OBJECT* object = queue->head;
  float f = 0.0;
  /*for(int i = 0; i < N; i++){
    printf("%f ", object->value);  //an initial print
    object = object->next;
  }*/


  //for t times, do an enqueue and dequeue command back to back
  stopwatch_start (timer);
  //start timer at beginning of actual enqueue and dequeue command
  for(int j = 0; j < t; j++){
    f = dequeue(queue);
    enqueue(queue, f);
    object = queue->head;

    //a print after every operation
    /*for(int i = 0; i < N; i++){
      printf("%f ", object->value);
      object = object->next;
    }*/

  }
  
  printf("\n");
  long double time = stopwatch_stop (timer);
  printf("Code took %Lg seconds\n", time);

  printf("\n --------------------------------------------\n");

  printf ("\nN == %d\n\n", N);

  /* Sort, calling YOUR routine. 
  keytype* A_ms = newCopy (N, A_in);
  stopwatch_start (timer);
  mySort (N, A_ms);
  long double t_ms = stopwatch_stop (timer);
  printf ("My sort: %Lg seconds ==> %Lg million keys per second\n",
	  t_ms, 1e-6 * N / t_ms);
  assertIsSorted (N, A_ms);
  assertIsEqual (N, A_ms, A_qs);*/
  
  /* Cleanup 
  printf ("\n");
  free (A_in);
  free (A_qs);
  free (A_ms);*/
  deleteQueue(queue);
  stopwatch_destroy (timer);
  return 0;
}

/* eof */
