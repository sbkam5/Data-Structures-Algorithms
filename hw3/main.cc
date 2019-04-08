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

#include "hashtable.hh"

/* ============================================================
 */

int
main (int argc, char* argv[])
{
  int N = -1;
  int t =-1;

  if (argc == 2) {
    N = atoi (argv[1]);
    assert (N > 0);
  } else {
    fprintf (stderr, "usage: %s <n>\n", argv[0]);
    fprintf (stderr, "where <n> is the length of the list to sort.\n");
    return -1;
  }

  stopwatch_init ();
  struct stopwatch_t* timer = stopwatch_create (); assert (timer);

  /*randomize seed*/
  //srand(time(NULL));

  HASHTABLE* table = makeHashTable(N);
  int fifty = 0, ninety = 1, random, fiftySum = 0, ninetySum=0;
  float fiftyCount = 0.0, ninetyCount = 0.0, average1 = 0.0, average2 = 0.0, failfifty = 0.0, failninety = 0.0, successAvg = 0.0, successAvg2 = 0.0;

  //
  for(int i=0; i<N ; i++){
    random = (rand() % (100000+1));
    int x = insert(table, N, random, random);

    //Only care about averaging stuff up to 90%
    if(i <= N * 9/10){
      ninetySum += x;
      ninetyCount += 1.0;

      //Average the probes for insert up to 50%
      if(i <= N/2){
        if(i+1 >= N/2){
          fifty = 1;
        }
        fiftySum += x;
        fiftyCount += 1.0;
      }

      //Average the probes to search at 50%
      if(fifty == 1 && i >= N/2){
        fifty = 0;
        //printf("--------------------------Fifty Percent Full----------------------\n");
        int sum = 0, temp=0, p=0, sumSuccess = 0;
        
        for(int j = 0; j < 10000; j++){
          temp = (rand() % (100000+1));
          p = probe(table, N, temp);
          sum += p;
          if(p == -1){
            failfifty += 1.0;
          }
          else{
            sumSuccess += p;
          }
        }
        
        average1 = sum/10000.00;
        if(failfifty != 10000.0){
          successAvg = sumSuccess/(10000-failfifty);
        }
      }
    }

    if(i >= N * 9/10 && ninety==1){
      ninety = 0;
      //printf("--------------------------Ninety Percent Full---------------------\n");
      int sum = 0, temp=0, p=0, sumSuccess=0;
      float average = 0.0;

      for(int j = 0; j < 10000; j++){
        temp = (rand() % (100000+1));
        p = probe(table, N, temp);
        sum += p;
        if(p == -1){
          failninety += 1.0;
        }
        else{
          sumSuccess += p;
        }
      }

      average2 = sum/10000.00;
      if(failninety != 10000.0){
        successAvg2 = sumSuccess/(10000-failninety);
      }
    }

    /*if( x <= N){
      printf("Insert was succesful for key = %d. Probed %d times \n", random, x);
    }
    else{
      printf("Insert was unsuccessful for key = %d.\n", random);
    }*/
  }

  printf("\n");
  printf("The average amount of probes to insert at 50 percent is %f\n", fiftySum/fiftyCount);
  printf("The total number of failed probe searches at 50 percent is %.2f\n", failfifty);
  printf("The average amount of successful probes searches at 50 percent is %.2f\n", successAvg);
  printf("The average amount of probes to search at 50 percent is %.2f \n\n", average1);

  printf("The average amount of probes to insert at 90 percent is %f\n", ninetySum/ninetyCount);
  printf("The total number of failed probe searches at 90 percent is %.2f\n", failninety);
  printf("The average amount of successful probe searches at 90 percent is %.2f\n", successAvg2);
  printf("The average amount of probes to search at 90 percent is %.2f \n\n", average2);
  /*for(int i = 0; i < N; i++){
    int p = probe(table, N, i);
    printf("It took %d probes to find %d\n", p, i);  //an initial print
  }*/

  
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
  deleteHashTable(table);
  stopwatch_destroy (timer);
  return 0;
}

/* eof */
