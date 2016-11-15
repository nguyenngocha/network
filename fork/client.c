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
	char buff[1024],s[512],sockid[6];	
	FILE *f1,*f;
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
		
		printf("Vui long dang nhap vao he thong\n");
		gets(buff);
		send (sockfd,buff,strlen(buff),0);
		printf("%s\n",buff);
		FILE *f =fopen(buff,"wb");
		while(1){
			reciveBytes = recv(sockfd,buff,1024,0);
			// printf("%d\n",reciveBytes);
			if(reciveBytes<=0){
				break;	
			} 
	        fwrite(buff, 1, reciveBytes, f);
		}
		fclose(f);
		printf("xau nhan duoc tu sever: %s\n", buff);
	}
	printf("OK\n");
	printf("So byte da gui toi server: %d\n",count);
	close(sockfd);
}
