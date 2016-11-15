#include "stdio.h"
#include "string.h"
#include "stdlib.h"
void combine(char buff[],char *c,int n){
    int start=strlen(buff);
    int stop= start+n,i;
    for(i=start;i<stop;i++){
        buff[i]=c[i-start];
    }
    buff[i]='\0';
}
char * split(char *buff[], char symbol){
  char *temp = (char *)malloc(1000*sizeof(char));
  int i=0;
  while(**buff!=symbol&&**buff!='\0'){
    temp[i]=**buff;
    *buff=*buff+1;
    i++;
  }
  (*buff)++;
  temp[i]='\0';
  return temp;
}

int main(){
    int n;
    char t1[14],t2[14],c[1000],*test=(char*)malloc(2000*sizeof(char));
    FILE *f1,*f2;
    printf("\n TEP NGUON: ");
    gets(t1);
    printf("\n TEP DICH: ");
    gets(t2);
    f1=fopen(t1,"rb");
    if(f1==NULL){printf("File khong ton tai\n");}else{
        f2=fopen(t2,"wb");
        while((n=fread(c,1,1000,f1))>0){
            printf("vao\n");
            strcpy(test,"1|asdf|");
            // printf("%s\n",c);
            printf("ok\n");
            combine(test,c,n);
            printf("%d\n",strlen(test));
            split(&test,'|');
            split(&test,'|');
            // printf("%s\n",test);
            printf("cat xong\n");
            fwrite(test,1,n,f2);
            printf("ghi file xong\n");
        }
        printf("sadfasdfsfbsahfbasjnbgkjnajskdfnakgnj\n");
        fclose(f1);
        fclose(f2);
    }
    return 0;
}

// #include "stdio.h"
// int main(){
//     int n;
//     char t1[14],t2[14],c[1000];
//     FILE *f1,*f2;
//     printf("\n TEP NGUON: ");
//     gets(t1);
//     printf("\n TEP DICH: ");
//     gets(t2);
//     f1=fopen(t1,"r");
//     if(f1==NULL){printf("File khong ton tai\n");}else{
//         f2=fopen(t2,"w");
//         while(1){
//             fgets(c,256,f1);
            
//             if(feof(f1)) break;
//             printf("%s\n",c);
//             fprintf(f2,"%s",c);
//         }
//         fclose(f1);
//         fclose(f2);
//     }
//     return 0;
// }