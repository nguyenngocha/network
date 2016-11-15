char* findUserName( char* name){
	FILE* fptr = fopen("verirylogin.txt","r");
	char* user_info = (char*)malloc(81*sizeof(char));
	char* user_name;
	while(!feof(fptr)){
	fgets(user_info,81,fptr);
	//char * split(char *buff[], char symbol)
		user_name = split(&user_info,'|');
		if(strcmp(name,user_name)==0)
			return split(&user_info,'|');
	}
	return NULL;
}
int doLogin( command command){
	char* password = findUserName( command.param[0]);
	char buff[30];
	if(password == NULL||strcmp(command.param[1],password)!=0)
		strcpy(buff,"login|false");
	else strcpy(buff,"login|true");
	sentBytes= send(connSock,buff,1024,0);
}
void doLogout( command command){
	sentBytes= send(connSock,"",1024,0);
}	
void doDelete( command command){
	sentBytes= send(connSock,"",1024,0);
}
void doAdd( command command){
	sentBytes= send(connSock,"",1024,0);
}

