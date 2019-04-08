#if !defined (LIST_HH)
#define LIST_HH

typedef struct node NODE;
typedef struct list LIST;

struct node{
  NODE* next;
  NODE* prev;

  int value;

};

struct list{
  NODE* first;
  NODE* last;
  int length;

};

NODE* makeNode(int x);

LIST* makeList(int N);

void deleteNode(NODE* n);

void deleteList(LIST* l);

void addBack(LIST *l, int i);

void addFront(LIST *l, int i);

int returnFrontNode(LIST *l);

int returnLastNode(LIST *l);

void removeNode(LIST* l, NODE* n);

int returnPrevNode(LIST* l, int i);

int returnNextNode(LIST* l, int i);

NODE* findNode(LIST* l, int val);

#endif
