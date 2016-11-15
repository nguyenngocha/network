char buff[1024],username[1024],currentFolder[1024],currentFile[256];
#include "helper/helper.h"
int doCommandClient(char*(*make_what_command)()){
	char *cmd;
    command c;
	printf("doCommandClient\n");
	cmd=make_what_command();
	printf("doCommandClient\n");
	
	c=*(command*)cmd;
	printf("%s\n",c.param[0]);
}
void main(){
	char *s=make_download_file_command();
	command c;
	printf("%s\n",s);
	c = analyzeCommand(s);
	printf("%d\n",c.code);
	printf("%s\n",c.param[0]);
	printf("%s\n",c.param[1]);
	// doCommandClient(make_download_file_command);
}
