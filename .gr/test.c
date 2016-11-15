#include<iostream>
#include<string>
// #include<stdlib>
// #include <cstring.h>
// dau vao la 2 string, string muc tieu se duoc copy ra 2 ban va free string cu~,
// string ms dc cap phat lai. 
// lam viec nay de khi string ms dai` ra k chen` vao vung` nho' cua thang khac.
//
// void insertString(char **string, char *string1, int position,int newLengh){
//     int len =strlen(*string);
//     char *s = (char*) malloc(len*sizeof(char)),*position_to_end;
//     strcpy(s,*string);
//     free(*string);
//     strncpy(position_to_end,s+position,len-position);// cho nay de len cung dc neu de thi k mat phep tinh tru`, nhung ton bo nho' khi o trong ham.
    
// }
// wstring Replace(const wstring& orig,const wstring& fnd, const wstring& repl)
// {
//     ret = orig;
//     size_t pos = 0;

//     while(true)
//     {
//         pos = ret.find(fnd,pos);
//         if(pos == wstring::npos)  // no more instances found
//             break;

//         ret.replace(pos,pos+fnd.size(),repl);  // replace old string with new string
//         pos += repl.size();
//     }

//     return ret;
// }
int main(){
    setlocale(LC_ALL,"");
    wstring foo = L"This is a test.  Is this a test?";
    // foo = Replace(foo,L"is",L"WOW");
    cout << foo;
    // char *s,s2[30],*s1;
    // s = (char*) malloc(30*sizeof(char));
    // strcpy(s,"asdfasdf");
    // s1=strncpy(s2,s,3);
    // free(s);
    // printf("%s\n",s2);
    // printf("%s\n",s1);
    // printf();
}