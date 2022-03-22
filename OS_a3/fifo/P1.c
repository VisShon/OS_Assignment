#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
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
    printf("Crearting the fifo\n");
    mkfifo("./FIFO1",0777);
    int fd; 
    int n=0;
    while(n<50){
        // for sending the string array
        printf("Opening the fifo\n");
        printf("Writing...\n");
        char s[50]={};
        char temp[50]={};
        printf("Sending the string array...\n");
        fd= open("./FIFO1", O_WRONLY);
        for (int j=0;j<5;j++){
            if(j==4){
                sprintf(temp,"%c[%d]\0",str[n],n);
            }
            else{
                sprintf(temp, "%c[%d]\n",str[n],n); 
            }
            strcat(s,temp);
            n++;
        }
        write(fd,s,sizeof(s));
        printf("sent\n");
        sleep(3);
        // for recieving the highest index
        printf("recieving...\n");
        int fd2 = open("./FIFO2", O_RDONLY);
        char *c = (char *) calloc(1000, sizeof(char));
        read(fd2,c,1000);
        printf("Highest Id is  %s\n",c);
        close(fd2);
    }
    return 0;
}