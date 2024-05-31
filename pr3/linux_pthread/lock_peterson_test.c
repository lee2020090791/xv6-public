#include <stdio.h>
#include <pthread.h>

#define NUM_ITERS 10
#define NUM_THREADS 10

int shared_resource = 0;
int turn=0;
int flag[NUM_THREADS];
#define n 10
struct mutex{
    int locked;
    int id;
};
int other[n];


void lock();
void unlock();
int 
checkother(int *other)
{
    for(int i=1;i<n;i++){
        if(flag[other[i]])
            return 1;
    }
    return 0;
}
void giveturn(struct mutex *m)
{
    for(int i=1;i<n;i++){
        if(flag[(m->id+i)%n]){
            turn=(m->id+i)%n;
            break;
        }
    }
}
void lock(struct mutex *m)
{
    int other[n];
    for(int i=1;i<n;i++){
        other[i]=(m->id+i)%n;
    }  
    flag[m->id]=1;
    turn = -1;
    while(checkother(other)&&turn!=m->id){
        
    }
}


void unlock(struct mutex *m)
{
    flag[m->id]=0;
    giveturn(m);
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
    }

    printf("shared: %d\n", shared_resource);
    
    return 0;
}