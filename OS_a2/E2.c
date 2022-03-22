#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include <sys/time.h>

int SPID;
static inline unsigned int rdRand(){
    unsigned int num = 0;
    asm volatile ("RDRAND %%rax":"=r"(num));
    return num;
}

void SRhandler(){
    union sigval value;
    printf("running SRhandler\n");
    printf("ID S1:%d\n",getppid()+1);
    unsigned int randm = rdRand();
    value.sival_int = randm;
    printf("value: %d\n",randm);
    printf("Terminated\n");
    kill(getpid(), SIGTERM);
    sigqueue(SPID,SA_SIGINFO,value);
}

int main(int argc, char*argv[]){
    int ID;
    sscanf(argv[1], "%d", &ID);
    SPID=ID;
    struct itimerval it_val;
    printf("SR started\nID:%d\n",getpid());
    struct sigaction sa;
    sa.sa_sigaction = &SRhandler;
    sigaction(SIGALRM, &sa, NULL);
    it_val.it_value.tv_sec=1;
    it_val.it_value.tv_usec=0;
    it_val.it_interval = it_val.it_value;
    setitimer(ITIMER_REAL, &it_val,0);
    for(;;){
        printf("running main in SR\n");
        sleep(1);
    }
    return 0;
}
