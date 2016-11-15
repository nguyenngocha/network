typedef struct{
  int code;
  char *param[2];
} command; 
char* make_command(int comCode, char* attr1, char* attr2){
  char* buff;
  if(attr2!= NULL & attr1!= NULL)
    asprintf(&buff,"%d|%s|%s|",comCode,attr1,attr2);
  else if(attr1!=NULL)
    asprintf(&buff,"%d|%s|",comCode,attr1);
  else
    asprintf(&buff,"%d|",comCode);
  return buff;
}

char * split(char *buff[], char symbol){
  char temp[2048];
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

command analyzeCommand(char * buff){
  command c;
  char param0[1024];
  char param1[strlen(buff)];
  c.code = atoi(split(&buff,'|'));
  c.param[0]=param0;
  strcpy(c.param[0],split(&buff,'|'));
  c.param[1]=param1;
  strcpy(c.param[1],split(&buff,'|'));
  return c;
}
void splitFromEnd(char buff[], char symbol){
  int i=strlen(buff)-1;
  int k=0;
  while(buff[i]!=symbol&&i>0){
    i--;
    k++;
  }
  buff[i]='\0';
}