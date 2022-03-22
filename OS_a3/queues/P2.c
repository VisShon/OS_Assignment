#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
struct message { 
    long mesg_type; 
    struct data{
        char arr[5];
        int h;
        int ids[5];
    }data;
}ms;
int main(){
    printf("recieving...\n");
    int h=0;
    while(h<50){
        // for recieving the string array
        key_t tok = ftok("smacky",65);
        int Id =msgget(tok,IPC_CREAT|0660);
        msgrcv(Id, &ms, sizeof(ms),1,0); 
        for(int j=0;j<5;j++){
            printf("%c[%d]\n",ms.data.arr[j],ms.data.ids[j]);}
            
        // for sending the highest index
        h=ms.data.ids[4];
        ms.data.h=h;
        printf("sending the mssg...\n");
        printf("sent\n");
        sleep(3);
        msgsnd(Id,&ms,sizeof(ms),0);
    }
    return 0;
}