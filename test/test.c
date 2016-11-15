#include<stdio.h>
#include<string.h>
int main(){
    char  error[100];
    system("ls -x");
    // sprintf(error,"%s",system("cd 'New Folder1' && ls -x"));
    printf("%d\n",system("cd 'New Folder1' && ls -x"));
    if(system("cd 'New Folder1' && ls -x")){
        printf("folder not exist\n");
    }else{
        printf("OK\n");
    }
    
    // system("cd 'New Folder' && mkdir test");
    // printf("$%\^&*()=+");
}