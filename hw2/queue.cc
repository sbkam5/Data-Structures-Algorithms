/*Spencer Kam*/
#include <stdlib.h>
#include <stdio.h>
#include "main.hh"

    QUEUE_OBJECT* makeQueueObject(float value){
      QUEUE_OBJECT* temp = (QUEUE_OBJECT*)malloc(sizeof(QUEUE_OBJECT));

      temp->value = value;
      temp->next = NULL;

    }

    void deleteQueueObject(QUEUE_OBJECT* object){
      object->next = NULL;
      free(object);
    }


    //Constructor
    QUEUE* makeQueue(int N){
      QUEUE *queue = (QUEUE*)malloc(sizeof(QUEUE));;
      QUEUE_OBJECT* temp;

      for(int i = 0; i <= N; i++){
        float random = (i == N)? -1.0 : (float)rand();
        temp = makeQueueObject(random);
        if(i == 0){
          queue->head = temp;
          queue->tail = temp;
        }
        else{
          queue->tail->next = temp;
          queue->tail = temp;
        }
      }
      queue->tail->next = queue->head;  //Once the queue has been created, the tail must point back to the head since the queue is empty.
              //Also, the queue is circular.

      return queue;
    }


    //enqueue method-------------------------
    int enqueue(QUEUE* q, float f){

        //If the end links back to the start of the queue, that means the queue is full.
        if(q->tail->next == q->head){
          return -1;  //returning negative one means failer.
        }

        q->tail->value = f;
        q->tail = q->tail->next;

      return 1;  //1 means successful enqueue.

    }

    //dequeue method-------------------------
    int dequeue(QUEUE* q){
      
        //If the tail and head point to the same location, that means the length of the queue is 0.
        if(q->head == q->tail){
          return -1;
        }

        //First in first out.
        float f = q->head->value;
        q->head = q->head->next;

      return f;  //return the value of the first element.

    }

    //Delete Queue-----------------------------
    void deleteQueue(QUEUE* queue){
      QUEUE_OBJECT* temp1 = queue->head;
      QUEUE_OBJECT* temp2 = NULL;
      int count = 0;

      while(!((temp1 == queue->head)&&(count!=0))){ //keep deleting nodes in the queue until you come right back to the beginning of the queue.
        temp2 = temp1;
        temp1 = temp1->next;

        temp2->next = NULL;
        deleteQueueObject(temp2);
        ++count;
      }

      queue->head = NULL;
      queue->tail = NULL;
      free(queue);

    }


