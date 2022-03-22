#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

int main(){
    int fd;
    mkfifo("./FIFO2",0777);
    printf("recieving...\n");
    char *c = (char *) calloc(1000, sizeof(char));
    int n=0;
    while(n<50){
        // for recieving the string array
        char *value;
        char *str;
        char *temp;
        char s[50]={};
        fd = open("./FIFO1", O_RDONLY);
        read(fd,c,1000);
        value = strtok(c,"\n");
        for(int i=0; i<4; i++){
            printf( "%s\n", value );
            value = strtok(NULL,"\n");
            str=value;
        }
        printf( "%s\n", value );
        str=strtok(str,"[");
        str=strtok(NULL,"[");
        temp=str;
        str=strtok(temp,"]");
        n=atoi(temp);
        sprintf(s, "%d",n);
        close(fd);
        sleep(3);
        
        // for sending the highest index
        int fd2 = open("./FIFO2", O_WRONLY);
        printf("sending the message...\n");
        write(fd2,&s,sizeof(s));
        printf("sent\n");
    } 
    close(fd);
    return 0;
}