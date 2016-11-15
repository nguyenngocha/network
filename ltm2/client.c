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
	printf("8. Back folder\n");
	printf("%sYour chose: ",KNRM);
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
		char buff[2048];
		while((c = getchar())!='\n');
		switch(sw){
			case 1:
				printf("\n\n\n--- LOGIN ---\n");
				char* loginform;
				loginform = make_login_command();
				send (sockfd,loginform,2048,0);
				recv(sockfd,buff,2048,0);
				if(strcmp(buff,"login|true")==0)
					printf("dang nhap thanh cong\n\n");
				else
					printf("tai khoan hoac mat khau khong dung\n\n");
				break;
			case 2:
				printf("\n\n\n--- SIGN UP ---\n");
				char* signupform = make_signup_command();
				send (sockfd,signupform,strlen(signupform),0);
				recv(sockfd,buff,2048,0);
				if(strcmp(buff,"signup|false")==0)
					printf("\nTai khoan nguoi dung da ton tai");
				else 
					printf("\ndang ky thanh cong");
				break;
			case 3:
				exit(0);
			default:
				printf("\nnhap sai!");
		}
		if(strcmp(buff,"login|true")==0) break;
	}while(1);
}



void dost(){
	// login
	verify_login();
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
	// while(1){
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
	// 		fgets(buff,2048,f);			
	// 		if(feof(f)){				
	// 			break;
	// 		}else{
	// 			sendBytes = send (sockfd,buff,strlen(buff),0);
	// 			reciveBytes = recv(sockfd,buff,2048,0);
	// 			printf("%s",buff);
	// 			fprintf(f1,"%s",buff);
				
	// 		}
	// 	}
	// 	break;
	// }
}
