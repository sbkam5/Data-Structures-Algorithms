#include <stdlib.h>
#include <stdio.h>
#include "mst.hh"

/*This function creates a graph data structure*/
GRAPH* makeGraph(int vertices){
  GRAPH* graph = (GRAPH*)malloc(sizeof(GRAPH));
  graph->vertices = vertices; 
    
  graph->list = (ADJLIST*)malloc(vertices * sizeof(ADJLIST)); 
         
  for (int i = 0; i < vertices; i++){
    graph->list[i].head = NULL; 
  }             
  return graph;
}

/*This function creates a single adjacency list node*/
ADJNODE* makeAdjNode(int vertex, float weight){
  ADJNODE* newNode = (ADJNODE*)malloc(sizeof(ADJNODE)); 
  newNode->vertex = vertex; 
  newNode->weight = weight; 
  newNode->next = NULL; 
  return newNode; 
}

/*Adds an edge to adjacency list*/
void addEdge(GRAPH* graph, int parent, int dest, float weight){
  /*add the "dest" as an edge for the parent*/
  ADJNODE* newNode = makeAdjNode(dest, weight);
  newNode->next = graph->list[parent].head; 
  graph->list[parent].head = newNode; 
  
  /*add the "parent" as an edge for the dest*/
  newNode = makeAdjNode(parent, weight); 
  newNode->next = graph->list[dest].head; 
  graph->list[dest].head = newNode;
}

/*Makes a minimum heap*/
MINHEAP* makeMinHeap(int size){
  MINHEAP* minHeap = (MINHEAP*)malloc(sizeof(MINHEAP)); 
  minHeap->pos = (int*)malloc(size * sizeof(int)); 
  minHeap->size = size; 
  minHeap->currentSize = 0; 
  minHeap->nodes = (MINNODE**)malloc(size * sizeof(MINNODE*)); 
  return minHeap;
}

/*MAkes a minheap node*/
MINNODE* makeMinNode(int vertex, float key){
  MINNODE* minNode = (MINNODE*)malloc(sizeof(MINNODE)); 
  minNode->vertex = vertex; 
  minNode->key = key; 
  return minNode;
}

/*Swaps the position of two nodes*/
void swapMinNodes(MINNODE** a, MINNODE** b){
  MINNODE* temp = *a; 
  *a = *b; 
  *b = temp;
}

/*Performs minheapify*/
void minHeapify(MINHEAP* heap, int index){
  int smallest, left, right; 
  smallest = index; 
  left = 2 * index + 1; 
  right = 2 * index + 2; 
  
  //Find the index of the smallest node
  if (left < heap->currentSize && heap->nodes[left]->key < heap->nodes[smallest]->key){
    smallest = left; 
  }
                              
  if (right < heap->currentSize && heap->nodes[right]->key < heap->nodes[smallest]->key){
    smallest = right;
  }
  
  //If the index of the smallest node has changed, swap the index node with the current smallest one
  if (smallest != index) { 
    MINNODE* smallestNode = heap->nodes[smallest]; 
    MINNODE* idxNode = heap->nodes[index];
    
    heap->pos[smallestNode->vertex] = index;
    heap->pos[idxNode->vertex] = smallest; 
                                    
    swapMinNodes(&heap->nodes[smallest], &heap->nodes[index]); 
    minHeapify(heap, smallest); 
  }
}


/*Extracts the minimum node of minheap*/
MINNODE* extractMinNode(MINHEAP* heap){
  if (heap->currentSize == 0){
    return NULL;
  }
            
  MINNODE* root = heap->nodes[0]; 
  MINNODE* lastNode = heap->nodes[heap->currentSize - 1]; 
  heap->nodes[0] = lastNode; 

  //update position of last node and min node
  heap->pos[root->vertex] = heap->currentSize - 1; 
  heap->pos[lastNode->vertex] = 0;   
                   
  heap->currentSize = heap->currentSize - 1; 
  minHeapify(heap, 0); 
  
  return root;
}

/*Dexreases the key value of a particular vertex while mantaining the minheap property*/
void decreaseKey(MINHEAP* heap, int vertex, float key){
  int i = heap->pos[vertex]; 
  heap->nodes[i]->key = key; 
  
  while (i && heap->nodes[i]->key < heap->nodes[(i - 1) / 2]->key) { 
    heap->pos[heap->nodes[i]->vertex] = (i - 1) / 2; 
    heap->pos[heap->nodes[(i - 1) / 2]->vertex] = i; 
    swapMinNodes(&heap->nodes[i], &heap->nodes[(i - 1) / 2]); 
    
    //go back to parent
    i = (i - 1) / 2; 
  }
  //minHeapify(heap, i);
}

int isInHeap(MINHEAP* heap, int vertex){
  if (heap->pos[vertex] < heap->currentSize){
    return 1;
  }
  else{
    return 0;
  }
}

void MST(GRAPH* graph, int z){
  int vertices = graph->vertices; // Get the number of vertices in graph 
  int parent[vertices]; // Array to store constructed MST 
  float key[vertices]; // Key values used to pick minimum weight edge 
  
  MINHEAP* heap = makeMinHeap(vertices); 
  
  //Initialize min heap with all vertices.
  for (int v = 1; v < vertices; v++) { 
    parent[v] = -1; 
    key[v] = 1000000.00; 
    heap->nodes[v] = makeMinNode(v, key[v]); 
    heap->pos[v] = v; 
  } 

  //vertex 0 is chosen to start out 
  key[0] = 0.0; 
  heap->nodes[0] = makeMinNode(0, key[0]); 
  heap->pos[0] = 0;
  //parent[0] = 0;
  
  // Initially size of min heap is equal to number of vertices
  heap->currentSize = vertices; 
  
  // min heap contains all nodes not yet added to MST. 
  while (heap->currentSize != 0) { 
    MINNODE* minHeapNode = extractMinNode(heap); 
    int u = minHeapNode->vertex; // Store the extracted vertex number 
    
    ADJNODE* pCrawl = graph->list[u].head; 
    while (pCrawl != NULL) { 
      int v = pCrawl->vertex; 
    
    // If v is not yet included in MST and weight of u-v is less than what is currently saved in key, then update key and insert into MST
      if (isInHeap(heap, v) && pCrawl->weight < key[v]) { 
        key[v] = pCrawl->weight; 
        parent[v] = u; 
        decreaseKey(heap, v, key[v]); 
      } 
      
      //move on to the next adjacent node
      pCrawl = pCrawl->next; 
    } 
  }


  FILE* outputFile;
  if(z == 0){
    outputFile = fopen("Output.txt", "w");
  }
  else{
    outputFile = fopen("Output2.txt", "w");
  }
  fprintf(outputFile, "%d\n", vertices);
  for(int i = 0; i < vertices; i++){
    if(i != 0){
      fprintf(outputFile, "%d %d %f\n", parent[i], i, key[i]);
    }
  }

  fclose(outputFile);

  //deleteHeap(heap);
  
}


void deleteGraph(GRAPH* graph){
  ADJNODE* n = graph->list->head;
  ADJNODE* temp;

  while(n != NULL){
    temp = n;
    n = n->next;
    free(temp);
  }

  free(graph);
}

void deleteHeap(MINHEAP* heap){
  MINNODE** n = heap->nodes;
  int size = heap->size;

  for(int i=0; i < size; i++){
    free(n[i]);
  }

  free(heap);
}
