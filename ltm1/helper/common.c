typedef struct{
  int code;
  char *param[2];
} command; 

char* make_command(int comCode, char* attr1, char* attr2){
  char* buff = (char*)malloc(sizeof(attr1) + sizeof(attr2) + sizeof(comCode));
  if(attr2!= NULL & attr1!= NULL)
    sprintf(buff,"%d|%s|%s|",comCode,attr1,attr2);
  else if(attr1!=NULL)
    sprintf(buff,"%d|%s",comCode,attr1);
  else
    sprintf(buff,"%d|",comCode);
  return buff;
}

char * split(char *buff[], char symbol){
  char *temp = (char *)malloc(1000*sizeof(char));
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
  c.code = atoi(split(&buff,'|'));
  c.param[0]=(char*)malloc(sizeof(char)*81);
  strcpy(c.param[0],split(&buff,'|'));
  c.param[1]=(char*)malloc(sizeof(char)*strlen(buff));
  strcpy(c.param[1],split(&buff,'|'));
  return c;
}