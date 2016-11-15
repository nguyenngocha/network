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
void upper(char * str){
	int i = 0;	
	while(str[i]!='\0'){
		if(str[i]>='a'&&str[i]<='z'){
			str[i]-=32;
		}
		i++;
	}
}
void main(){
    int sockfd, n;
    struct sockaddr_in servaddr,clientaddr; 
    char buff[1024];
    socklen_t len;
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(5500);
    bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    printf("OK\n");
    while (1) {
        len=sizeof(clientaddr);
        if(recvfrom(sockfd, buff, 1024, 0, (struct sockaddr *)&clientaddr, &len)!=1) {
            upper(buff);
            printf("%s\n",buff);   
            printf("Received packet from %s:%d\nData: %s\n\n",inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), buff);
        }
        sendto(sockfd, buff, strlen(buff), 0,(struct sockaddr *)&servaddr, sizeof(struct sockaddr)); 
    }
}