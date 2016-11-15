#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1024
char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
void decodeblock(unsigned char in[], char *clrstr) {
  unsigned char out[4];
  out[0] = in[0] << 2 | in[1] >> 4;
  out[1] = in[1] << 4 | in[2] >> 2;
  out[2] = in[2] << 6 | in[3] >> 0;
  out[3] = '\0';
  strncat(clrstr, out, sizeof(out));
}

void b64_decode(char *b64src, char *clrdst) {
  int c, phase, i;
  unsigned char in[4];
  char *p;

  clrdst[0] = '\0';
  phase = 0; i=0;
  while(b64src[i]) {
    c = (int) b64src[i];
    if(c == '=') {
      decodeblock(in, clrdst); 
      break;
    }
    p = strchr(b64, c);
    if(p) {
      in[phase] = p - b64;
      phase = (phase + 1) % 4;
      if(phase == 0) {
        decodeblock(in, clrdst);
        in[0]=in[1]=in[2]=in[3]=0;
      }
    }
    i++;
  }
}
void encodeblock( unsigned char in[], char b64str[], int len ) {
    unsigned char out[5];
    out[0] = b64[ in[0] >> 2 ];
    out[1] = b64[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
    out[2] = (unsigned char) (len > 1 ? b64[ ((in[1] & 0x0f) << 2) |
             ((in[2] & 0xc0) >> 6) ] : '=');
    out[3] = (unsigned char) (len > 2 ? b64[ in[2] & 0x3f ] : '=');
    out[4] = '\0';
    strncat(b64str, out, sizeof(out));
}
void b64_encode(char *clrstr, char *b64dst) {
  unsigned char in[3];
  int i, len = 0;
  int j = 0;

  b64dst[0] = '\0';
  while(clrstr[j]) {
    len = 0;
    for(i=0; i<3; i++) {
     in[i] = (unsigned char) clrstr[j];
     if(clrstr[j]) {
        len++; j++;
      }
      else in[i] = 0;
    }
    if( len ) {
      encodeblock( in, b64dst, len );
    }
  }
}

typedef struct users
{
	char name[30];
	char pass[30];
}user;

typedef struct mess_client
{
	int flag;
	char buff[MAX];
	user u;
}msg_client;

typedef struct mess_server
{
	int flag;
	char buff[MAX];
	
}msg_server;

void sig_chld(int signo)
{
pid_t pid;
int stat;
while((pid = waitpid(-1, &stat, WNOHANG))>0)
printf("child %d terminated\n", pid);
return;
}
void add_user(user u){
	FILE *f;
	f=fopen("user.txt","ab");
	fwrite(&u,1,sizeof(u),f);
	fclose(f);
}

int checkuser(user u){
	FILE *f;
	user temp;
	f=fopen("user.txt","rb");
	while(!feof(f)){
		fread(&temp,1,sizeof(temp),f);
		printf("name = %s\n",temp.name );
		printf("pass = %s\n",temp.pass );
		if((strcmp(u.name,temp.name)==0)&&(strcmp(u.pass,temp.pass)==0)){
			fclose(f);
			return 1;
		}
		if(strcmp(u.name,temp.name)==0){
			fclose(f);
			return 2;
		}
	}
	fclose(f);
	return 3;
}

int main()
{
int listen_sock, conn_sock;
int server_len, client_len;
struct sockaddr_in server_address;
struct sockaddr_in client_address;
char myb64[1024] = ""; 
char mydst[1024] = "";
msg_client s1;
msg_server s2;
int ch,k;
			
listen_sock = socket(AF_INET, SOCK_STREAM, 0);
if (listen_sock == -1)
 {
    printf("khong tao duoc socket\n");
    return 0;
 }
 printf("Tao socket thanh cong\n");

server_address.sin_family = AF_INET;
inet_aton("127.0.0.1",&server_address.sin_addr);
server_address.sin_port = htons(5500);
server_len = sizeof(server_address);

if(bind(listen_sock, (struct sockaddr *)&server_address,server_len)<0)
{
	printf("bind failed.\n");
    return 0;
}
printf("bind done\n");
int check = listen(listen_sock,10);
if (check == -1)
 {
 printf("error connect");
 return 0;
 }
printf("waiting connect ...\n");
while(1) {
		client_len = sizeof(client_address);
		conn_sock = accept(listen_sock,(struct sockaddr *)&client_address, &client_len);
		if(conn_sock==-1){
			printf("error connect\n");
			return 1;
		}else{
			printf("Accept new connection\n");
		}
		if(fork() == 0){
			close(listen_sock);
			int sentBytes,revedBytes,i;
			int chose;
			while(1){
			
					revedBytes = recv(conn_sock,&s1,sizeof(s1),0);
					//if(revedBytes < 0) break;
					ch=s1.flag;
					switch(ch){
						case 1:
							printf("%s\n",s1.u.name);
							k=checkuser(s1.u); 	//dang nhap
							printf("k: %d\n",k );
							if(k==1) s2.flag=1;
							if(k!=1) s2.flag=0;
							send(conn_sock,&s2,sizeof(s2),0);
						case 2:
							printf("%s\n",s1.u.name);
							k=checkuser(s1.u);		//dang ki
							printf("k: %d\n",k );
							if(k!=3) s2.flag=0;
							if(k==3){
									s2.flag=1;
									add_user(s1.u);
								}
							send(conn_sock,&s2,sizeof(s2),0);
							break;
						case 3:
						while(1){
						    	revedBytes = recv(conn_sock,&s1,1024,0);
						        s1.buff[revedBytes]='\0';
						        if(strcmp(s1.buff,"Q")==0) break;
						        b64_encode(s1.buff, s2.buff);
						    	sentBytes=send(conn_sock,&s2,sizeof(msg_server),0);
						    }
						break;
						case 4:
							while(1){
							    	revedBytes = recv(conn_sock,&s1,sizeof(msg_client),0);
							        s1.buff[revedBytes]='\0';
							        if(strcmp(s1.buff,"Q")==0) break;
							        b64_decode(s1.buff,s2.buff);
							    	sentBytes=send(conn_sock,&s2,sizeof(msg_server),0);
							    }
							break;
					}
				}
			close(conn_sock);
			exit(1);
			}
		signal(SIGCHLD,sig_chld);
		}
	return 1;
	}
