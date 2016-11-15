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
void main(){
    int sockfd, n;
    struct sockaddr_in servaddr; 
    int sendBytes,reciveBytes,count=0;
    char buff[1024];
 	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(5500);
	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    while (1) {
        printf("Nhap chuoi ki tu can chuyen: ");
		gets(buff);
        if(strlen(buff)==0){
			printf("Chuoi ki tu da chuyen doi: %s\n",buff);
			continue;
		}else{	
		    sendBytes=sendto(sockfd, buff, strlen(buff), 0,(struct sockaddr *)&servaddr, sizeof(struct sockaddr)); 
			if(sendBytes<=0){
				break;
			}
			if(strcmp(buff,"q")==0||strcmp(buff,"Q")==0){
				break;
			}
			count +=sendBytes;
			recvfrom(sockfd, buff, 1024, 0, NULL, NULL); 
			printf("Chuoi ki tu da chuyen doi: %s\n",buff);
		}
	}
	printf("So byte da gui toi server: %d\n",count);
    close(sockfd);
}