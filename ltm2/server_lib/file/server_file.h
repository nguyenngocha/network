#include "server_file.c"
void acceptAndAction(command cmd,void(*action)(int,char*,char*),char * actionName, char * path);
void doDownloadFile(command cmd);
void doUploadFile(command cmd);
void doDeleteFile(command cmd);
void doDeleteFolder(command cmd);
void doOpenFolder(command cmd);
void doNewFolder(command cmd);
void doShowContentFolder(command cmd);
void doBackFolder(command cmd);