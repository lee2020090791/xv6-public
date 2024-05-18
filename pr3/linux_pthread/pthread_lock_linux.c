#include <stdio.h>
#include <pthread.h>

#define NUM_ITERS 10
#define NUM_THREADS 10

int shared_resource = 0;
int turn=0;
int flag[NUM_THREADS];
int n=0;



void lock();
void unlock();

void lock(int tid)
{
    int j;
    do{ // flag 0 for lv1, flag 1 for finish cs, flag 2 for ready to enter cs(lv2)
        // lv1
        flag[tid]=0; 
        while(turn!=tid){
            if(flag[turn]==1){
                turn = tid;
            }
        }
        //lv2
        flag[tid]=2;
        j=0;
        while((j<n)&&(j==tid||flag[j]!=2)){ // check other thread is in lv2
            j=j+1;
        }
    } while(j<n);    
}

void unlock(int tid)
{
    flag[tid]=1;
}

void* thread_func(void* arg) {
    n++;
    int tid = *(int*)arg;
    lock(tid);
    
    for(int i = 0; i < NUM_ITERS; i++)    shared_resource++;
    
    unlock(tid);
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int tids[NUM_THREADS];
    
    for (int i = 0; i < NUM_THREADS; i++) {
        tids[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &tids[i]);
    }
    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        n--;
    }

    printf("shared: %d\n", shared_resource);
    
    return 0;
}