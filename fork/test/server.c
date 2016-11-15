#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h> 
#include <unistd.h>

void sig_chld(int singno){
	pid_t pid;
	int stat;
	while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("child %d terminated\n", pid);
	return; 
}
typedef struct sockaddr sockaddr;
void upper(char * str);
void main(){
	pid_t pid;
	int listenSock, connSock;
	struct sockaddr_in serverAddr, clientAddr;
	int clientAddrLength;
	char buff[1024];
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
		int reciveBytes,sentBytes;
		if((pid=fork()) == 0){
			close(listenSock);
			reciveBytes=recv(connSock,buff,1024,0);
			buff[reciveBytes]='\0';
			printf("%s\n",buff);
			FILE *f = fopen(buff,"rb");
			int n;
			while((n=fread(buff,1,1024,f))>0){
				sentBytes= send(connSock,buff,n,0);
			}
			fclose(f);
			close(connSock);
			exit(0);
		}
		signal(SIGCHLD,sig_chld);
		close(connSock);
	}
	close(listenSock);
}
void upper(char * str){
	int i = 0;	
	while(str[i]!='\0'){
		if(str[i]>='a'&&str[i]<='z'){
			str[i]-=32;
		}
		i++;
	}
}
