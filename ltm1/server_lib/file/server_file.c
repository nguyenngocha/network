void acceptAndAction(command cmd,void(*action)(int,char*),char * actionName){
    sendCommand(connSock,make_command(cmd.code,currentFile,NULL));
    action(connSock,actionName);   
}
void doDownloadFile(command cmd){
    strcpy(currentFile,cmd.param[0]);
    if(checkFileExist(currentFile)){
        acceptAndAction(cmd,sendContentFile,"Download");
    }else{
        sendCommand(connSock,make_command(cmd.code,"false!",NULL));
    }
}
void doUploadFile(command cmd){
    strcpy(currentFile,cmd.param[0]);
    if(checkFileExist(currentFile)){
        sendCommand(connSock,make_command(cmd.code,"false!",NULL));
        command cmdResponeFromeClient=reciveRespond(connSock);
        if(strcmp(cmdResponeFromeClient.param[0],"Overwrite")==0){
            acceptAndAction(cmd,saveContentFile,"Upload");
        }else if(strcmp(cmdResponeFromeClient.param[0],"Keep both")==0){
            changeFilenameToDifferrent();
            acceptAndAction(cmd,saveContentFile,"Upload");
        }// neu ng dung chon cancel thi k lam j ca
    }else{
        acceptAndAction(cmd,saveContentFile,"Upload");
    }
}
void doDeleteFile(command cmd){
    strcpy(currentFile,cmd.param[0]);
    if(checkFileExist(currentFile)){
        char command[100];
        sprintf(command,"rm %s",currentFile);
        system(command);
        sendCommand(connSock,make_command(cmd.code,"success!",NULL));
    }else{
        sendCommand(connSock,make_command(cmd.code,"false!",NULL));
    }
    
}