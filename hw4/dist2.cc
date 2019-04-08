#include <stdio.h>
#include <stdlib.h>
#include "dist.hh"

int distance(char* s1, char* s2, int m, int n){

  COST** solutions = (COST**)malloc(sizeof(COST*)*(m+1));
  for(int i = 0; i <= m; i++){
    solutions[i] = (COST*)malloc(sizeof(COST)*(n+1));

    for(int j = 0; j <= n; j++){
      solutions[i][j].prev = NULL;
      solutions[i][j].s1 = i;
      solutions[i][j].s2 = j;
    }
  }

  dis_dynamic(s1, s2, m, n, solutions);

  COST* temp = &(solutions[m][n]);
  COST* backup = NULL;
  int cost = solutions[m][n].tot_cost;

  FILE* output = fopen("instructions.txt", "w");

  while(temp != NULL){
    //fprintf(output, "%d %d | %d %d\n", temp->cost, temp->tot_cost, temp->s1, temp->s2);
    backup = temp;
    temp = temp->prev;

    if(temp != NULL)
      temp->next = backup;
  }

  temp = backup;

  while(temp != NULL){
    if(temp->s1 == 0 && temp->s2 != 0){
      fprintf(output, "%d %d\n", 0, 0);
      int x = temp->s2;
      for(int i = 0; i < x; i++){
        fprintf(output, "%d %d\n", temp->cost, temp->tot_cost - (temp->cost * (x - i -1)));
      }
    }
    else if(temp->s2 == 0 && temp->s1 != 0){
      fprintf(output, "%d %d\n", 0, 0);
      int x = temp->s1;
      for(int i = 0; i < x; i++){
        fprintf(output, "%d %d\n", temp->cost, temp->tot_cost - (temp->cost * (x - i -1)));
      }
    }
    else{
      fprintf(output, "%d %d\n", temp->cost, temp->tot_cost);
    }
    temp = temp->next;
  }

  /*fprintf(output, "\n\n");

  for(int row = 0; row <= m; row++){
    for(int column = 0; column <= n; column++){
      fprintf(output, "%d ", solutions[row][column].tot_cost);
    }
    fprintf(output, "\n");
  }*/

  for(int i = 0; i <= m; i++){
    free(solutions[i]);
  }
  free(solutions);

  fclose(output);

  return cost;
}

void dis_dynamic(char* s1, char* s2, int m, int n, COST** solutions){

  for(int pos_1=0; pos_1 <= m; pos_1++){
    for(int pos_2=0; pos_2 <= n; pos_2++){

      if(pos_1 == 0){
        solutions[pos_1][pos_2].tot_cost = pos_2 * 3;
        solutions[pos_1][pos_2].cost     = (pos_2 == 0)? 0 : 3;
      }
      else if(pos_2 == 0){
        solutions[pos_1][pos_2].tot_cost = pos_1 * 2;
        solutions[pos_1][pos_2].cost     = 2;
      }
      else if(s1[pos_1] == s2[pos_2]){
        solutions[pos_1][pos_2].tot_cost = solutions[pos_1 -1][pos_2 -1].tot_cost;
        solutions[pos_1][pos_2].cost     = 0;
        solutions[pos_1][pos_2].prev     = &(solutions[pos_1-1][pos_2-1]);
        solutions[pos_1-1][pos_2-1].next = &(solutions[pos_1][pos_2]);
      }
      else{
        min(pos_1, pos_2, solutions,
            4 + solutions[pos_1-1][pos_2-1].tot_cost,
            2 + solutions[pos_1-1][pos_2].tot_cost,
            3 + solutions[pos_1][pos_2-1].tot_cost);
      }
    }
 }

}

void min(int pos_1, int pos_2, COST** solutions,  int replace, int remove, int add){
  int min = replace;

  /*First determine optimal operation*/
  if(remove < min){
    min = remove;
  }
  else if(add < min){
    min = add;
  }

  /*Once optimal operation is found, link that operation to the previous set of operations.*/
  if(min == replace){
    solutions[pos_1][pos_2].tot_cost  = min;
    solutions[pos_1][pos_2].cost      = 4;
    solutions[pos_1][pos_2].prev      = &(solutions[pos_1-1][pos_2-1]);
    solutions[pos_1-1][pos_2-1].next  = &(solutions[pos_1][pos_2]);
  }
  else if(min == remove){
    solutions[pos_1][pos_2].tot_cost  = min;
    solutions[pos_1][pos_2].cost      = 2;
    solutions[pos_1][pos_2].prev      = &(solutions[pos_1-1][pos_2]);
    solutions[pos_1-1][pos_2].next    = &(solutions[pos_1][pos_2]);
  }
  else{
    solutions[pos_1][pos_2].tot_cost = min;
    solutions[pos_1][pos_2].cost     = 3;
    solutions[pos_1][pos_2].prev     = &(solutions[pos_1][pos_2-1]);
    solutions[pos_1][pos_2-1].next   = &(solutions[pos_1][pos_2]);
  }

}


