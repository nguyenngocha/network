#include<stdio.h>
#include<string.h>
int main(){
    char s[30];
    s[0]=-31;
    s[1]=-69;
    s[2]=-128;
    s[3]='\0';
    printf("%s\n",s);
}