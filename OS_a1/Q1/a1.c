#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
int main(){
    int count=0;
    int A = 0;
    float a[]={0.0,0.0,0.0,0.0,0.0,0.0};
    float b[]={0.0,0.0,0.0,0.0,0.0,0.0};
    int file;
    int file2;
    int s;
    char *c = (char *) calloc(1000, sizeof(char));
    file = open("student_record.csv", O_RDONLY);
    s = read(file, c, 1000);
    int pid1 = fork();
    if(pid1==-1){
        printf("\nFailed to fork");
        return 1;
    }
    if(pid1==0){
        file2 = open("SectionA.csv", O_WRONLY | O_CREAT);
        write(file2, "\nAverage marks(sec A),", strlen("\nAverage marks(sec A),"));
        write(file2, ",", strlen(","));
        char* token;
        while((token=strtok_r(c,"\n",&c))){
            A++;
            if (A == 1){
                continue;
            }
            char* value = strtok(token, ",");
            value=strtok(NULL, ",");
            int rslt=strcmp(value,"A");
            if(rslt==0){
                count++;
                for(int i=0; i<6;i++){
                    value=strtok(NULL, ",");
                    int x =atoi(value);
                    a[i]=a[i]+x;
                }
            }
        }
        for(int i=0; i<6;i++){
            a[i]=a[i]/count;
            char str[50];
            snprintf(str, 50, "%f,", a[i]); 
            write(file2, str, strlen(str));
        }
        exit(0);
    }
    else{
        waitpid(pid1,NULL,0);
        file2 = open("SectionB.csv", O_WRONLY | O_CREAT);
        write(file2, "\nAverage marks(sec B),", strlen("\nAverage marks(sec B),"));
        write(file2, ",", strlen(","));
        char* token;
        while ((token=strtok_r(c,"\n",&c))){
            A++;
            if (A == 1){
                continue;
            }
            char* value = strtok(token, ",");
            value=strtok(NULL, ",");
            int rslt=strcmp(value,"B");
            if(rslt==0){
                count++;
                for(int i=0; i<6;i++){
                    value=strtok(NULL, ",");
                    int x =atoi(value);
                    b[i]=b[i]+x;
                }
            }
        }
        for(int i=0; i<6;i++){
            b[i]=b[i]/count;
            char str[50];
            snprintf(str, 50, "%f,", b[i]);    
            write(file2, str, strlen(str));
        }
    }
}