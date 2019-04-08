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

#include "list.hh"

/* ============================================================
 */

int
main (int argc, char* argv[])
{
  int N = -1;

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
  srand(time(NULL));
  int random = 0;
  int index = 0;

  /* Create an input array of length N, initialized to random values 
  keytype* A_in = newKeys (N);
  for (int i = 0; i < N; ++i)
    A_in[i] = lrand48 ();*/

  LIST* list = makeList(N);
  NODE* node = NULL;
  int input = 1;
  int input2 = 0;
  int input3 = 0;
  node = list->first;

  //Show user what their list looks like.
  /*printf("Your list: ");
  while(node != NULL){
    printf("%d ", node->value);
    node = node->next;
  }*/
  printf("\n\n");

  stopwatch_start (timer);                                  //Start timer at beginning of operation
    
  for(int i = 0; i < 10; i++){
    random = (rand() % (N - 1 + 1)) + 1;                      //generate the random number
    node = findNode(list, random);                           //find the index of the random
    removeNode(list, node);                                  //remove that node from the list
    addFront(list, random);
  }

  long double t_ms = stopwatch_stop (timer);
  printf("Operation took %Lg seconds\n", t_ms);             //Stop timer at end of operation

  //---------------------This large section was used to help with debugging.-----------------------------------
  /*while(input != 9){
    printf("What do you want to do to your list?\n");
    printf("0 : Do the HW 2 operation\n");
    printf("1 : add to front\n");
    printf("2 : add to back\n");
    printf("3 : return first node\n");
    printf("4 : return last node\n");
    printf("5 : remove a node\n");
    printf("6 : return a previous node given an index\n");
    printf("7 : return a next node given an index.\n");
    printf("8 : search for a node that contains a value\n");
    printf("9 : quit\n");
    scanf("%d", &input);

    switch(input){
      case 0:
        for(int i = 0; i < 10; i++){
          random = (rand() % (N - 1 + 1)) + 1;                      //generate the random number
          //printf("The number to be moved is: %d\n", random);
          node = findNode(list, random);                           //find the index of the random
          removeNode(list, node);                                  //remove that node from the list
          addFront(list, random);                                   //add it back to the front

          node = list->first;
          printf("Your list: ");
          while(node != NULL){
            printf("%d ", node->value);
            node = node->next;
          }
          printf("\n\n");
        }
        break;
      case 1:
        printf("What do you want to add?");
        scanf("%d", &input2);
        addFront(list, input2);
        break;
      case 2:
        printf("What do you want to add?");
        scanf("%d", &input2);
        addBack(list, input2);
        break;
      case 3:
        input2 = returnFrontNode(list);
        printf("The front node is %d \n", input2);
        break;
      case 4:
        input2 = returnLastNode(list);
        printf("The last node is %d \n", input2);
        break;
      case 5:
        printf("You can't do that command.  Sorry\n");
        break;
      case 6:
        printf("Enter the index of the reference node:");
        scanf("%d", &input2);
        input3 = returnPrevNode(list, input2);
        printf("The value of the previous node is: %d\n", input3);
        break;
      case 7:
        printf("Enter the index of the reference node:");
        scanf("%d", &input2);
        input3 = returnNextNode(list, input2);
        printf("The value of the next node is: %d\n", input3);
        break;
      case 8:
        printf("Enter the value you wish to search for:");
        scanf("%d", &input2);
        node = findNode(list, input2);
        printf("The address of the node with your value: %p\n", node);
        break;
      default:
        printf("Command not recognized\n\n");
        break;
      }

      node = list->first;
      printf("Your list: ");
      while(node != NULL){
        printf("%d ", node->value);
        node = node->next;
      }
      printf("\n\n");
  }

  printf("\n\n");
  node = list->first;
  printf("Your New list: ");
  while(node != NULL){
    printf("%d ", node->value);
    node = node->next;
  }*/
  printf("\n\n");

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
  deleteList(list);
  stopwatch_destroy (timer);
  return 0;
}

/* eof */
