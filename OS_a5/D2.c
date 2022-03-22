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
//0=finding  bowl
//1=eating 
int phil_ids[5] = {0,1,2,3,4};
//this is a counting semaphore which will represent the four bowls
sem_t bowls;

int Left(int phil_id){
    return (phil_id + 4) % num;
}
int Right(int phil_id){
    return (phil_id + 1) % num;
}

void find_bowl(int phil_id){
    printf("Philosopher %d needs food\n",phil_id);
    phil_state[phil_id] =-1;
    if(phil_state[phil_id]==-1 && phil_state[Left(phil_id)]!=1 && phil_state[Right(phil_id)]!=1){
        phil_state[phil_id]=1;
        sleep(2);
        printf("Philosopher %d has eaten\n",phil_id);
        sem_post(&bowls);
        printf("Philosopher %d has taken the bowl\n",phil_id);
        printf("Philosopher %d has eaten\n",phil_id);
    }
    sem_wait(&bowls);
    sleep(1);
}

void give_bowl(int phil_id){
    phil_state[phil_id]=0;
    printf("Philosopher %d is thinking\n", phil_id);
    //checking for the Left(phil_id)
    phil_id=Left(phil_id);
    if(phil_state[phil_id]==-1 && phil_state[Left(phil_id)]!=1 && phil_state[Right(phil_id)]!=1){
        phil_state[phil_id]=1;
        sleep(2);
        printf("Philosopher %d is eating\n",phil_id);
        sem_post(&bowls);
        printf("Philosopher %d has taken the bowl\n",phil_id);
        printf("Philosopher %d has eaten\n",phil_id);
    }

    //checking for the Right(phil_id)
    phil_id=Right(phil_id);
    if(phil_state[phil_id]==-1 && phil_state[Left(phil_id)]!=1 && phil_state[Right(phil_id)]!=1){
        phil_state[phil_id]=1;
        sleep(2);
        printf("Philosopher %d has eaten\n",phil_id);
        sem_post(&bowls);
        printf("Philosopher %d has taken the bowl\n",phil_id);
        printf("Philosopher %d has eaten\n",phil_id);
    }
    
}

void* phily(int* n){
    for(int* i=n;;){
        sleep(1);
        find_bowl(*i);
        sleep(0);
        give_bowl(*i);
    }
}

int main(){
    pthread_t thread_id[num];
    // initializing the semaphore
    sem_init(&bowls, 0,4);
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