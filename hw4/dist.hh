#if !defined(DIST_HH)
#define DIST_HH

typedef struct cost COST;

struct cost{
  int tot_cost;
  int cost;
  int s1;
  int s2;
  COST* prev;
  COST* next;
};

int distance(char* s1, char* s2, int m, int n);

void dis_dynamic(char* s1, char* s2, int m, int n, COST** solutions);

void min(int pos_1, int pos_2, COST** solutions,  int replace, int remove, int add);

#endif
