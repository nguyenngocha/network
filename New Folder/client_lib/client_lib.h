int sockfd;
struct sockaddr_in serverAddr;
char buff[1024];	
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include "../helper/helper.h"
#include "file/client_file.h"
#include "user/client_user.h"
