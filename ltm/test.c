char buff[1024],username[1024],currentFolder[1024],currentFile[256];
#include "helper/helper.h"
void main(){
	char *s=make_delete_file_command();
	command c;
	// printf("%s\n",s);
	c = analyzeCommand(s);
	printf("%d\n",c.code);
	printf("%s\n",c.param[0]);
	// printf("%s\n",c.param[1]);
}
