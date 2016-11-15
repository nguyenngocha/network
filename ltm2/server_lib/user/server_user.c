char* findUserName( char* name){
	FILE* fptr = fopen("verirylogin.txt","r");
	char* user_info = (char*)malloc(81*sizeof(char));
	char* user_name;
	while(!feof(fptr)){
	fgets(user_info,81,fptr);
		user_info[strlen(user_info)-1]= '\0';
	//char * split(char *buff[], char symbol)
		user_name = split(&user_info,'|');
		if(strcmp(name,user_name)==0){
			fclose(fptr);
			return user_info;
		}
	}
	return NULL;
}

char* doLogin(command command){
	char* password = findUserName( command.param[0]);
	char* buff = (char*)malloc(30*sizeof(char));
	if(password == NULL||strcmp(command.param[1],password)!=0)
		strcpy(buff,"login|false");
	else strcpy(buff,"login|true");
	sentBytes= send(connSock,buff,1024,0);
	return buff;
}

void addUsers(char* name, char* password){
	char buff[81];
	char* ex = (char*)malloc(81*sizeof(char));
	FILE* fptr = fopen("verirylogin.txt","a+t");

	strcpy(buff,name);
	strcpy(buff+strlen(buff),"|");
	strcpy(buff+strlen(buff),password);

	while(!feof(fptr)){
		fgets(ex,81,fptr);
	}
	fprintf(fptr,"%s\n",buff);
	fclose(fptr);
}

void doSignup(command command){
		printf("%d\n",command.code);
		printf("%s\n",command.param[0]);
		printf("%s\n",command.param[1]);
	printf("ok\n");
	char* password = findUserName(command.param[0]);
			printf("%d\n",command.code);
		printf("%s\n",command.param[0]);
		printf("%s\n",command.param[1]);
	printf("ok\n");
	char buff[30],*cmd;
	if(password == NULL){
				printf("%d\n",command.code);
		printf("%s\n",command.param[0]);
		printf("%s\n",command.param[1]);
		printf("ok\n");
		strcpy(buff,"signup|true");
		addUsers(command.param[0],command.param[1]);
		printf("%s|||\n",command.param[0]);// t ms them o day
		asprintf(&cmd,"mkdir %s",command.param[0]);// day
		system(cmd);// day the thoi.
	}else
		strcpy(buff,"signup|false");
	sentBytes= send(connSock,buff,1024,0);
}



void doLogout( command command){
	sentBytes= send(connSock,"",1024,0);
}	



