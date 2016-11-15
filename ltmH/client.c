#include "client_lib/client_lib.h"
void dost();
void menu();
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
void menu(){
	printf("%s1. Download file\n",KYEL);
	printf("2. Upload file\n");
	printf("3. Delete file\n");
	printf("4. Open folder\n");
	printf("5. New folder\n");
	printf("6. Delete folder\n");
	printf("7. Show file and folder\n");
	printf("8. Back\n");
	printf("%sYour chose: ",KGRN);
}

void verify_login(){
	int sw;
	char* buff = (char*)malloc(sizeof(char));
	do{
		printf("%s\n\n\n***** Verify User *****\n%s",KGRN,KNRM);
		printf("%s1.login\n2.signup\n3.exit\n%s",KYEL,KNRM);
		printf("%schoose: ",KGRN);
		scanf("%d",&sw);
		printf("%s",KNRM);
		char c;
		char buff[2048];
		while((c = getchar())!='\n');
		switch(sw){
			case 1:
				printf("\n\n\n%s--- LOGIN ---%s\n",KGRN,KNRM);
				char* loginform;
				loginform = make_login_command();
				send (sockfd,loginform,2048,0);
				recv(sockfd,buff,2048,0);
				if(strcmp(buff,"login|true")==0)
					printf("%sdang nhap thanh cong%s\n\n",KGRN,KNRM);
				else
					printf("%stai khoan hoac mat khau khong dung%s\n\n",KRED,KNRM);
				break;
			case 2:
				printf("\n\n\n%s--- SIGN UP ---%s\n",KGRN,KNRM);
				char* signupform = make_signup_command();
				send (sockfd,signupform,strlen(signupform),0);
				recv(sockfd,buff,2048,0);
				if(strcmp(buff,"signup|false")==0)
					printf("\n%sTai khoan nguoi dung da ton tai%s",KRED,KNRM);
				else 
					printf("\n%sdang ky thanh cong%s",KGRN,KNRM);
				break;
			case 3:
				exit(0);
			default:
				printf("\n%snhap sai!%s",KRED,KNRM);
		}
		if(strcmp(buff,"login|true")==0) break;
	}while(1);
}



void dost(){
	// login
	verify_login();
	printf("%s\n", username);
	while(1){
		int chose;
		printf("%sCurrent foler: %s%s\n",KGRN,currentFolder,KNRM);
		menu();
		scanf("%d",&chose);
		printf("\x1B[0m");
		while(getchar()!='\n');
		switch(chose){
			case 1:
				doDownloadFileClient();
				break;
			case 2:
				doUploadFileClient();
				break;
			case 3:
				doDeleteFileClient();
				break;
			case 4:
				doOpenFolderClient();
				break;
			case 5:
				doNewFolderClient();
				break;
			case 6:
				doDeleteFolderClient();
				break;
			case 7:
				doShowContentFolderClient();
				break;
			case 8:
				doBackFolderClient();
				break;
			default:
				break;
		}
	}

}
