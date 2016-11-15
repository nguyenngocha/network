#include "stdio.h"
int main(){
    int n;
    char t1[14],t2[14],c[1000];
    FILE *f1,*f2;
    printf("\n TEP NGUON: ");
    gets(t1);
    printf("\n TEP DICH: ");
    gets(t2);
    f1=fopen(t1,"rb");
    if(f1==NULL){printf("File khong ton tai\n");}else{
        f2=fopen(t2,"wb");
        while((n=fread(c,1,1,f1))>0){
            fwrite(c,1,n,f2);
        }
        fclose(f1);
        fclose(f2);
    }
    return 0;
}