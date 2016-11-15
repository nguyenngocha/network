#include "client_lib/client_lib.h"




void dost();

void main(){

	sockfd = socket(AF_INET,SOCK_STREAM,0);
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
	dost();
	close(sockfd);
}

void dost(){
	while(1){
		printf("Vui long dang nhap vao he thong\n");
		char* loginform = make_login_command();
		loginform[strlen(loginform)]='\0';

		send (sockfd,loginform,strlen(loginform),0);
		recv(sockfd,buff,1024,0);
		printf("xau nhan duoc tu sever: %s\n", buff);
	}
	// while(1){
	// 	printf("Nhap duong dan file can chuyen: ");
	// 	gets(s);	
	// 	f = fopen(s,"r");
	// 	if(f==NULL){
	// 		printf("Loi: khong co duong dan nay\n");
	// 		continue;
	// 	}
	// 	int i =0;		
	// 	while(s[i]!='\0'){
	// 		if(s[i]=='.'){
	// 			s[i]='\0';
	// 		}
	// 		i++;
	// 	}
	// 	sprintf(sockid, "%d", sockfd);
	// 	strcat(s,sockid);
	// 	f1=fopen(s,"w");		
	// 	printf("File da chuyen doi:\n");
	// 	while(1){		
	// 		fgets(buff,1024,f);			
	// 		if(feof(f)){				
	// 			break;
	// 		}else{
	// 			sendBytes = send (sockfd,buff,strlen(buff),0);
	// 			reciveBytes = recv(sockfd,buff,1024,0);
	// 			printf("%s",buff);
	// 			fprintf(f1,"%s",buff);
				
	// 		}
	// 	}
	// 	break;
	// }
}