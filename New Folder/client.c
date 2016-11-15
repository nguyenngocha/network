#include "client_lib/client_lib.h"

void dost();
void verify_login();

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
	while(1){
		verify_login();
		printf("\nDang nhap thanh cong\n");

	}
	close(sockfd);
}

void verify_login(){
	int sw;
	char* buff = (char*)malloc(sizeof(char));
	do{
		printf("\n\n\n***** Verify User *****\n");
		printf("1.login\n2.signup\n3.exit\n");
		printf("choose: ");
		scanf("%d",&sw);
		char c;
		char buff[1024];
		while((c = getchar())!='\n');
		switch(sw){
			case 1:
				printf("\n\n\n--- LOGIN ---\n");
				char* loginform = make_login_command();
				loginform[strlen(loginform)]='\0';
				send (sockfd,loginform,1024,0);
				recv(sockfd,buff,1024,0);
				break;
			case 2:
				printf("\n\n\n--- SIGN UP ---\n");
				char* signupform = make_signup_command();
				send (sockfd,signupform,strlen(signupform),0);
				recv(sockfd,buff,1024,0);
				break;
			case 3:
				exit(0);
			default:
				printf("nhap sai!\n\n");
		}
		printf("|%s|\n",buff);
		if(strcmp(buff,"login|true")==0) break;
	}while(1);
}