//Nhung truong hop server tra ve false! ma xu ly sau, k xu ly trong ham doCommandClient, thi cho vao list
int ignoreList[]={upload_file,new_folder,back_folder}; 
int ignoreListSize=3;
int hasInIgnoreList(int command_code){
    int i;
   for(i=0;i<ignoreListSize;i++){
       if(command_code==ignoreList[i]) return 1;
   } 
   return 0;
}
void saveFileWithCheck(int sock){
        while(1){
            if(!checkFileExist(currentFile)){//Neu ten file chua ton tai thi tao file ms 
                saveContentFile(sock,"Download",currentFile);
                break;
            }else{
                printf("%sFile already exist !\n%s",KRED,KNRM);
                if(yesNoQuestion("Do you want to overwrite it(Yes/No)? ")){
                    saveContentFile(sock,"Download",currentFile);
                    break;
                }else{
                    printf("Please input new file name: ");
                    gets(currentFile);
                }
            }
        }    
}
// this function onle use for client to chose overwrite keep both or cancel
char* analyzeClientChose(int chose){
    switch(chose){
        case 1:
            return "Overwrite";
        case 2:
            return "Keep both";
        case 3:
            return "Cancel";
    }
}
//if file already exist in server folder
int choseOverwriteCancelBoth(int command_code){
    int chose;
    char choseToString[10];
    printf("   1.Overwrite\n   2.Keep both\n   3.Cancel\n   Your chose: ");
    scanf("%d",&chose);
    while(getchar()!='\n');
    sendCommand(sockfd,make_command(command_code,analyzeClientChose(chose),NULL));
    if(chose==3) return 0;// neu nguoi dung cancel return 0 con lai thi return 1
    return 1;
}
////////////////////////////////////////////////////
//RESPONE nhan tra ve tu server
int responeCommand(command cmd, char * msg1, char* msg2){
    if(strcmp(cmd.param[0],"false!")==0){
        printf("%s%s%s",KRED,msg2,KNRM);
        return 0;
    }
    printf("%s",msg1);
    return 1;
}
//DO WHAT
// ham nay se tra ve 1 command neu cmd code = 0  nghia la ham tra ve false 
int doCommandClient(char*(*make_what_command)(),int (*respone_what)(command)){
    command cmd;
    int isNotCancel=0;// khoi tao the nay de neu send bi nguoi dung cancel thi isNotCancel =0
    while(1){
        if(!sendCommand(sockfd,make_what_command())) break; // neu nguoi dung cancel thi break; 
        // neu server tra ve !false hoac nam trong ignoreList thi return 1
        if(respone_what((cmd = reciveRespond(sockfd)))){
            return 1;
        }
        else if(hasInIgnoreList(cmd.code)){ // neu nam trong ignore list ma bao ve la server tra ve la false thi return 2 de biet la xu ly sau
            return 2;
        }
        //Neu respone ve la false thi hoi nguoi dung co tiep tuc hay k
        if(!continueYesNo()) // neu tra loi NO thi se thoi k lap nua 
            break;
    }
    return isNotCancel;
}
/////////////////////////////////////////////CODE FOR FILE///////////////////////////////////
int responeUploadFile(command cmd){
    return responeCommand(cmd ,"Uploading ...........\n","File name already exist\n");
}
int responeDeleteFile(command cmd){
    return responeCommand(cmd ,"Delete file success\n","File name does't exist\n");
}
int responeDownloadFile(command cmd){
    return responeCommand(cmd,"Checking information in client folder before download\n","File name does't exist\n");
}
void doDeleteFileClient(){
    doCommandClient(make_delete_file_command,responeDeleteFile);
}
void doDownloadFileClient(){
    if(doCommandClient(make_download_file_command,responeDownloadFile)){ // neu k bi nguoi dung cancel thi lam`
        saveFileWithCheck(sockfd);
    }
}
void doUploadFileClient(){
    switch(doCommandClient(make_upload_file_command,responeUploadFile)){ // neu k bi nguoi dung cancel thi lam`
        case 2:// khi trung ten file tren server
            if(!choseOverwriteCancelBoth(upload_file)) break;
        case 1:
            sendContentFile(sockfd,"Upload",currentFile);
            break;
    }
}
//////////////////////////////////////////////////Code for folder//////////////////////////
int responeNewFolder(command cmd){
    return responeCommand(cmd ,"Make new folder success\n", "File name already exist\n");
}
int responeDeleteFolder(command cmd){
    return responeCommand(cmd ,"Delete folder success\n","Folder name does't exist\n");
}
int responeOpenFolder(command cmd){
    int len = strlen(cmd.param[0]);
    (cmd.param[0])[len-7]='\0';
    if(strcmp(cmd.param[0],"false!")!=0)
        strcpy(currentFolder,getPathOfCurrentFolder(cmd.param[0]));
    // sprintf(msg,"File in folder:\n%s",cmd.param[1]);
    return responeCommand(cmd ,"","Folder name does't exist\n");
}
int responeShowContentFolder(command cmd){
    return responeCommand(cmd ,"File in folder:\n","Folder name does't exist\n");
}
int responeBackFolder(command cmd){
    char msg[1024];
    if(strcmp(cmd.param[0],"false!")!=0)
        backFolder();
    return responeCommand(cmd ,msg,"Cant back any more\n");
}
void doDeleteFolderClient(){
    doCommandClient(make_delete_folder_command,responeDeleteFolder);
}
void doNewFolderClient(){
    switch(doCommandClient(make_new_folder_command,responeNewFolder)){
        case 2:
            choseOverwriteCancelBoth(new_folder);
            printf("Make new folder success\n");
            break;
        case 1:
            
            break;
    }
}
void doOpenFolderClient(){
    if(doCommandClient(make_open_folder_command,responeOpenFolder)){
        reciveNameOfFileAndFolder(sockfd);
    }
}
void doShowContentFolderClient(){
    if(doCommandClient(make_show_content_folder_command,responeShowContentFolder)){
        reciveNameOfFileAndFolder(sockfd);
    }
}
void doBackFolderClient(){
    if(doCommandClient(make_back_folder_command,responeBackFolder)!=2){
        reciveNameOfFileAndFolder(sockfd);        
    }
}