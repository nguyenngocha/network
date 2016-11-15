#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include "gen_vowel_with_stress.h"
#include "gen_consonant.h"
void join_consonant_vowel();
void join_one_time(wchar_t *consonant, wchar_t *vowel);
void join_one_time_with_rule(wchar_t *consonant, wchar_t *vowel);
wchar_t phones[30000][8];
int phones_size=0;
int main(){
    setlocale(LC_CTYPE, "");
    insert_stress_for_all_element();
    join_consonant_vowel();
    print_array_of_string(phones_size,8,phones);
}
void join_consonant_vowel(){
    int i,j;
    for(i=0;i<CONSONANTS_SIZE;i++){
        for(j=0;j<vowels_with_stress_size;j++){
            join_one_time_with_rule(consonants[i],vowels_with_stress[j]);
        }
    }
}
void join_one_time(wchar_t *consonant, wchar_t *vowel){
    wcscpy(phones[phones_size],consonant);
    wcscat(phones[phones_size],vowel);
    phones_size++;
}
void join_one_time_with_rule(wchar_t *consonant, wchar_t *vowel){
    // switch(consonant[0]){
    //     case L'q':
    //         if(vowel[0]==L'u')
    //             join_one_time(consonant,vowel);
    //         break;
    //     case L'n':
    //         if(wcslen(consonant)==3){
    //             if(vowel[0]==L'i'||vowel[0]==L'ê'||vowel[0]==L'e')
    //               join_one_time(consonant,vowel);
    //         }else if(wcslen(consonant)==2){
    //                 if(!(vowel[0]==L'i'||vowel[0]==L'ê'||vowel[0]==L'e'))
    //                  join_one_time(consonant,vowel);
    //         }else {
    //             join_one_time(consonant,vowel);
    //         }
    //         break;
    //     case L'g':
    //         if(wcslen(consonant)==2){
    //             if(consonant[1]==L'h'){
    //                 if(vowel[0]==L'i'||vowel[0]==L'ê'||vowel[0]==L'e')
    //                   join_one_time(consonant,vowel);
    //             }else if(consonant[1]==L'i'){
    //                 if(vowel[0]!=L'i'&&vowel[0]!=L'y')
    //                     join_one_time(consonant,vowel);
    //             }
    //         }else{
    //             join_one_time(consonant,vowel);
    //         }
    //         break;
    //     default:
    //         join_one_time(consonant,vowel);
    // }
}