#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>  // for sleep
#include <time.h>

#define N 100

struct item* items[N];
int count = 0;
int sequence = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

int generate_sequence(){
    return sequence++;
}

struct item {
    int seq;
};

struct item* produce_item() {
    struct item* created = NULL;
    created = malloc(sizeof(struct item));
    created->seq = generate_sequence();
    return created;
}


void* producer(void* arg) {
    int thread_num = *((int*)arg);  // Extract thread number from the argument

    while (1) {
        struct item* new_item = produce_item();

        pthread_mutex_lock(&mutex);
        while (count == N) {
            pthread_cond_wait(&empty, &mutex);
        }

       
        items[count] = new_item;
        printf("Producer %d: 아이템 추가 %d, 현재 아이템 수 %d \n", thread_num, items[count]->seq, count+1);
        count = count + 1;
      

        if (count == 1) {
            pthread_cond_signal(&full);
        }

        pthread_mutex_unlock(&mutex);


    }
}


void* consumer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (count == 0) {
            pthread_cond_wait(&full, &mutex);
        }
   
        struct item* new_item = items[--count];
        printf("아이템 사용 %d\n", new_item->seq);
        free(new_item);
    

        if (count >= N-1) {
            pthread_cond_signal(&empty);
        }

        pthread_mutex_unlock(&mutex);
    }
}



int main(void) {
    pthread_t producer_thread, consumer_thread, producer_thread_second, consumer_thread_second;

    int producer_thread_num = 1;
    if (pthread_create(&producer_thread, NULL, producer, (void*)&producer_thread_num) != 0) {
        fprintf(stderr, "Failed to create producer thread.\n");
        return 1;
    }

    int producer_thread_num_second = 2;
    if (pthread_create(&producer_thread_second, NULL, producer, (void*)&producer_thread_num_second) != 0) {
        fprintf(stderr, "Failed to create producer thread.\n");
        return 1;
    }
    if (pthread_create(&consumer_thread_second, NULL, consumer, NULL) != 0) {
        fprintf(stderr, "Failed to create consumer thread.\n");
        return 1;
    }
    if (pthread_create(&producer_thread_second, NULL, consumer, NULL) != 0) {
        fprintf(stderr, "Failed to create consumer thread.\n");
        return 1;
    }

    // Wait for threads to finish (which will never happen in this example)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}
