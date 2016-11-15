#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
#include <term.h>

void ClearScreen()
  {
  if (!cur_term)
    {
    int result;
    setupterm( NULL, STDOUT_FILENO, &result );
    if (result <= 0) return;
    }

  putp( tigetstr( "clear" ) );
  }
//Chua sau ve convention
char * changeFilename(char *nameI){
    char temp[200],afterPoint[100],*name=nameI;
    int lenCurrentFile = strlen(name);
    int i = lenCurrentFile-1,j=lenCurrentFile-1,k,l;
    while(name[i]!='.'&&i>=0){// tim xem co dau'. hay k
      i--;  
    }
    k=i;
    if(i>=0){
        while(name[k]!='\0'){// lay chuoi ki tu sau dau .
            afterPoint[k-i]=name[k+1];
            k++;
        }
    }
    if(i>0){
        j=i-1;
        while(name[j]!='_'&&j>=0){// tim xem co dau'_trc dau .  hay k
          j--;  
        }
    }else{
        while(name[j]!='_'&&j>=0){// tim xem co dau'_ hay k
          j--;  
        }
    }
    if(j<i&&j>=0){// neu la chuoi co dang *_*.*
        k=i;
        temp[i-j-1]='\0';
        while(i>j+1){// lay chuoi ki tu nam giua _ va .
            temp[i-j-2]=name[i-1];
            i--;
        }
        if((i=atoi(temp))){//neu temp la so !=0
            name[j]='\0';
            sprintf(name,"%s_%d.%s",name,i+1,afterPoint);
        }else{// neu giua dau _ va . k phai la so thi them _1 dang sau
            sprintf(name,"_%s_1.%s",temp,afterPoint);
        }
    }else if(j>=0&&i<0){ // neu la chuoi ki tu co dang *_* va k co dau .
        i=0;
        k=j;
        while(j<lenCurrentFile){//temp la chuoi ki tu sau dau _
            j++;
            temp[i]=name[j];
            i++;
        }
        if((i=atoi(temp))){//neu temp la so !=0
            name[k]='\0';
            sprintf(name,"%s_%d",name,i+1);
        }else{// neu sau dau _ k phai la so thi them _1 dang sau
            sprintf(name,"%s_1",name);
        }
    }else if(i>=0){//neu chuoi co dang .* thi in cai _1 vao cuoi
        name[i]='\0';
        sprintf(name,"%s_1.%s",name,afterPoint);
    }else
        sprintf(name,"%s_1",name);
    return name;
}

// char* changeNameToDifferrent(char *name){
//     while(1){
//         if(checkFileExist(name)){// doi ten file den khi nao k trung thi thoi
//             name=changeFilename(name);
//         }
//         else
//             break;
//     }
//     return name;
// }
char * changeFolderName(char * name){
    int nameSize = strlen(name),i,j,k;
    char temp[256];
    name[nameSize-7]='\0';
    i=strlen(name);
    while(name[i]!='_'&&i>0){
        i--;
    }
    j=strlen(name)-1;
    k=j;
    while(j>i&&j>=0){
        temp[j-i-1]=name[j];
        j--;
    }
    temp[k-i]='\0';
    j=atoi(temp);
    if(j){
        name[i+1]='\0';
        sprintf(name,"%s%d-folder",name,j+1);
    }else{
        if(i>0){
            name[k]='\0';
        }
        sprintf(name,"%s_1-folder",name);
    }
    return name;
}
void main(){
    // system("exit"); 
    ClearScreen();
    char *name=(char*)malloc(256*sizeof(char)), test[256]="Kien hehe sadfasf";
    // strcpy(name,"test.c");
    // changeNameToDifferrent(name);
    // printf("%s\n",name);
    // strcpy(name,"test-folder");
    // changeFolderName(name);
    // printf("%s\n",name);
    // free(name);
    // name=(char*)malloc(256*sizeof(char));
    // strcpy(name,"test-folder");
    // changeFolderName(name);
    // printf("%s\n",name);
    char currentFolder[256]="test-folder", folder[256]="kien-folder",path[256];
    sprintf(path,"%s/%s",currentFolder,folder);
    printf("%s\n",path);
    sprintf(name,"%s",test);
    printf("name is : %s\n",name);
    printf("test is: %s\n",test);
}
