#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include "gen_valve.h"
void insert_stress(wchar_t *valve, FILE *f);
void insert_stress_end_ptk(wchar_t *valve, FILE *f);
void insert_stress_non_end_ptk(wchar_t *valve, FILE *f);
int  is_end_ptk(wchar_t *valve);
int find_index_to_insert_stress(wchar_t *valve);
wchar_t valves_with_stress[1000][4];
int main(){
    setlocale(LC_CTYPE, "");
    FILE *newValveFile = fopen("rhymes","w");
    wchar_t valve[6];
    int i;
    for(i=0;i<RHYME_SIZE;i++)
        insert_stress(valves[i],newValveFile);
    fclose(newValveFile);
    return 0;
}
void insert_stress(wchar_t *valve, FILE *f){
    if(is_end_ptk(valve)){
        insert_stress_end_ptk(valve,f);
    }else{
        fwprintf(f,L"%ls\n",valve);
        insert_stress_non_end_ptk(valve,f);
    }
}
void insert_stress_end_ptk(wchar_t *valve, FILE *f){
    wchar_t c;
    int position_replace;
    position_replace = find_index_to_insert_stress(valve);
    c=valve[position_replace];
    switch (c){
        case L'a':
            valve[position_replace]=L'á';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ạ';
            fwprintf(f,L"%ls\n",valve);
            break;
        case L'ă':
            valve[position_replace]=L'ắ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ặ';
            fwprintf(f,L"%ls\n",valve);
            break;
        case L'â':
            valve[position_replace]=L'ấ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ậ';
            fwprintf(f,L"%ls\n",valve);
            break;
        case L'e':
            valve[position_replace]=L'é';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ẹ';
            fwprintf(f,L"%ls\n",valve);
            break;
        case L'ê':
            valve[position_replace]=L'ế';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ệ';
            fwprintf(f,L"%ls\n",valve);
            break;
        case L'o':
            valve[position_replace]=L'ó';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ọ';
            fwprintf(f,L"%ls\n",valve);
            break;
        case L'ô':
            valve[position_replace]=L'ố';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ộ';
            fwprintf(f,L"%ls\n",valve);
            break;
        case L'ơ':
            valve[position_replace]=L'ớ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ợ';
            fwprintf(f,L"%ls\n",valve);
            break;
        case L'i':
            valve[position_replace]=L'í';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ị';
            fwprintf(f,L"%ls\n",valve);
            break;
        case L'u':
            valve[position_replace]=L'ú';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ụ';
            fwprintf(f,L"%ls\n",valve);
            break;
        case L'ư':
            valve[position_replace]=L'ứ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ự';
            fwprintf(f,L"%ls\n",valve);
            break;
        case L'y':
            valve[position_replace]=L'ý';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ỵ';
            fwprintf(f,L"%ls\n",valve);
    }
}
void insert_stress_non_end_ptk(wchar_t *valve, FILE *f){
    wchar_t c;
    int position_replace;
    position_replace = find_index_to_insert_stress(valve);
    c=valve[position_replace];
    switch (c){
        case L'a':
            valve[position_replace]=L'á';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'à';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ã';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ả';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ạ';
            fwprintf(f,L"%ls\n",valve);
            break;
        case L'ă':
            valve[position_replace]=L'ắ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ằ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ẵ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ẳ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ặ';
            fwprintf(f,L"%ls\n",valve);
            break;
        case L'â':
            valve[position_replace]=L'ấ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ầ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ẫ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ẩ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ậ';
            fwprintf(f,L"%ls\n",valve);
            break;
        case L'e':
            valve[position_replace]=L'é';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'è';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ẽ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ẻ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ẹ';
            fwprintf(f,L"%ls\n",valve);
            break;
        case L'ê':
            valve[position_replace]=L'ế';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ề';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ễ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ể';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ệ';
            fwprintf(f,L"%ls\n",valve);
            break;
        case L'o':
            valve[position_replace]=L'ó';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ò';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'õ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ỏ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ọ';
            fwprintf(f,L"%ls\n",valve);
            break;
        case L'ô':
            valve[position_replace]=L'ố';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ồ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ỗ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ổ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ộ';
            fwprintf(f,L"%ls\n",valve);
            break;
        case L'ơ':
            valve[position_replace]=L'ớ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ờ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ỡ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ở';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ợ';
            fwprintf(f,L"%ls\n",valve);
            break;
        case L'i':
            valve[position_replace]=L'í';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ì';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ĩ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ỉ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ị';
            fwprintf(f,L"%ls\n",valve);
            break;
        case L'u':
            valve[position_replace]=L'ú';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ù';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ũ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ủ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ụ';
            fwprintf(f,L"%ls\n",valve);
            break;
        case L'ư':
            valve[position_replace]=L'ứ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ừ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ữ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ử';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ự';
            fwprintf(f,L"%ls\n",valve);
            break;
        case L'y':
            valve[position_replace]=L'ý';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ỳ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ỹ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ỷ';
            fwprintf(f,L"%ls\n",valve);
            valve[position_replace]=L'ỵ';
            fwprintf(f,L"%ls\n",valve);
    }
}

int is_end_ptk(wchar_t *valve){
    int len=wcslen(valve);
    switch(valve[len-1]){
        case L'p':
            return 1;
        case L't':
            return 1;
        case L'c':
            return 1;
        case L'h':
            if(valve[len-2]==L'c')
                return 1;
        default:
            return 0;
    }
}
int find_index_to_insert_stress(wchar_t *valve){
    int len=wcslen(valve);
    switch(len){
        case 2:
            if(valve[len-1]==L'ơ'||valve[len-1]==L'ê')
                return 1;
        case 1:
            return 0;
        case 3:
            if(valve[len-1]==L'h'||valve[len-1]==L'g')
                return 0;
            return 1; 
        case 4:
            if(valve[len-1]!=L'h'&&valve[len-1]!=L'g')
                return 2;
            return 1; 
    }
}