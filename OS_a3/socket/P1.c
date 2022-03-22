#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#define buff 100
#define sctr "hello"

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

    printf("Creating the socket...\n");
    struct sockaddr_un clt;
    int P1_sock;
    char buffer[buff];
    int ids[5];
    char h;

    P1_sock = socket(AF_UNIX, SOCK_STREAM, 0);
    memset(&clt,0, sizeof(struct sockaddr_un));
    clt.sun_family = AF_UNIX;
    strncpy(clt.sun_path, sctr, sizeof(clt.sun_path) - 1);
    int cl_ret = connect (P1_sock, (const struct sockaddr *) &clt, sizeof(struct sockaddr_un));
    int n=0;

    while(n<50){
        //for sending the message
        memset(buffer,0,sizeof(buffer));
        memset(ids,0,sizeof(ids));
        for(int i=0; i<5;i++){
            buffer[i]=str[n];
            ids[i]=n;
            n++;
        }
        printf("sending the mssg...\n");
        write(P1_sock,buffer,sizeof(buffer));
        write(P1_sock,ids,sizeof(ids));
        printf("sent\n");
        sleep(3);

        //for recieving the message
        printf("recieving the reply...\n");
        memset(&h,0,sizeof(h));
        read(P1_sock,&h,sizeof(h));
        printf("recieved\n");
        printf("Highest Id is %c\n",h);
    }

    close(P1_sock);
    return 0;
}