#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void splitFromEnd(char buff[], char symbol){
  int i=strlen(buff)-1;
  int k=0;
  while(buff[i]!=symbol&&i>0){
    i--;
    k++;
  }
  buff[i]='\0';
}
int main(){
 char test[256]="test-folder/test2-folder/asdf-folder";
 splitFromEnd(test,'/');
 printf("%s\n",test);
 splitFromEnd(test,'/');
 printf("%s\n",test);
 splitFromEnd(test,'/');
 printf("%s\n",test);
    fgets(test, 256 , stdin);
    test[strlen(test)-1]='\0';
    printf("%s\n",test);
}