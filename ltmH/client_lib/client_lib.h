int reciveBytes,sentBytes,sockfd;
struct sockaddr_in serverAddr;
char buff[2048],username[2048],currentFolder[2048]="",currentFile[256];
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../helper/helper.h"
#include "file/client_file.h"
#include "user/client_user.h"
