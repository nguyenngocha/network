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
#define PHONE_RHYME_WITH_TONE_MAX_LENGH 13
#define PHONE_SYLLABEL_MAX_LENGH PHONE_CONSONANT_MAX_LENGH+PHONE_RHYME_WITH_TONE_MAX_LENGH-1
#define SYLLABLE_MAX_SIZE 30000
#define RHYME_WITH_TONE_MAX_SIZE 1000
#define RHYME_MAX_SIZE 300
#define CONSONANT_MAX_SIZE 100

wchar_t syllables[SYLLABLE_MAX_SIZE][SYLLABLE_MAX_LENGH];
wchar_t phone_syllables[SYLLABLE_MAX_SIZE][PHONE_SYLLABEL_MAX_LENGH];
wchar_t rhymes_with_tone[RHYME_WITH_TONE_MAX_SIZE][RHYME_WITH_TONE_MAX_LENGH];
wchar_t phone_rhymes[RHYME_MAX_SIZE][PHONE_RHYME_MAX_LENGH];

wchar_t phone_consonants[CONSONANT_MAX_SIZE][PHONE_CONSONANT_MAX_LENGH];
wchar_t consonants[CONSONANT_MAX_SIZE][CONSONANT_MAX_LENGH];
wchar_t rhymes[RHYME_MAX_SIZE][RHYME_MAX_LENGH];
wchar_t q[4], phone_q[4];
int rhyme_size=0;
int consonant_size=0;
int rhymes_with_tone_size=0;
int syllables_size=0;
wchar_t * split(wchar_t *buff[], wchar_t symbol){
  wchar_t *temp = (wchar_t *)malloc(1000*sizeof(wchar_t));
  int i=0;
  while(**buff!=symbol&&**buff!='\0'){
    temp[i]=**buff;
    *buff=*buff+1;
    i++;
  }
  (*buff)++;
  temp[i]='\0';
  return temp;
}
void read_file(FILE *f, int max_size, int max_len1,int max_len2,wchar_t string1[max_size][max_len1], wchar_t string2[max_size][max_len2],int *count){
		wchar_t *string=(wchar_t*)malloc(256*sizeof(wchar_t)),*buff,c;
		while(fgetws(string,256,f)!=NULL){
    		string[wcslen(string)-1]='\0';
    		wcscpy(string1[*count],split(&string,L' '));
    		wcscpy(string2[*count],string);
    		(*count)++;
		}
}
void store_consonants_rhymes(){
	FILE *initial_consonant = fopen("initial_consonants","r");
	FILE *rhyme_phone = fopen("rhymes_phones","r");
    read_file(initial_consonant,CONSONANT_MAX_SIZE,CONSONANT_MAX_LENGH,PHONE_CONSONANT_MAX_LENGH,consonants,phone_consonants,&consonant_size);
    read_file(rhyme_phone,RHYME_MAX_SIZE,RHYME_MAX_LENGH,PHONE_RHYME_MAX_LENGH,rhymes,phone_rhymes,&rhyme_size);
    fclose(initial_consonant);
    fclose(rhyme_phone);
}
void join_one_time(wchar_t *consonant, wchar_t *rhyme){
    wcscpy(syllables[syllables_size],consonant);
    wcscat(syllables[syllables_size],rhyme);
    syllables_size++;
}
void join_one_time_with_rule(wchar_t *consonant,  wchar_t *rhyme, wchar_t *phone_rhyme){
    int len;
    if(wcscmp(consonant,L"q")!=0){
//    	if(rhyme[0]!=L'u'&&phone_rhyme[0]!=L'w'){
			if(wcscmp(consonant,L"gi")==0){
				len = wcslen(rhyme);
				if(rhyme[0]==L'i'){
					if(!(len ==2 &&(rhyme[1]==L'u'||rhyme[1]==L'a'))){
						join_one_time(L"g",rhyme);
					}
				}else{
						join_one_time(consonant,rhyme);
				}
			}
			else{
				if(wcscmp(consonant,L"g")==0){
					if(rhyme[0]!=L'i')
						join_one_time(consonant,rhyme);
				}else{
					if(wcscmp(consonant,L"c")!=0||(rhyme[0]!=L'i'&&rhyme[0]!=L'e'&&rhyme[0]!=L'y'&&(rhyme[0]!=L'u'||phone_rhyme[0]!=L'w')))
						join_one_time(consonant,rhyme);
				}
			}
//    	}
    }else{
    	len = wcslen(rhyme);
    	if(rhyme[0]==L'u'&&len>2){
    		join_one_time(consonant,rhyme);
    	}
    }
}
void add_exeception_of_literal_y(){
	int i;
	wchar_t temp_rhyme[RHYME_MAX_LENGH];
	for(i=0;i<rhyme_size;i++){
		if(wcscmp(rhymes[i],L"iec")==0||
		   wcscmp(rhymes[i],L"ieng")==0||wcscmp(rhymes[i],L"iet")==0||
		   wcscmp(rhymes[i],L"ien")==0||wcscmp(rhymes[i],L"iep")==0||
		   wcscmp(rhymes[i],L"iem")==0||wcscmp(rhymes[i],L"ieu")==0){
		   wcscpy(temp_rhyme,rhymes[i]);
		   temp_rhyme[0]=L'y';
		   join_one_time(L"",temp_rhyme);
		}
	}
}
void join_all(){
	int i,j;
	for(i=0;i<consonant_size;i++){
		for(j=0;j<rhyme_size;j++){
			join_one_time_with_rule(consonants[i],rhymes[j],phone_rhymes[j]);
		}
	}
}
void printf_result_to_file(char *filename){
	int i;
	FILE *f = fopen(filename,"w");
	for(i=0;i<syllables_size;i++){
		fwprintf(f,L"%ls\n",syllables[i]);
	}
	fclose(f);
}
void add_rhyme(){
	int i;
	for(i=0;i<rhyme_size;i++){
		join_one_time(L"",rhymes[i]);
	}
}
int main(){
    setlocale(LC_CTYPE, "");
    store_consonants_rhymes();
    join_all();
    add_rhyme();
    add_exeception_of_literal_y();
    printf_result_to_file("result");
}
