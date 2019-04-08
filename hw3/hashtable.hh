#if !defined (LIST_HH)
#define LIST_HH

typedef struct hashtable HASHTABLE;
typedef struct node NODE;

struct hashtable{
  NODE* elements;
};

struct node{

  int key;
  int value;
};

HASHTABLE* makeHashTable(int n);

int hash(int n, int key);

int insert(HASHTABLE* h, int n, int key, int data);

int get(HASHTABLE* h, int n, int key);

int remove(HASHTABLE* h, int n, int key);

int probe(HASHTABLE* h, int n, int key);

int getWithIndex(HASHTABLE* h, int i);

int getKeyWithIndex(HASHTABLE* h, int i);

void deleteHashTable(HASHTABLE* h);

#endif
