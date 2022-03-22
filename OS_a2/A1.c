#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

void S1Handler(int sig, siginfo_t *info, void *ucontext){
    int int_val = info->si_value.sival_int;
    printf("value: %d\n",int_val);
    printf("Terminated\n");
    if(sig == SIGTERM){
        return;
    }
}

int main(){
    int pidS1=getpid()+1;
    int pid = fork();
    if (pid < 0){
        return-1;
        printf("Error");
    }
    else if (pid== 0){
        printf("ID of S1: %d\n", pidS1);
        struct sigaction sa;
        sa.sa_sigaction = &S1Handler;
        sa.sa_flags = SA_SIGINFO;
        printf("S1 started\n");
        sigaction(SIGTERM, &sa, NULL);
        return 1;
    }
    else{
        wait(NULL);
        int pid2=fork();
        if(pid2<0){
            return-1;
            printf("Error");
        }
        else if (pid2==0){
            char ID[100];
            sprintf(ID, "%d", pidS1);
            execl("./E1","./E1",ID,NULL);
            return 1;
        }
        else{
            wait(NULL);
            int pid3=fork();
            if(pid3<0){
                return-1;
                printf("Error");
                return -1;
            }
            else if (pid3==0){
                char ID[100];
                sprintf(ID, "%d", pidS1);
                execl("./E2","./E2",ID,NULL);
                return 1;
            }
            else{
                wait(NULL);
                return 0;
            }
        }
    }
}