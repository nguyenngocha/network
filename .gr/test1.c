#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
int main(){
    setlocale(LC_CTYPE, "");
    wchar_t t = L'ê';
    if(t==L'ê')
        printf("ok\n");
    wchar_t consonant[4]=L"gi";
    if(wcscmp(consonant,L"gi")==0) printf("ok\n");
    wchar_t test[30] = L"aớớ",test1[30] = L"aớớ";
    test[0]=L'ế';
    printf("%lc\n",test[0]);
    printf("%lc\n",test[1]);
    printf("%lc\n",test[2]);
    wcscat(test,test1);
    printf("%ls\n",test);
}