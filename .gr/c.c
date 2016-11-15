#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include "gen_consonant.h"
#include "gen_vowel.h"
int main(){
    wchar_t s[256];
    FILE *f = fopen("1.txt","r");
    while(1){
        fgetws(s,256,f);
        if(feof(f)){
            break;
        }
        printf("%ls\n",s);
    }
    fclose(f);
}