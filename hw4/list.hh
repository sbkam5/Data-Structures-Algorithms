#if !defined (LIST_HH)
#define LIST_HH

typedef struct node NODE;
typedef struct list LIST;

struct node{
  NODE* next;
  NODE* prev;

  char ch;

};

struct list{
  NODE* first;
  NODE* last;
  NODE* current;
  int length;

};

NODE* makeNode(char c);

LIST* makeList(int N);

void copyString(LIST* l, char*s, int length);

void deleteNode(NODE* n);

void deleteList(LIST* l);

/*-------------------Miscellaneous----------------------*/

void addFront(LIST* l, char i);

void addBack(LIST *l, char i);

void addChar(LIST* l, char c);

void replaceChar(LIST* l, char c);

void deleteChar(LIST* l);

char returnFrontNode(LIST *l);

char returnLastNode(LIST *l);

void removeNode(LIST* l, NODE* n);

#endif
