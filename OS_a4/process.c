#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <stdbool.h>
#include <stdint.h>
static int error_check(int sys_call_return_value , char * message){
    if(sys_call_return_value < 0){
        perror(message);
        exit(EXIT_FAILURE);
    }
    return sys_call_return_value;
}
void* P(){
    // producer proccess
    long val;
    int rand= open("/dev/urandom", O_RDONLY);
    error_check(rand, "Invalid random number");
    int s =read(rand, &val, 8);
    error_check(s,"unable to read");
    printf("placed %ld in the queue\n",val);
    syscall(449,val);
}
void* C(){
    //cosumer proccess
    long recv_val;
    syscall(450,recv_val);
    printf("removed %ld from the queue\n",recv_val);
}
int main(){
    //main program
    pthread_t producer;
    pthread_t consumer;
    pthread_create(&P,NULL,&producer,NULL);
    pthread_join(producer,NULL);
    pthread_create(&C,NULL,&consumer,NULL);
    pthread_join(consumer,NULL);
    return 0;
}