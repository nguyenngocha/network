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
wchar_t * split(wchar_t *buff[], wchar_t symbol){
  wchar_t *temp = (wchar_t *)malloc(1000*sizeof(wchar_t));
  int i=0;
  if(**buff==L'\0')
  	return NULL;
  while(**buff!=symbol&&**buff!=L'\0'){
    temp[i]=**buff;
    *buff=*buff+1;
    i++;
  }
  if(**buff!=L'\0')
	  (*buff)++;
  temp[i]='\0';
  return temp;
}
void replace_one_char_with_string(wchar_t *string, wchar_t *result_string, wchar_t symbol_be_replace, wchar_t *string_replace){
	wchar_t *temp_string=(wchar_t*)malloc(SYLLABLE_MAX_LENGH*sizeof(wchar_t)),*split_result; // cho nay cap phat hoi thua, sau tinh toan ki hon
	wcscpy(temp_string,string);
	wcscpy(result_string,L"");
	while((split_result = split(&temp_string,symbol_be_replace))!=NULL){
		wcscat(result_string,split_result);
		wcscat(result_string,string_replace);
		free(split_result);
	}
	result_string[wcslen(result_string)-1]=L'\0';
}
wchar_t * convert_tone(wchar_t *tone){

}

int main(){
	wchar_t string [] = L"k-i-e-n", result_string [100];
	replace_one_char_with_string(string,result_string,L'-',L"1-");
	printf("%ls\n",result_string );
	return 0;
}