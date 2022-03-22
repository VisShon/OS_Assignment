#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
struct message { 
    long mesg_type; 
    struct data{
        char arr[5];
        int h;
        int ids[5];
    }data;
}ms;
static char randomString(){
    static char set[] = "abcdefghijklmnopqrstuvwxyz";        
    char str;
    for (int i=0;i<1;i++){            
        int num=rand()%25;
        str=set[num];
    }
    return str;
}
int main(){
    char str[50];
    for(int i=0;i<50;i++){
        str[i]=randomString();
    }
    printf("\n");
    int n=0;
    while(n<50){
        // for sending the string array
        key_t tok = ftok("smacky",65);
        int Id =msgget(tok,IPC_CREAT|0660);
        for(int j=0;j<5;j++){
            ms.data.arr[j]=str[n];
            ms.data.ids[j]=n;
            n++;
        }
        ms.mesg_type=1;
        printf("sending the mssg...\n");
        msgsnd(Id,&ms,sizeof(ms),0);
        printf("sent\n");
        sleep(3);

        // for recieving the highest index
        printf("recieving...\n");
        msgrcv(Id,&ms,sizeof(ms),1,0);
        printf("Highest Id is  %d\n",ms.data.h);
        msgctl(Id,IPC_RMID,NULL);
    }
    return 0;
}