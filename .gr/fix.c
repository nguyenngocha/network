#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include "gen_valve.h"
void insert_stress(wchar_t *valve);
void insert_stress_end_ptk(wchar_t *valve);
void insert_stress_non_end_ptk(wchar_t *valve);
int  is_end_ptk(wchar_t *valve);
int find_index_to_insert_stress(wchar_t *valve);
void add_element(wchar_t *valve);
void print_array_of_string(int size,int len,wchar_t arrString[size][len]);
void insert_stress_for_all_element();
wchar_t valves_with_stress[1000][5];
int valves_with_stress_size=0;
int main(){
    setlocale(LC_CTYPE, "");
    insert_stress_for_all_element();
    print_array_of_string(valves_with_stress_size,5,valves_with_stress);
    return 0;
}
void insert_stress_for_all_element(){
    int i;
    for(i=0;i<RHYME_SIZE;i++)
        insert_stress(valves[i]);    
}
void print_array_of_string(int size,int len,wchar_t arrString[size][len]){
    int i;
    for(i=0;i<size;i++){
        printf("%ls\n",arrString[i]);
    }
}
void add_element(wchar_t *valve){
    wcscpy(valves_with_stress[valves_with_stress_size],valve);
    valves_with_stress_size++;
}
void insert_stress(wchar_t *valve){
    if(is_end_ptk(valve)){
        insert_stress_end_ptk(valve);
    }else{
        add_element(valve);
        insert_stress_non_end_ptk(valve);
    }
}
void insert_stress_end_ptk(wchar_t *valve){
    wchar_t c;
    int position_replace;
    position_replace = find_index_to_insert_stress(valve);
    c=valve[position_replace];
    switch (c){
        case L'a':
            valve[position_replace]=L'á';
            add_element(valve);
            valve[position_replace]=L'ạ';
            add_element(valve);
            break;
        case L'ă':
            valve[position_replace]=L'ắ';
            add_element(valve);
            valve[position_replace]=L'ặ';
            add_element(valve);
            break;
        case L'â':
            valve[position_replace]=L'ấ';
            add_element(valve);
            valve[position_replace]=L'ậ';
            add_element(valve);
            break;
        case L'e':
            valve[position_replace]=L'é';
            add_element(valve);
            valve[position_replace]=L'ẹ';
            add_element(valve);
            break;
        case L'ê':
            valve[position_replace]=L'ế';
            add_element(valve);
            valve[position_replace]=L'ệ';
            add_element(valve);
            break;
        case L'o':
            valve[position_replace]=L'ó';
            add_element(valve);
            valve[position_replace]=L'ọ';
            add_element(valve);
            break;
        case L'ô':
            valve[position_replace]=L'ố';
            add_element(valve);
            valve[position_replace]=L'ộ';
            add_element(valve);
            break;
        case L'ơ':
            valve[position_replace]=L'ớ';
            add_element(valve);
            valve[position_replace]=L'ợ';
            add_element(valve);
            break;
        case L'i':
            valve[position_replace]=L'í';
            add_element(valve);
            valve[position_replace]=L'ị';
            add_element(valve);
            break;
        case L'u':
            valve[position_replace]=L'ú';
            add_element(valve);
            valve[position_replace]=L'ụ';
            add_element(valve);
            break;
        case L'ư':
            valve[position_replace]=L'ứ';
            add_element(valve);
            valve[position_replace]=L'ự';
            add_element(valve);
            break;
        case L'y':
            valve[position_replace]=L'ý';
            add_element(valve);
            valve[position_replace]=L'ỵ';
            add_element(valve);
    }
}
void insert_stress_non_end_ptk(wchar_t *valve){
    wchar_t c;
    int position_replace;
    position_replace = find_index_to_insert_stress(valve);
    c=valve[position_replace];
    switch (c){
        case L'a':
            valve[position_replace]=L'á';
            add_element(valve);
            valve[position_replace]=L'à';
            add_element(valve);
            valve[position_replace]=L'ã';
            add_element(valve);
            valve[position_replace]=L'ả';
            add_element(valve);
            valve[position_replace]=L'ạ';
            add_element(valve);
            break;
        case L'ă':
            valve[position_replace]=L'ắ';
            add_element(valve);
            valve[position_replace]=L'ằ';
            add_element(valve);
            valve[position_replace]=L'ẵ';
            add_element(valve);
            valve[position_replace]=L'ẳ';
            add_element(valve);
            valve[position_replace]=L'ặ';
            add_element(valve);
            break;
        case L'â':
            valve[position_replace]=L'ấ';
            add_element(valve);
            valve[position_replace]=L'ầ';
            add_element(valve);
            valve[position_replace]=L'ẫ';
            add_element(valve);
            valve[position_replace]=L'ẩ';
            add_element(valve);
            valve[position_replace]=L'ậ';
            add_element(valve);
            break;
        case L'e':
            valve[position_replace]=L'é';
            add_element(valve);
            valve[position_replace]=L'è';
            add_element(valve);
            valve[position_replace]=L'ẽ';
            add_element(valve);
            valve[position_replace]=L'ẻ';
            add_element(valve);
            valve[position_replace]=L'ẹ';
            add_element(valve);
            break;
        case L'ê':
            valve[position_replace]=L'ế';
            add_element(valve);
            valve[position_replace]=L'ề';
            add_element(valve);
            valve[position_replace]=L'ễ';
            add_element(valve);
            valve[position_replace]=L'ể';
            add_element(valve);
            valve[position_replace]=L'ệ';
            add_element(valve);
            break;
        case L'o':
            valve[position_replace]=L'ó';
            add_element(valve);
            valve[position_replace]=L'ò';
            add_element(valve);
            valve[position_replace]=L'õ';
            add_element(valve);
            valve[position_replace]=L'ỏ';
            add_element(valve);
            valve[position_replace]=L'ọ';
            add_element(valve);
            break;
        case L'ô':
            valve[position_replace]=L'ố';
            add_element(valve);
            valve[position_replace]=L'ồ';
            add_element(valve);
            valve[position_replace]=L'ỗ';
            add_element(valve);
            valve[position_replace]=L'ổ';
            add_element(valve);
            valve[position_replace]=L'ộ';
            add_element(valve);
            break;
        case L'ơ':
            valve[position_replace]=L'ớ';
            add_element(valve);
            valve[position_replace]=L'ờ';
            add_element(valve);
            valve[position_replace]=L'ỡ';
            add_element(valve);
            valve[position_replace]=L'ở';
            add_element(valve);
            valve[position_replace]=L'ợ';
            add_element(valve);
            break;
        case L'i':
            valve[position_replace]=L'í';
            add_element(valve);
            valve[position_replace]=L'ì';
            add_element(valve);
            valve[position_replace]=L'ĩ';
            add_element(valve);
            valve[position_replace]=L'ỉ';
            add_element(valve);
            valve[position_replace]=L'ị';
            add_element(valve);
            break;
        case L'u':
            valve[position_replace]=L'ú';
            add_element(valve);
            valve[position_replace]=L'ù';
            add_element(valve);
            valve[position_replace]=L'ũ';
            add_element(valve);
            valve[position_replace]=L'ủ';
            add_element(valve);
            valve[position_replace]=L'ụ';
            add_element(valve);
            break;
        case L'ư':
            valve[position_replace]=L'ứ';
            add_element(valve);
            valve[position_replace]=L'ừ';
            add_element(valve);
            valve[position_replace]=L'ữ';
            add_element(valve);
            valve[position_replace]=L'ử';
            add_element(valve);
            valve[position_replace]=L'ự';
            add_element(valve);
            break;
        case L'y':
            valve[position_replace]=L'ý';
            add_element(valve);
            valve[position_replace]=L'ỳ';
            add_element(valve);
            valve[position_replace]=L'ỹ';
            add_element(valve);
            valve[position_replace]=L'ỷ';
            add_element(valve);
            valve[position_replace]=L'ỵ';
            add_element(valve);
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