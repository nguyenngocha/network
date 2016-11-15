#include<stdio.h>
#include<string.h>
char str_arr [30000][9],str_arr2[30000][9];
void catchuoi (char *s){
    int i=0;
    while(s[i]!='\0'){
        if(s[i]=' '){
            s[i]='\0';
        }
    }
}
int find_in_array_file_full(char * string){
    int i,flag=0;
    for(i=0;i<21648;i++){
        if(strcmp(str_arr[i],string)==0){
            flag=1;
        }
    }
    if(flag==0){
        printf("%s\n",string);
    }
}

int main(){
    char s[256];
    FILE *full = fopen("Full_vi","r");
    FILE *me = fopen("ok","r");
    int meSize=0,fullSize=0;
    int len
    while(1){
        fgets(s,256,me);
        if(feof(me))
            break;
        s[strlen(s)-1]='\0';
        strcpy(str_arr2[meSize],s);
        meSize++;
    }
    int i;
    for(i=0;i<meSize;i++){
        printf("%s\n",str_arr2[i]);
    }
    // while(1){
    //     fgets(s,256,full);
    //     if(feof(full))
    //         break;
    //     catchuoi(s);
    //     strcpy(str_arr[fullSize],s);
    //     fullSize++;
    // }
    // int i;
    // for(i=0;i<meSize;i++){
    //     find_in_array_file_full(str_arr2[i]);
    // }
    fclose(full);
    fclose(me);
}
