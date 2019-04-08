/*Header file for Hw 2*/

#if !defined (MAIN_HH)
#define MAIN_HH

typedef struct queue_object QUEUE_OBJECT;
typedef struct queue        QUEUE;

struct queue_object{

  QUEUE_OBJECT* next;
  float value;

};


struct queue{
  QUEUE_OBJECT* head;
  QUEUE_OBJECT* tail;

};

QUEUE* makeQueue(int N);

QUEUE_OBJECT* makeQueueObject(float value);

int enqueue(QUEUE* q, float f);

int dequeue(QUEUE* q);

void deleteQueue(QUEUE* queue);

void deleteQueueObject(QUEUE_OBJECT* object);

#endif
