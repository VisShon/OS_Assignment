#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include <sys/time.h>

int SPID;
typedef unsigned long long uint64;
static unsigned long long rdTsc(){
    uint64 val;
    unsigned int h, l;
    __asm__ __volatile__("rdtsc" : "=a" (l), "=d" (h));
    val = ((uint64)l) | (((uint64)h) << 32);
    return val;
}

void SThandler(){
    union sigval value;
    printf("running SThandler\n");
    printf("ID S1:%d\n",getppid()+1);
    unsigned long long tsc =rdTsc();
    value.sival_int = tsc;
    printf("value: %llu\n",tsc);
    printf("Terminated\n");
    kill(getpid(), SIGTERM);
    sigqueue(SPID,SA_SIGINFO,value);
}

int main(int argc, char*argv[]){
    int ID;
    sscanf(argv[1], "%d", &ID);
    SPID=ID;
    struct itimerval it_val;
    printf("ST started\nID:%d\n",getpid());
    struct sigaction sa;
    sa.sa_sigaction = &SThandler;
    sigaction(SIGALRM, &sa, NULL);
    it_val.it_value.tv_sec=1;
    it_val.it_value.tv_usec=0;
    it_val.it_interval = it_val.it_value;
    setitimer(ITIMER_REAL, &it_val,0);
    for(;;){
        printf("running main in ST\n");
        sleep(1);
    }
    return 0;
}