#include "server_lib/server_lib.h"

void dost();
void processRecive( char *buff);
void verify_login();
// char * getContentOfCommand( char * buff);	

void sig_chld(int singno){
	pid_t pid;
	int stat;
	while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("child %d terminated\n", pid);
	return; 
}

void main(){
	char buff[2048];
	pid_t pid;
	struct sockaddr_in serverAddr, clientAddr;
	int clientAddrLength;
	if((listenSock = socket(AF_INET,SOCK_STREAM,0)) == -1){
		printf("Loi tao socket\n");
	return;
	}
	// khoi tao cac dia chi
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5500);
	serverAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	if(bind(listenSock,(struct sockaddr *)&serverAddr, sizeof(sockaddr))==-1){
		printf("Loi bind\n");
	return;
	}
	listen(listenSock,10);
	clientAddrLength = sizeof(clientAddr);
	while(1){

		connSock = accept(listenSock,(sockaddr *)&clientAddr,(socklen_t*)&clientAddrLength);
		if(connSock<0) {printf("loi\n");exit(0);}
        printf("client ket noi\n");
		if((pid=fork()) == 0){
			close(listenSock);
			dost();
			close(connSock);
			exit(0);
		}
		signal(SIGCHLD,sig_chld);
		close(connSock);
	}
	close(listenSock);
}


void dost(){
	verify_login();
	printf("USERNAME: %s\n", username);
	while(1){
		reciveBytes = recv(connSock,buff,2048,0);
		buff[reciveBytes]='\0';
		processRecive(buff);
	}
}

void verify_login(){
		char buff[2048];
		char cmt[30];
		while(1){
		reciveBytes = recv(connSock,buff,2048,0);
		command command = analyzeCommand(buff);
		if(command.code == login)
		  strcpy(cmt,doLogin(command));
		else
		  doSignup(command);
		  
		if(strcmp(cmt,"login|true")==0){
			strcpy(username,command.param[0]);
			printf("success login!\n");
			break;
		}
	}
}



void processRecive( char *buff){
	command command = analyzeCommand(buff);
	switch(command.code){
		case new_folder:
			doNewFolder(command);
			break;
		case logout:
			doLogout(command);
			break;
		case signup:
			doSignup(command);
			break;
		case download_file:
			doDownloadFile(command);
			break;
		case upload_file:
			doUploadFile(command);
			break;
		case delete_file:
			doDeleteFile(command);
			break;
		case open_folder:
			doOpenFolder(command);
			break;
		case delete_folder:
			doDeleteFolder(command);
			break;
		case show_content_folder:
			doShowContentFolder(command);
			break;
	}
}


