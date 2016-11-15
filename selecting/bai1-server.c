#include <sys/socket.h>
#include <stdlib.h>
#include <sys/time.h> 
#include <arpa/inet.h>    
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>   
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>  

typedef struct sockaddr sockaddr;
void upper(char * str);
void main(){
	int reciveBytes,sentBytes;
	int listenSocket, connSock;
	int i;
	int clientAddrLength;
	struct sockaddr_in serverAddr, clientAddr;
	char buff[1024];
	int maxfd,fd;
	fd_set readfd;
	int event;
	struct timeval time;
	int client[FD_SETSIZE];
	for(i=0;i<FD_SETSIZE;i++) client[i]=-1;
	if((listenSocket = socket(AF_INET,SOCK_STREAM,0)) == -1){
		printf("Loi tao socket\n");
	return;
	}
	// khoi tao cac dia chi
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5500);
	serverAddr.sin_addr.s_addr=INADDR_ANY;
	if(bind(listenSocket,(struct sockaddr *)&serverAddr, sizeof(sockaddr))==-1){
		printf("Loi bind\n");
	return;
	}
	listen(listenSocket,10);
	
	while(1){
		FD_ZERO(&readfd);
		FD_SET(listenSocket,&readfd);
		maxfd=listenSocket;
		  for ( i = 0 ; i < FD_SETSIZE ; i++) 
        {
            
            fd = client[i];
            if(fd > 0)
                FD_SET( fd , &readfd);
            if(fd > maxfd)
                maxfd = fd;
        }
        time.tv_sec=10;
        time.tv_usec=500000;
        event=select(maxfd+1,&readfd,NULL,NULL,&time);
        if(event==0){printf("time out\n");}
        if(event==-1) printf("loi select\n");
        if( FD_ISSET(listenSocket,&readfd)!=0){
        	clientAddrLength=sizeof(serverAddr);
        	connSock=accept(listenSocket,(sockaddr*)&serverAddr,(socklen_t*)&clientAddrLength);
        	if(connSock<0) {printf("loi\n");exit(0);}
        	printf("client ket noi\n");
        	for(i=0;i<FD_SETSIZE;i++){
        		if(client[i]==-1){
        			client[i] = connSock;
 					break;
        		}
        	}
        }
        for(i=0;i<FD_SETSIZE;i++){
        	if(FD_ISSET(client[i],&readfd)){
        		while((reciveBytes= recv(client[i],buff,1024,0))!=0){
        			buff[reciveBytes]='\0';
					upper(buff);
					send(client[i],buff,1024,0);
        		}
				printf("client dong ket noi'\n");
        		close(client[i]);
        		client[i]=-1;
        	}
        }
	}
	close(listenSocket);
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
