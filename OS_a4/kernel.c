
//Sir, i am a M1 mac user and i was unable to compile on my own so with 
//the help of the tuts i wrote this code which will go when the kernel will compile 
//i have mailed you but to avail no reply so please consider this

#include <linux/semaphore.h>

struct semaphore stack_full;
struct semaphore stack_empty;
struct semaphore lock;
static long buffer[5];
static int f = 0;
SYSCALL_DEFINE1(writer , long , send){
    long buffe = (long*)kmalloc(5* sizeof(long), GFP_KERNEL);
    if(f == 0){
        sema_init(&stack_full , 0);
	    sema_init(&stack_empty , 5);
	    sema_init(&lock , 1);
    }
    down(&stack_empty);
    down(&lock);
    buffer[f] = send;
    f = (f+1) % 5;
    up(&lock);
    up(&stack_full);
    return 0;
}
static int u = 0;
SYSCALL_DEFINE1(reader , long , recieve){
    down(&stack_full);
    down(&lock);
    recieve = buffer[u];
    u = (u+1) % 5;
    up(&lock);
    up(&stack_empty);
    return 0;
}