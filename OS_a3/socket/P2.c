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

int main(){
    struct sockaddr_un srvr;
    int ret;
    int P2_sock;
    int acc;
    char buffer[buff];
    int ids[5];
    int h;

    unlink(sctr);
    P2_sock = socket(AF_UNIX, SOCK_STREAM, 0);
    memset(&srvr, 0, sizeof(struct sockaddr_un));
    srvr.sun_family = AF_UNIX;
    strncpy(srvr.sun_path, sctr, sizeof(srvr.sun_path) - 1);
    ret = bind(P2_sock, (const struct sockaddr *) &srvr,sizeof(struct sockaddr_un));
    ret = listen(P2_sock,1);
    acc = accept(P2_sock, NULL, NULL);
    int n=0;

    while(n<50){
        //for recieving
        printf("recieving...\n");
        memset(buffer, 0, sizeof(buffer));
        memset(ids,0,sizeof(ids));
        read(acc, buffer,sizeof(buffer));
        read(acc, ids,sizeof(ids));
        printf("received\n");
        for(int i=0;i<5;i++){
            printf("%c[%d]\n",buffer[i],ids[i]);
        }

        //for sending
        h = ids[4];
        char snd[10];
        printf("sending the mssg...\n");
        printf("sent\n");
        sprintf(snd, "%d", h);
        ret = write(acc,snd,sizeof(snd));
        sleep(3);
    }
    close(acc);
    close(P2_sock);
    unlink(sctr);
}