// enum{
//   login = 1,
//   logout = 2,
//   delete = 3,
//   add = 4,
//   edit = 5,
//   download = 6
// }command_code;
typedef struct{
  int code;
  char param1[81];
  char param2[100];
} command; 

char* make_command(int comCode, char* attr1, char* attr2){
  command cmd;
  char buff[1024];
  cmd.code=comCode;
  strcpy(param1,attr1);
  strcpy(param2,attr2);
  return memcpy(buff,&cmd,sizeof(cmd));
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
  command c=*((command*)buff;
  return c;
}



// openfile|filename
// back
// add|filename|filecontent
