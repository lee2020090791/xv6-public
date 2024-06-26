#include <stdio.h>
#include <pthread.h>

#define NUM_ITERS 10
#define NUM_THREADS 10

int shared_resource = 0;
int turn=0;
int flag[NUM_THREADS];
int flag2[NUM_THREADS];
int n=0;



void lock();
void unlock();

void lock(int tid)
{
    n++;
    int i;

    while(1){ 
        
        flag[tid]=1; 
        while(turn!=tid){
            if(flag[turn]==0){
                turn = tid;
            }
        }
        ////////////////////////////
        for(int j=0;j<NUM_THREADS;j++){
            flag2[j]=0;
        }
        flag2[tid]=1;
        i=0;
        while((i<n)){ // check other thread is in 2nd block
            if(i==tid || flag2[i]!=1){ // i!=tid&flag2[i]=1 means other thread is in block
                i++;
                continue;
            }
            break;
        }
        if(i==n){
            break;
        }
    }   
}

void unlock(int tid)
{
    flag[tid]=0;
}

void* thread_func(void* arg) {
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