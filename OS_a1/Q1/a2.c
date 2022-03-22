#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
float t[] = {0.0,0.0,0.0,0.0,0.0,0.0};
int k;
void* secA(){
    char buffer[1024];
    int count=0;
    int A = 0;
    float a[]={0.0,0.0,0.0,0.0,0.0,0.0};
    int file;
    int f;
    int s;
    char *c = (char *) calloc(1000, sizeof(char));
    file = open("student_record.csv", O_RDONLY);
    f = open("SectionA.csv", O_WRONLY|O_CREAT);
    s = read(file, c, 1000);
    write(f, "\nAverage marks(sec A),", strlen("\nAverage marks(sec A),"));
    write(f, ",", strlen(","));
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
                t[i]=t[i]+x;
            }
        }
    }
    k=k+count;
    for(int i=0; i<6;i++){
        a[i]=a[i]/count;
        char str[50];
        snprintf(str, 50, "%f,", a[i]); 
        write(f, str, strlen(str));
    }
    return(0);
}
void* secB(){
    char buffer[1024];
    int count=0;
    int A = 0;
    float b[]={0.0,0.0,0.0,0.0,0.0,0.0};
    int file;
    int f;
    int s;
    char *c = (char *) calloc(1000, sizeof(char));
    file = open("student_record.csv", O_RDONLY);
    f = open("SectionB.csv", O_WRONLY|O_CREAT);
    s = read(file, c, 1000);
    write(f, "\nAverage marks(sec B),", strlen("\nAverage marks(sec B),"));
    write(f, ",", strlen(","));
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
                t[i]=t[i]+x;                
            }
        }
    }
    k=k+count;
    for(int i=0; i<6;i++){
        b[i]=b[i]/count;
        char str[50];
        snprintf(str, 50, "%f,", b[i]);    
        write(f, str, strlen(str));
    }
    
    return(0);
}
int main(){
    int f;
    pthread_t sA;
    pthread_t sB;
    pthread_create(&sA, NULL, &secA,NULL );
    pthread_join(sA,NULL);
    pthread_create(&sB, NULL, &secB,NULL );
    pthread_join(sB,NULL);
    f = open("Total.csv", O_WRONLY|O_CREAT);
    write(f, "\nAverage marks,", strlen("\nAverage marks,"));
    write(f, ",", strlen(","));
    for(int i=0; i<6;i++){
        t[i]=t[i]/k;
        char str[50];
        snprintf(str, 50, "%f,", t[i]);    
        write(f, str, strlen(str));
    }
}