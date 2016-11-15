#include "client_file.c"
int hasInIgnoreList(int command_code);
void saveFileWithCheck(int sock);
char* analyzeClientChose(int chose);
int choseOverwriteCancelBoth(int command_code);
int responeCommand(command cmd, char * msg1, char* msg2);
int doCommandClient(char*(*make_what_command)(),int (*respone_what)(command));
int responeUploadFile(command cmd);
int responeDeleteFile(command cmd);
int responeDownloadFile(command cmd);
void doDeleteFileClient();
void doDownloadFileClient();
void doUploadFileClient();
int responeNewFolder(command cmd);
int responeDeleteFolder(command cmd);
int responeOpenFolder(command cmd);
void doDeleteFolderClient();
void doNewFolderClient();
void doOpenFolderClient();
