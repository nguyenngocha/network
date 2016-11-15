#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bt-5.0.0/inc/btree.h"
char* split(char *buff, char symbol);
void read_file_to_tree(char *source,char *destiny);
void search (BTA* tree1);
int main(){
	// read_file_to_tree("result_xampa","tree_xampa");
	BTA * tree;
  	tree = btopn("tree_xampa",0,0);
  	for(;;)
  	search(tree);
  	btcls(tree);
}

void read_file_to_tree(char *source,char *destiny){
	btinit();
	BTA *tree;
	FILE *source_file = fopen(source,"r");
	char *syllable=(char*)malloc(256*sizeof(char)),*phone_syllable;
	tree=btcrt(destiny,0,0);
	while(fgets(syllable,256,source_file)){
        syllable[strlen(syllable)-1]=L'\0';
        phone_syllable=split(syllable,L' ');
        // printf("%s %s\n",syllable,phone_syllable);
        int size = strlen(syllable)+strlen(phone_syllable)-1;
		btins(tree,syllable,phone_syllable,size);
	}
	fclose(source_file);
	btcls(tree);
}

char* split(char *buff, char symbol){
    if(buff==L'\0')
        return NULL;
    while(*buff!=symbol&&*buff!=L'\0')
        buff++;
    *buff=L'\0';
    buff++;
    return buff;
}

void search (BTA* tree1)
{
  int size;
  char ta[100],tv[256];
  printf("syllable:");
  gets(ta);
  if(btsel(tree1,ta,tv,30*sizeof(char),&size)==0)
   printf("%s %s\n",ta,tv);
  else 
    printf("can't search\n");
}