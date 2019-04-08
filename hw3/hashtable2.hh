#if !defined (HASH_HH)
#define HASH_HH

typedef struct hashtable HASHTABLE;
typedef struct node NODE;

struct hashtable{
  NODE** elements;
};

struct node{
  int key;
  int value;
  NODE* next;
};

HASHTABLE* makeHashTable(int n);

int hash(int n, int key);

int insert(HASHTABLE* h, int n, int key, int data);

int get(HASHTABLE* h, int n, int key);

int remove(HASHTABLE* h, int n, int key);

int probe(HASHTABLE* h, int n, int key);

void deleteHashTable(HASHTABLE* h, int n);

#endif
