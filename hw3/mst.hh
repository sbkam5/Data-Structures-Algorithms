#if !defined (MST_HH)
#define MST_HH

typedef struct adjList ADJLIST;

typedef struct adjNode ADJNODE;

typedef struct graph GRAPH;

struct graph{
  int vertices;
  ADJLIST* list;
};

struct adjList{
  ADJNODE* head;
};

struct adjNode{
  int vertex;
  float weight;
  ADJNODE* next;
};

GRAPH* makeGraph(int vertices);

ADJNODE* makeAdjNode(int vertex, float weight);

void addEdge(GRAPH* graph, int parent, int dest, float weight);

typedef struct minHeap MINHEAP;

typedef struct minNode MINNODE;

struct minHeap{
  int currentSize;
  int size;
  int* pos;
  MINNODE** nodes;
};

struct minNode{
  int vertex;
  float key;
};

MINHEAP* makeMinHeap(int size);

MINNODE* makeMinNode(int vertex, float key);

void swapMinNodes(MINNODE** a, MINNODE** b);

void minHeapify(MINHEAP* heap, int index);

MINNODE* extractMinNode(MINHEAP* heap);

void decreaseKey(MINHEAP* heap, int vertex, float key);

int isInHeap(MINHEAP* heap, int vertex);

void MST(GRAPH* graph, int z);

void deleteGraph(GRAPH* graph);

void deleteHeap(MINHEAP* heap);

#endif
