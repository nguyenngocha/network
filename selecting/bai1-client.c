#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdio.h>
#include <netinet/in.h>
#include <string.h>
void main(){
	int sendBytes,reciveBytes,count=0;
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in serverAddr;
	char buff[1024],quit[]="Q";
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5500);
	if((inet_aton("127.0.0.1",&serverAddr.sin_addr)==0)){
		printf("Loi:loi o inet_aton\n");
		return;
	}
	if(connect(sockfd,(struct sockaddr*)&serverAddr,sizeof serverAddr)!=0){
		printf("Loi: Ket noi den server that bai\n");
		return;
	}
	while(1){
		printf("Nhap chuoi ki tu can chuyen: ");
		gets(buff);
		if(strlen(buff)==0){
			printf("Chuoi ki tu da chuyen doi: %s\n",buff);
			continue;
		}else{	
			sendBytes = send (sockfd,buff,strlen(buff),MSG_NOSIGNAL);
			if(sendBytes<=0){
				break;
			}
			if(strcmp(buff,"q")==0||strcmp(buff,"Q")==0){
				break;
			}
			count +=sendBytes;
			reciveBytes = recv(sockfd,buff,1024,0);
			printf("Chuoi ki tu da chuyen doi: %s\n",buff);
		}
	}
	printf("So byte da gui toi server: %d\n",count);
	close(sockfd);
}
