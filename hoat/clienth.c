#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1024
typedef struct users
{
  char name[30];
  char pass[30];
}user;
typedef struct mess_client
{
  int flag;
  char buff[MAX];// noi dung file gui di
  user u;// thong tin nguoi dung
}msg_client;
typedef struct mess_server
{
  int flag;
  char buff[MAX];
}msg_server;
int sockfd;
int createSocket(){
  struct sockaddr serverAddr;
  struct sockaddr_in inAddr;
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  if (sockfd == -1)
    {
        printf("khong tao duoc socket\n");
        exit(1);
    }
    printf("Tao socket thanh cong\n");
    inAddr.sin_family=AF_INET;
    inAddr.sin_port=htons(5500);
    inet_aton("127.0.0.1",&inAddr.sin_addr);
    if(connect(sockfd,(struct sockaddr *)&inAddr,sizeof(struct sockaddr))<0){
      printf("connect failed.\n");
      exit(1);
    } 
}
char *inputString(int size){
  int test=0;
  char *s=(char*)malloc(size);
  do{
    if(test!=0){
      printf("Moi nhap lai : ");
    }
  fgets(s,size,stdin);
  test++;
  }while(strlen(s)<=1);
  return strtok(s,"\n");
} //nhan xau dau vao tu ban phim
int todo1(){
  char *FileName;
  char *Result;
  FILE *fpt,*ft;
  int sentBytes,revedBytes;
  int Count=0;
  msg_client s;
  msg_server s1;
  s.flag=3;
  printf("Input file name : ");
  __fpurge(stdin);
  FileName = inputString(20);
  fpt = fopen(FileName,"r");
  if(fpt==NULL){
    printf("File not found");
    return -1;
  }
  printf("File Result : ");
  Result = inputString(20);
  ft = fopen(Result,"w");
  while(!feof(fpt)){
    if (fgets(s.buff,MAX,fpt) != NULL ){
      sentBytes=send(sockfd,&s,sizeof(msg_client),0);
      Count = Count + strlen(s.buff);
      revedBytes=recv(sockfd,&s1,sizeof(msg_server),0);
      fprintf(ft,"%s\n",s1.buff);
    }
  }
  fclose(fpt);fclose(ft);
  strcpy(s.buff,"Q");
  send(sockfd,&s,sizeof(msg_client),0);
  return Count;
} // gui noi dung file va nhan noi dung dc ma hoa va ghi vao file dc chi dinh
int todo2(){
  char *FileName;
  char *Result;
  FILE *fpt,*ft;
  int sentBytes,revedBytes;
  int Count=0;
  msg_client s;
  msg_server s1;
  printf("Input file name : ");
  __fpurge(stdin);
  FileName = inputString(20);
  fpt = fopen(FileName,"r");
  if(fpt==NULL){
    printf("File not found");
    return -1;
  }
  printf("File Result: ");
  Result = inputString(20);
  ft = fopen(Result,"w");
  s.flag=4;
  while(!feof(fpt)){
    if (fgets(s.buff,MAX,fpt) != NULL ){
      sentBytes=send(sockfd,&s,sizeof(msg_client),0);
      Count = Count + strlen(s.buff);
      revedBytes=recv(sockfd,&s1,sizeof(msg_server),0);
      fprintf(ft,"%s",s1.buff);
    }
  }
  fclose(fpt);fclose(ft);
  strcpy(s.buff,"Q");
  send(sockfd,&s,sizeof(msg_server),0);
  return Count;
}

int main(int argc, char const *argv[])
{
  int Sum;
  int s,size,ch,choose1;
  msg_server s2;
  msg_client s1;
  user a;

  createSocket();
	while(1){
	printf("1.dang nhap\n");
	printf("2.dang ki\n");
	printf("3.thoat\n");
	printf("nhap lua chon so :");
	scanf("%d",&choose1);
  while(getchar()!='\n');
		switch (choose1){
			case 1:	
			printf("nhap name : \n");gets(s1.u.name);
			printf("input password : \n");gets(s1.u.pass);
			s1.flag=1;
			send(sockfd,&s1,sizeof(s1),0);
			recv(sockfd,&s2,sizeof(s2),0);
			if(s2.flag==1){
				while(1){
						printf("---------------------MENU----------------\n1.ma hoa\n2.giai ma\n3.thoat\n-------------------------------------");
						printf("chon: \n");
						scanf("%d",&ch);
            while(getchar()!='\n');
						switch(ch){
							case 1:
								Sum = todo1();
								printf("Ma hoa xong :\n");
								break;
							case 2: 
								Sum = todo2();
								printf("giai ma xong\n");
								break;
							case 3:
                break;
						}
            if(ch==3) break;					}	
			}else{
				printf("Username hoac password sai\n");
			}
			break;
			case 2:
				printf("Nhap username: \n");
				scanf("%s",s1.u.name);
				printf("Password:\n");
				scanf("%s",s1.u.pass);
				s1.flag=2;
				send(sockfd,&s1,sizeof(s1),0);
				recv(sockfd,&s2,sizeof(s2),0);
				if(s2.flag==1) printf("Dang ki thanh cong\n");
				else printf("Username da co nguoi dung\n");	
				break;
		} 
		if(choose1==3) break;
	
}
close(sockfd);
	return 0;
}

