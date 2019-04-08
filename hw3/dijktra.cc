#include <stdlib.h>
#include <stdio.h>

int minimum(int distances[], int visited[]);

int main(int argc, char* argv[]){
  int parent[5] = {5, 1, 1, 2, 3};
  int child[5] = {4, 2, 3, 4, 5};
  int ids[5] = {1, 2, 3, 3, 2};
  int val = 2;
  
        int graph[5][5];
        int visited[5];
        int distances[5];
        int from, to, minDistance = 10000, changed = 0;

        for(int i = 0; i < 5; i++){
            distances[i] = 10000;
            visited[i] = 0;
        }

        for(int i = 0; i < 5; i++){
          for(int j = 0; j < 5; j++){
            graph[i][j] = 0;
          }
        }

        for(int i = 0; i < 5; i++){
            from = parent[i] - 1;
            to = child[i] - 1;
            graph[from][to] = 1;
            graph[to][from] = 1;
        }

        for(int i = 0; i < 5; i++){
          for(int j = 0; j < 5; j++){
            printf("%d ", graph[i][j]);
          }
          printf("\n\n");
        }

        for(int vertex = 0; vertex < 5; vertex++){
            if(ids[vertex] != val){
                continue;
            }

            distances[vertex] = 0;

            for(int i = 0; i < 5; i++){

                int min = minimum(distances, visited);
                visited[min] = 1;

                for(int j = 0; j < 5; j++){
                    if(distances[j] > graph[min][j] + distances[min] && visited[j] == 0
                    && graph[min][j] != 0){
                        distances[j] = distances[min] + graph[min][j];

                        if(ids[j] == val && distances[j] < minDistance){
                            minDistance = distances[j];
                            changed = 1;
                        }
                    }
                }
            
             printf("%d\n", min);

             for(int index = 0; index < 5; index++){
             printf("%d ", distances[index]);
             }
             printf("\n");

        }

        break;


        }
        

}

int minimum(int distances[], int visited[]){
  int min = 10000;
  int minIndex = 0;

        for(int i = 0; i < 5; i++){
            if(min > distances[i] && visited[i] == 0){
                min = distances[i];
                minIndex = i;
            }
        }
        return minIndex;
}
