//RESPONE nhan tra ve tu server
int responeCommand(command cmd, char * msg1, char* msg2){
    if(strcmp(cmd.param[0],"false!")){
        printf(msg2);
        return 0;
    }
    printf(msg1);
    return 1;
}
//DO WHAT
// ham nay se tra ve 1 command neu cmd code = 0  nghia la ham tra ve false 
int doCommandClient(char*(*make_what_command)(),int (*respone_what)(command)){
    printf("ok\n");
    int isNotCancel=0;// khoi tao the nay de neu send bi nguoi dung cancel thi isNotCancel =0
    while(1){
        if(!sendCommand(sockfd,make_what_command())) break; // neu nguoi dung cancel thi break; 
        if(respone_what(reciveRespond(sockfd))){// neu server tra ve !false thi thoat vong lap
            isNotCancel=1;
            break;
        }
        //Neu respone ve la false thi hoi nguoi dung co tiep tuc hay k
        if(!continueYesNo()){ // neu tra loi NO thi se thoi k lap nua 
            break;
        }
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
    return responeCommand(cmd,"Downloading...........\n","File name does't exist\n");
}
void doDeleteFileClient(){
    doCommandClient(make_delete_file_command,responeDeleteFile);
}
void doDownloadFileClient(){
    if(doCommandClient(make_download_file_command(),responeDownloadFile)){ // neu k bi nguoi dung cancel thi lam`
        printf("ok\n");
        saveFileWithCheck(sockfd);
    }
}
void doUploadFileClient(){
    
}

/// Phan nay ti vut vao helper.c
void sendContentFile(int sock){
    FILE *f = fopen(currentFile,"rb");
    int n;
    while((n=fread(buff,1,1024,f))>0){
        sentBytes= send(sock,buff,n,0);
    }
    fclose(f);
}
void saveFileWithCheck(int sock){
        while(1){
            if(checkFileExistInClientFolder(currentFile)){//Neu ten file chua ton tai thi tao file ms 
                saveContentFile(sock);
                break;
            }else{
                printf("File already exist !\n");
                if(yesNoQuestion("Do you want to overwrite it(Yes/No)? ")){
                    saveContentFile(sock);
                }else{
                    printf("Please input new file name: ");
                    gets(currentFile);
                }
            }
        }    
}
void saveContentFile(int sock){
    FILE *f=fopen(currentFile,"wb");
    while(1){
    reciveBytes = recv(sock,buff,1024,0);
    if(reciveBytes<=0){
    	break;	
    } 
    fwrite(buff, 1, reciveBytes, f);
    }
    printf("Download file success");
}
//////////////////////////////////////////////////BO//////////////////////////
int responeNewFolder(command cmd){
    return responeCommand(cmd ,"Make new folder success\n", "File name already exist\n");
}
int responeDeleteFolder(command cmd){
    return responeCommand(cmd ,"Delete folder success\n","Folder name does't exist\n");
}
int responeOpenFile(command cmd){
    char msg[1024];
    sprintf(msg,"File in folder: %s\n",cmd.param[1]);
    return responeCommand(cmd ,msg,"File name does't exist\n");
}
void doDeleteFolderClient(){
    doCommandClient(make_delete_folder_command,responeDeleteFolder);
}
void doNewFolderClient(){
    doCommandClient(make_new_folder_command,responeNewFolder);
}
void doOpenFolderClient(){
    doCommandClient(make_open_folder_command,responeOpenFile);
}
