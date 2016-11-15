int listenSock, connSock;
int reciveBytes,sentBytes;
char buff[1024],username[1024],currentFolder[1024],currentFile[256];
typedef struct sockaddr sockaddr;
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <unistd.h>
#include "../helper/helper.h"
#include "file/server_file.h"
#include "user/server_user.h"
