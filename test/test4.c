#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
    int i;
    printf("hello");
    for (i=0; i<80; i++)
    {
      printf("\b");
    }
    printf("bye\n");
    // printf("%c[2K", 27);
for( i=0;i<=100;i++) printf("\rRecived: %d\%",i);
printf("\n");    
}