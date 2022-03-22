#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/wait.h>

int num =5;
//There will be 5 philosophers
int phil_state[5];
//the state of a philosopher will be defined by -1, 0 or 1 where:
//-1=not eaten
//0=finding fork and bowl
//1=eating 
int phil_ids[5] = {0,1,2,3,4};
//seamaphores represents forks
sem_t forks[5];

int Left(int phil_id){
    return (phil_id + 4) % num;
}
int Right(int phil_id){
    return (phil_id + 1) % num;
}

void find_fork(int phil_id){
    printf("Philosopher %d needs food\n",phil_id);
    phil_state[phil_id] =-1;
    if(phil_state[phil_id]==-1 && phil_state[Left(phil_id)]!=1 && phil_state[Right(phil_id)]!=1){
        phil_state[phil_id]=1;
        sleep(2);
        printf("Philosopher %d has eaten\n",phil_id);
        sem_post(&forks[phil_id]);
    }
    sem_wait(&forks[phil_id]);
    sleep(1);
}

void give_fork(int phil_id){
    phil_state[phil_id]=0;
    printf("Philosopher %d is thinking\n", phil_id);
    //checking for the Left(phil_id)
    phil_id=Left(phil_id);
    if(phil_state[phil_id]==-1 && phil_state[Left(phil_id)]!=1 && phil_state[Right(phil_id)]!=1){
        phil_state[phil_id]=1;
        sleep(2);
        printf("Philosopher %d has eaten\n",phil_id);
        sem_post(&forks[phil_id]);
    }

    //checking for the Right(phil_id)
    phil_id=Right(phil_id);
    if(phil_state[phil_id]==-1 && phil_state[Left(phil_id)]!=1 && phil_state[Right(phil_id)]!=1){
        phil_state[phil_id]=1;
        sleep(2);
        printf("Philosopher %d has eaten\n",phil_id);
        sem_post(&forks[phil_id]);
    }
    
}

void* phily(int* n){
    for(int* i=n;;){
        sleep(1);
        find_fork(*i);
        sleep(0);
        give_fork(*i);
    }
}

int main(){
    pthread_t thread_id[num];
    // initializing the semaphores
    int i=0;
    while(i<num){
        sem_init(&forks[i], 0, 0);
        i++;
    }
    int j=0;
    while(j<num){
        pthread_create(&thread_id[j],NULL,phily,&phil_ids[j]);
        printf("Philosopher %d is thinking\n",phil_ids[j]);
        j++;
    }
    int k=0;
    while(k<num){
        pthread_join(thread_id[k], NULL);
        k++;
    }
    return 0;
}