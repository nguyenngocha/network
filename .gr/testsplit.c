#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#define CONSONANTS_SIZE 27
#define RHYME_SIZE 171

wchar_t phone_rhymes[RHYME_SIZE][8];
wchar_t phone_consonants[CONSONANTS_SIZE][8];
wchar_t consonants[CONSONANTS_SIZE][4];
wchar_t rhymes[RHYME_SIZE][5];
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

int read_file(FILE *f, wchar_t *string1, wchar_t *string2){
		wchar_t string;
		fgetws(string,256,f);
		if(feof(f))
			return 0;
		wcscpy(string2,string);
		string2[wcslen(string2)-1]='\0';
		wcscpy(string1,split(&string2,L' '));
		printf("%ls\n",string2);
		printf("%ls\n",string1);
		return 1;
}

void store_consonents_rhymes(){
	FILE *f = fopen("rhymes_phone","r");
	wchar_t string1[256], string2[256];
	while(1){
		if(!read_file(f,rhymes[],string2)){
			break;
		}
	}	
}
int main(){
    setlocale(LC_CTYPE, "");
	FILE *f = fopen("Full_vi","r");
	wchar_t string1[256], string2[256];
	while(1){
		if(!read_file(f,string1,string2)){
			break;
		}
	}	
	read_file(f,string1,string2);
}
