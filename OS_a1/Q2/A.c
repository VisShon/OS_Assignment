#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
void A()
{
    printf("you are now in A function\n");
    extern void B(int64_t y);
    int64_t y;
    scanf("%d",&y);
    B(y);
}
int main()
{
    A();
    return 0;
}