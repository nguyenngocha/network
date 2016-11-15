#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#define SYLLABLE_MAX_LENGH 16
#define RHYME_WITH_TONE_MAX_LENGH 5
#define PHONE_RHYME_MAX_LENGH 8
#define PHONE_CONSONANT_MAX_LENGH 8
#define RHYME_MAX_LENGH 5
#define CONSONANT_MAX_LENGH 4

#define SYLLABLE_MAX_SIZE 30000
#define RHYME_WITH_TONE_MAX_SIZE 1000
#define RHYME_MAX_SIZE 300
#define CONSONANT_MAX_SIZE 100


void insert_tone_and_join(wchar_t *rhyme);
void insert_tone_and_join_end_ptk(wchar_t *rhyme);
void insert_tone_and_join_non_end_ptk(wchar_t *rhyme);
int  is_end_ptk(wchar_t *rhyme);
int find_index_to_insert_tone_and_join(wchar_t *rhyme);
void add_element(wchar_t first_of_rhyme_non_tone,wchar_t *rhyme);
void print_array_of_string(int size,int len,wchar_t arrString[size][len]);
void insert_tone_and_join_for_all_element();

void join_one_time(wchar_t *consonant, wchar_t *rhyme);
void join_one_time_with_rule(wchar_t *consona, wchar_t first_of_rhyme_non_tone,  wchar_t *rhyme);
void join_consonant_rhyme(wchar_t first_of_rhyme_non_tone,  wchar_t *rhyme);
void add_exeception_of_literal_y();

void store_consonents_rhymes();
void read_file(FILE *f, int max_size, int max_len1,int max_len2,wchar_t string1[max_size][max_len1], wchar_t string2[max_size][max_len2],int *count);
wchar_t * split(wchar_t *buff[], wchar_t symbol);


wchar_t syllables[SYLLABLE_MAX_SIZE][SYLLABLE_MAX_LENGH];
wchar_t rhymes_with_tone[RHYME_WITH_TONE_MAX_SIZE][RHYME_WITH_TONE_MAX_LENGH];
wchar_t phone_rhymes[RHYME_MAX_SIZE][PHONE_RHYME_MAX_LENGH];

wchar_t phone_consonants[CONSONANT_MAX_SIZE][PHONE_CONSONANT_MAX_LENGH];
wchar_t consonants[CONSONANT_MAX_SIZE][CONSONANT_MAX_LENGH];
wchar_t rhymes[RHYME_MAX_SIZE][RHYME_MAX_LENGH];

int rhyme_size=0;
int consonant_size=0;
int rhymes_with_tone_size=0;
int syllables_size=0;
int main(){
    setlocale(LC_CTYPE, "");
    store_consonents_rhymes();
    insert_tone_and_join_for_all_element();
    print_array_of_string(syllables_size,8,syllables);
}

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
		wchar_t *string=(wchar_t*)malloc(256*sizeof(wchar_t)),*buff;
		while(1){
    		fgetws(string,256,f);
    		if(feof(f))
                return;
    		string[wcslen(string)-1]='\0';
    		wcscpy(string1[*count],split(&string,L' '));
    		wcscpy(string2[*count],string);
    		printf("%ls\n",string2[*count]);
    		printf("%ls\n",string1[*count]);
    		*count++;
		}
}

void store_consonents_rhymes(){
	FILE *initial_consonant = fopen("initial_consonant","r");
	FILE *rhyme_phone = fopen("rhyme_phone","r");
    read_file(initial_consonant,CONSONANT_MAX_SIZE,CONSONANT_MAX_LENGH,PHONE_CONSONANT_MAX_LENGH,consonants,phone_consonants,&consonant_size);
    read_file(rhyme_phone,RHYME_MAX_SIZE,RHYME_MAX_LENGH,PHONE_RHYME_MAX_LENGH,rhymes,phone_rhymes,&rhyme_size);
}
void add_exeception_of_literal_y(){
    wcscpy(syllables[syllables_size],L"yên");
    wcscpy(syllables[syllables_size+1],L"yến");
    wcscpy(syllables[syllables_size+2],L"yền");
    wcscpy(syllables[syllables_size+3],L"yễn");
    wcscpy(syllables[syllables_size+4],L"yển");
    wcscpy(syllables[syllables_size+5],L"yện");
    wcscpy(syllables[syllables_size+6],L"yêm");
    wcscpy(syllables[syllables_size+7],L"yếm");
    wcscpy(syllables[syllables_size+8],L"yềm");
    wcscpy(syllables[syllables_size+9],L"yễm");
    wcscpy(syllables[syllables_size+10],L"yểm");
    wcscpy(syllables[syllables_size+11],L"yệm");
    syllables_size+=12;
}
void join_one_time(wchar_t *consonant, wchar_t *rhyme){
    wcscpy(syllables[syllables_size],consonant);
    wcscat(syllables[syllables_size],rhyme);
    syllables_size++;
}
void join_one_time_with_rule(wchar_t *consonant, wchar_t first_of_rhyme_non_tone,  wchar_t *rhyme){
    int len;
    if(wcscmp(consonant,L"gi")==0){
        len = wcslen(rhyme);
        if(first_of_rhyme_non_tone==L'i'){
            if(!(len ==2 &&(rhyme[1]==L'u'||rhyme[1]==L'a')))
                join_one_time(L"g",rhyme);
        }else{
                // if(!(wcslen(rhyme)>1&&first_of_rhyme_non_tone==L'i'&&first_of_rhyme_non_tone==L'\0')
            if(!(len==2&&first_of_rhyme_non_tone==L'ê'))
                join_one_time(consonant,rhyme);
        }
    }
    else{
        if(wcscmp(consonant,L"g")==0){
            if(first_of_rhyme_non_tone!=L'i')
                join_one_time(consonant,rhyme);
        }else{
            join_one_time(consonant,rhyme);
        }
    }
    // if(!(wcscmp(consonant,L"q")==0&&wcslen(rhyme)==2&&(rhyme[1]==L'y'||rhyme[1]==L'i'))){
    // }
}
// void join_one_time_with_rule(wchar_t *consonant, wchar_t first_of_rhyme_non_tone,  wchar_t *rhyme){
//     if(wcscmp(consonant,L"q")==0){
//         if(first_of_rhyme_non_tone==L'u'&&wcslen(rhyme)>1){
//             join_one_time(consonant,rhyme);
//         }
//     }else{
//         if(wcscmp(consonant,L"gi")==0){
//             if(first_of_rhyme_non_tone!=L'i'&&first_of_rhyme_non_tone!=L'y'){
//                 join_one_time(consonant,rhyme);
//             }
//         }else{
//             if(first_of_rhyme_non_tone==L'i'||first_of_rhyme_non_tone==L'e'||first_of_rhyme_non_tone==L'ê'||first_of_rhyme_non_tone==L'y'){
//                 if(wcscmp(consonant,L"c")!=0&&wcscmp(consonant,L"g")!=0&&wcscmp(consonant,L"ng")!=0)
//                     join_one_time(consonant,rhyme);
//             }else if(wcscmp(consonant,L"k")!=0&&wcscmp(consonant,L"gh")!=0&&wcscmp(consonant,L"ngh")!=0&&!(wcscmp(consonant,L"c")==0&&
//                     (rhyme[1]==L'y'||rhyme[1]==L'ý'||rhyme[1]==L'ỳ'||rhyme[1]==L'ỵ'||rhyme[1]==L'ỹ'||rhyme[1]==L'ỷ'||first_of_rhyme_non_tone==L'y')))
//                         join_one_time(consonant,rhyme);
//         }
//     }
// }
void join_consonant_rhyme(wchar_t first_of_rhyme_non_tone,  wchar_t *rhyme){
    int i;
    for(i=0;i<consonant_size;i++){
        join_one_time_with_rule(consonants[i],first_of_rhyme_non_tone,rhyme);
    }
}
void insert_tone_and_join_for_all_element(){
    int i;
    for(i=0;i<rhyme_size;i++)
        insert_tone_and_join(rhymes[i]);    
}
void print_array_of_string(int size,int len,wchar_t arrString[size][len]){
    int i;
    for(i=0;i<size;i++){
        printf("%ls\n",arrString[i]);
    }
}
void add_element(wchar_t first_of_rhyme_non_tone,wchar_t *rhyme){
    wcscpy(syllables[syllables_size],rhyme);
    syllables_size++;
    join_consonant_rhyme(first_of_rhyme_non_tone,rhyme);
}
void insert_tone_and_join(wchar_t *rhyme){
    if(is_end_ptk(rhyme)){
        insert_tone_and_join_end_ptk(rhyme);
    }else{
        add_element(rhyme[0],rhyme);
        insert_tone_and_join_non_end_ptk(rhyme);
    }
}
void insert_tone_and_join_end_ptk(wchar_t *rhyme){
    wchar_t c,first_of_rhyme_non_tone = rhyme[0];
    int position_replace;
    position_replace = find_index_to_insert_tone_and_join(rhyme);
    c=rhyme[position_replace];
    switch (c){
        case L'a':
            rhyme[position_replace]=L'á';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ạ';
            add_element(first_of_rhyme_non_tone,rhyme);
            break;
        case L'ă':
            rhyme[position_replace]=L'ắ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ặ';
            add_element(first_of_rhyme_non_tone,rhyme);
            break;
        case L'â':
            rhyme[position_replace]=L'ấ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ậ';
            add_element(first_of_rhyme_non_tone,rhyme);
            break;
        case L'e':
            rhyme[position_replace]=L'é';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ẹ';
            add_element(first_of_rhyme_non_tone,rhyme);
            break;
        case L'ê':
            rhyme[position_replace]=L'ế';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ệ';
            add_element(first_of_rhyme_non_tone,rhyme);
            break;
        case L'o':
            rhyme[position_replace]=L'ó';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ọ';
            add_element(first_of_rhyme_non_tone,rhyme);
            break;
        case L'ô':
            rhyme[position_replace]=L'ố';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ộ';
            add_element(first_of_rhyme_non_tone,rhyme);
            break;
        case L'ơ':
            rhyme[position_replace]=L'ớ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ợ';
            add_element(first_of_rhyme_non_tone,rhyme);
            break;
        case L'i':
            rhyme[position_replace]=L'í';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ị';
            add_element(first_of_rhyme_non_tone,rhyme);
            break;
        case L'u':
            rhyme[position_replace]=L'ú';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ụ';
            add_element(first_of_rhyme_non_tone,rhyme);
            break;
        case L'ư':
            rhyme[position_replace]=L'ứ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ự';
            add_element(first_of_rhyme_non_tone,rhyme);
            break;
        case L'y':
            rhyme[position_replace]=L'ý';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ỵ';
            add_element(first_of_rhyme_non_tone,rhyme);
    }
}
void insert_tone_and_join_non_end_ptk(wchar_t *rhyme){
    wchar_t c,first_of_rhyme_non_tone = rhyme[0];
    int position_replace;
    position_replace = find_index_to_insert_tone_and_join(rhyme);
    c=rhyme[position_replace];
    switch (c){
        case L'a':
            rhyme[position_replace]=L'á';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'à';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ã';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ả';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ạ';
            add_element(first_of_rhyme_non_tone,rhyme);
            break;
        case L'ă':
            rhyme[position_replace]=L'ắ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ằ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ẵ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ẳ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ặ';
            add_element(first_of_rhyme_non_tone,rhyme);
            break;
        case L'â':
            rhyme[position_replace]=L'ấ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ầ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ẫ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ẩ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ậ';
            add_element(first_of_rhyme_non_tone,rhyme);
            break;
        case L'e':
            rhyme[position_replace]=L'é';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'è';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ẽ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ẻ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ẹ';
            add_element(first_of_rhyme_non_tone,rhyme);
            break;
        case L'ê':
            rhyme[position_replace]=L'ế';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ề';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ễ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ể';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ệ';
            add_element(first_of_rhyme_non_tone,rhyme);
            break;
        case L'o':
            rhyme[position_replace]=L'ó';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ò';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'õ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ỏ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ọ';
            add_element(first_of_rhyme_non_tone,rhyme);
            break;
        case L'ô':
            rhyme[position_replace]=L'ố';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ồ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ỗ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ổ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ộ';
            add_element(first_of_rhyme_non_tone,rhyme);
            break;
        case L'ơ':
            rhyme[position_replace]=L'ớ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ờ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ỡ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ở';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ợ';
            add_element(first_of_rhyme_non_tone,rhyme);
            break;
        case L'i':
            rhyme[position_replace]=L'í';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ì';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ĩ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ỉ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ị';
            add_element(first_of_rhyme_non_tone,rhyme);
            break;
        case L'u':
            rhyme[position_replace]=L'ú';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ù';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ũ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ủ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ụ';
            add_element(first_of_rhyme_non_tone,rhyme);
            break;
        case L'ư':
            rhyme[position_replace]=L'ứ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ừ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ữ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ử';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ự';
            add_element(first_of_rhyme_non_tone,rhyme);
            break;
        case L'y':
            rhyme[position_replace]=L'ý';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ỳ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ỹ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ỷ';
            add_element(first_of_rhyme_non_tone,rhyme);
            rhyme[position_replace]=L'ỵ';
            add_element(first_of_rhyme_non_tone,rhyme);
    }
}

int is_end_ptk(wchar_t *rhyme){
    int len=wcslen(rhyme);
    switch(rhyme[len-1]){
        case L'p':
            return 1;
        case L't':
            return 1;
        case L'c':
            return 1;
        case L'h':
            if(rhyme[len-2]==L'c')
                return 1;
        default:
            return 0;
    }
}
int find_index_to_insert_tone_and_join(wchar_t *rhyme){
    int len=wcslen(rhyme);
    switch(len){
        case 2:
            if(rhyme[len-1]==L'ơ'||rhyme[len-1]==L'ê')
                return 1;
        case 1:
            return 0;
        case 3:
            if(rhyme[len-1]==L'h'||rhyme[len-1]==L'g')
                return 0;
            return 1; 
        case 4:
            if(rhyme[len-1]!=L'h'&&rhyme[len-1]!=L'g')
                return 2;
            return 1; 
    }
}