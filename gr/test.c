
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#define SYLLABLE_MAX_LENGH 16
#define RHYME_WITH_TONE_MAX_LENGH 5
#define PHONE_RHYME_MAX_LENGH 12
#define PHONE_CONSONANT_MAX_LENGH 4
#define RHYME_MAX_LENGH 5
#define CONSONANT_MAX_LENGH 4
#define PHONE_RHYME_WITH_TONE_MAX_LENGH 15
#define PHONE_SYLLABEL_MAX_LENGH PHONE_CONSONANT_MAX_LENGH+PHONE_RHYME_WITH_TONE_MAX_LENGH-1
#define SYLLABLE_MAX_SIZE 30000
#define RHYME_WITH_TONE_MAX_SIZE 1000
#define RHYME_MAX_SIZE 300
#define CONSONANT_MAX_SIZE 100
#define TRICKY_MAX_SIZE 50
#define TRICKY_DESTINY_MAX_LENGH 5
#define TRICKY_SOURCE_MAX_LENGH 5
#define TRICKY_SOURCE_OTHER_FORM_MAX_LENGH TRICKY_SOURCE_MAX_LENGH+2
#define TRICKY_DESTINY_OTHER_FORM_MAX_LENGH TRICKY_DESTINY_MAX_LENGH+2
void split_tone_xampa(wchar_t *string, wchar_t * result){
    int len = wcslen(string);
    result[0] = string[len-2];
    result[1] = string[len-1];
    result[2] = L'\0';
    string[len-3]=L'\0'; // len-3 la vi tri dau cach cuoi cung
}
void replace_one_char_with_one_char(wchar_t *string, wchar_t symbol_be_replace, wchar_t symbol_replace){
    while(*string!=L'\0'){
        if(*string==symbol_be_replace)
            *string = symbol_replace;
        string++;
    }
}
// wchar_t * split(wchar_t *buff[], wchar_t symbol){// neu lam kieu nay thi dau cua mang se bi dich chuyen va den 1 luc nao do no se k con o nao de ghi vao nua.
//   wchar_t *temp;
//   int i=0;
//   temp=*buff;
//   while(**buff!=symbol&&**buff!=L'\0'){
//     (*buff)++;
//   }
//   *buff[0]=L'\0';
//   printf("%ls\n",temp);
//   (*buff)++;
//   return temp;
// }

wchar_t* split(wchar_t *buff, wchar_t symbol){
    if(buff==L'\0')
        return NULL;
    while(*buff!=symbol&&*buff!=L'\0')
        buff++;
    *buff=L'\0';
    buff++;
    return buff;
}
void print_result_xampa_festival_to_file( void (*split_tone)(wchar_t *,wchar_t *),char *source, char *destiny){
    FILE *source_file = fopen(source,"r"),*destiny_file=fopen(destiny,"w");
    wchar_t *syllable=(wchar_t*)malloc(256*sizeof(wchar_t)),*phone_syllable,tone[3];
    while(fgetws(syllable,256,source_file)){
        syllable[wcslen(syllable)-1]=L'\0';
        phone_syllable=split(syllable,L' ');
        split_tone(phone_syllable,tone);
        replace_one_char_with_one_char(phone_syllable,L'-',L' ');
        fwprintf(destiny_file,L"(\"%ls\" nil ((( %ls ) %ls)) )\n",syllable,phone_syllable,tone);
    }
    fclose(source_file);
    fclose(destiny_file);
}
// void print_result_xampa_festival_to_file(char *source, char *destiny){
//     FILE *source_file = fopen(source,"r"), *destiny_file=fopen(destiny,"w");
//     wchar_t *string=(wchar_t*)malloc(256*sizeof(wchar_t)),syllable[SYLLABLE_MAX_LENGH],phone_syllable_tricky[PHONE_SYLLABEL_MAX_LENGH+15];
//     wchar_t tricky_be_replace[TRICKY_SOURCE_MAX_LENGH+2];
//     int i;
//     while(fgetws(string,256,source_file)){
//         string[wcslen(string)-1]=L'\0';
//         wcscpy(syllable,split(&string,L' '));
//         wcscpy(phone_syllable_tricky,string);
//         // for(i=0;i<tricky_size;i++){
//             // wcscpy(phone_syllable_tricky,replace_all_string_with_string(phone_syllable_tricky, tricky_source_other_form[i],tricky_destiny_other_form[i]));
//         // }
//         // fwprintf(destiny_file,L"%ls %ls\n",syllable,phone_syllable_tricky);
//     }
//     fclose(source_file);
//     fclose(destiny_file);
// }
/*void print_result_xampa_festival_to_file(char *source, char *destiny, void (*split_tone)(wchar_t *,wchar_t *)){
    FILE *source_file = fopen(source,"r"), *destiny_file=fopen(destiny,"w");
    wchar_t *string=(wchar_t*)malloc(256*sizeof(wchar_t)),*syllable,*phone_syllable,tone[3],*p;
    while(fgetws(string,256,source_file)!=NULL){
        // printf("ok1\n");
        string[wcslen(string)-1]=L'\0';
        // printf("%ls\n",string);
        p=wcsstr(string,L" ");
        if(p){
            wmemcpy(syllable, string, p-string);
            // syllable[p-string] = L'\0';
            // phone_syllable=p+1;
        }
  //       p = wcsstr (phone_syllable,L"-");
  // wcsncpy (p,L"-",1);
  // wprintf (L"%ls\n",phone_syllable);
        // // wcscpy(syllable,split(&string,L' '));
        // // wcscpy(phone_syllable,string);
        // replace_one_char_with_one_char(phone_syllable,L'-',L' ');
        // split_tone(phone_syllable,tone);
        // printf("(\"%ls\" nil ((( %ls ) %ls)) )\n",syllable,phone_syllable,tone);
        // fwprintf(destiny_file,L"(\"%ls\" nil ((( %ls ) %ls)) )\n",syllable,phone_syllable,tone);
        // printf("ok\n");
    }
    printf("ok\n");
    // free(string);
    fclose(source_file);
    fclose(destiny_file);
}*/
int main(){
    setlocale(LC_CTYPE, "");
    // store_consonants_rhymes();
    // remove_q_from_initial_consonants();
    // insert_tone_and_join_for_all_element();
    // add_exeception_of_literal_y();
    // printf_result_to_file("result_xampa");
    // read_file_tricky_phone();
    // convert_tricky_to_other_form(TRICKY_MAX_SIZE,TRICKY_SOURCE_OTHER_FORM_MAX_LENGH,tricky_source_non_festival,TRICKY_SOURCE_MAX_LENGH,tricky_source,L"-");//convert source
    // convert_tricky_to_other_form(TRICKY_MAX_SIZE,TRICKY_SOURCE_OTHER_FORM_MAX_LENGH,tricky_destiny_non_festival,TRICKY_DESTINY_MAX_LENGH,tricky_destiny,L"-");//convert destiny
    // convert_result_to_tricky_phone("result_xampa","result_tricky_xampa",TRICKY_MAX_SIZE,TRICKY_SOURCE_OTHER_FORM_MAX_LENGH,tricky_source_non_festival,TRICKY_DESTINY_OTHER_FORM_MAX_LENGH,tricky_destiny_non_festival);
    print_result_xampa_festival_to_file(split_tone_xampa,"result_xampa","result_festival");
    // print_result_xampa_festival_to_file(split_tone_xampa,"result_tricky_xampa","result_tricky_festival");
    return 0;
}