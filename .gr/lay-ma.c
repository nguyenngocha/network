#include<stdio.h>
#include<string.h>
int main(){
    //1 chu chiem 3 ô
    // char s[400] = "ỀềỂểỄễỆệỈỉỊịỌọỎỏỐốỒồỔổỖỗỘộỚớỜờỞởỠỡỢợỤụỦủỨứỪừỬửỮữỰựẠạẢảẤấẦầẨẩẪẫẬậẮắẰằẲẳẴẵẶặ",temp[5];//
    // int len = strlen(s),i;
    // printf("%d\n",len);
    // for(i=0;i<len;i+=3){
    //     printf("%d ",temp[0]=s[i]);
    //     printf("%d ",temp[1]=s[i+1]);
    //     printf("%d ",temp[2]=s[i+2]);
    //     temp[3]='\0';
    //     printf("%s\n",temp);
    //     // printf("%s\n",s);
    // }
    
    //1 chữ chiếm 2 ô
    char s[100] = "ƯưƠơŨũĨĩĂăÚÙÕÔÓÒÍÌÊÃÂÁÀúùõôóòíìêãâáà",temp[5];//óòõáàãúùũíìĩ
    int len = strlen(s),i;
    printf("%d\n",len);
    for(i=0;i<len;i+=2){
        printf("%d ",temp[0]=s[i]);
        printf("%d ",temp[1]=s[i+1]);
        // printf("%d\n",temp[2]=s[i+2]);
        temp[2]='\0';
        printf("%s\n",temp);
        // printf("%s\n",s);
    }
    
    //1 chữ chiếm 1 ô
    // char s[100] = "abcdefghiklmnopqrstuvwxyzABCDEFGHIKLMNOPQRSTUVWXYZ",temp[5];//
    // int len = strlen(s),i;
    // printf("%d\n",len);
    // for(i=0;i<len;i++){
    //     printf("%d ",temp[0]=s[i]);
    //     temp[1]='\0';
    //     printf("%s\n",temp);
    //     // printf("%s\n",s);
    // }
}