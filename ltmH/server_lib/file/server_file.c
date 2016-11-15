void acceptAndAction(command cmd,void(*action)(int,char*,char*),char * actionName, char * path){
    sendCommand(connSock,make_command(cmd.code,currentFile,NULL));
    action(connSock,actionName,path);   
}
void doDownloadFile(command cmd){
    strcpy(currentFile,cmd.param[0]);
    char path[256];
    strcpy(path,getPathOfCurrentFile());
    if(checkFileExist(path)){
        acceptAndAction(cmd,sendContentFile,"Download",path);
    }else{
        sendCommand(connSock,make_command(cmd.code,"false!",NULL));
    }
}
void doUploadFile(command cmd){
    strcpy(currentFile,cmd.param[0]);
    char path[256];
    strcpy(path,getPathOfCurrentFile());
    if(checkFileExist(path)){
        sendCommand(connSock,make_command(cmd.code,"false!",NULL));
        command cmdResponeFromeClient=reciveRespond(connSock);
        if(strcmp(cmdResponeFromeClient.param[0],"Overwrite")==0){
            acceptAndAction(cmd,saveContentFile,"Upload",path);
        }else if(strcmp(cmdResponeFromeClient.param[0],"Keep both")==0){
            changeNameToDifferrent(path);
            acceptAndAction(cmd,saveContentFile,"Upload",path);
        }// neu ng dung chon cancel thi k lam j ca
    }else{
        acceptAndAction(cmd,saveContentFile,"Upload",path);
    }
}
void doDeleteFile(command cmd){
    strcpy(currentFile,cmd.param[0]);
    char path[256];
    strcpy(path,getPathOfCurrentFile());
    if(checkFileExist(path)){
        char command[100];
        sprintf(command,"rm %s",path);
        system(command);
        sendCommand(connSock,make_command(cmd.code,"success!",NULL));
    }else{
        sendCommand(connSock,make_command(cmd.code,"false!",NULL));
    }
    
}
///////////////////////////////CODE FOR FOLDER //////////////////////////////////////////
void doDeleteFolder(command cmd){
    char path[256];
    strcpy(path,getPathOfCurrentFolder(cmd.param[0]));
    if(checkFolderExist(path)){
        char command[100];
        sprintf(command,"rm -fr %s",path);
        system(command);
        sendCommand(connSock,make_command(cmd.code,"success!",NULL));
    }else{
        sendCommand(connSock,make_command(cmd.code,"false!",NULL));
    }
}
void doOpenFolder(command cmd){
	char * temp,path[256],tempPath[256];
	strcpy(tempPath,cmd.param[0]);
	strcpy(path,getPathOfCurrentFolder(cmd.param[0]));
	if(!checkFolderExist(path)){
		sendCommand(connSock,make_command(cmd.code,"false!",NULL));
	}else{
	    sendCommand(connSock,make_command(cmd.code,tempPath,NULL));
		getAnyThingInFolder(path,connSock);
 		sprintf(currentFolder,"%s",path);
	}
}
void doNewFolder(command cmd){
    char *temp=(char*)malloc(256*sizeof(char));
    strcpy(temp,cmd.param[0]);
    char path[256];
    strcpy(path,getPathOfCurrentFolder(cmd.param[0]));
    if(checkFolderExist(path)){
        sendCommand(connSock,make_command(cmd.code,"false!",NULL));
        command cmdResponeFromeClient=reciveRespond(connSock);
        if(strcmp(cmdResponeFromeClient.param[0],"Overwrite")==0){
            makeNewFolder(path);
        }else if(strcmp(cmdResponeFromeClient.param[0],"Keep both")==0){
            changeFolderNameToDifferrence(temp);
            strcpy(path,getPathOfCurrentFolder(temp));
            makeNewFolder(path);
        }
    }else{
        makeNewFolder(path);
        sendCommand(connSock,make_command(cmd.code,"success!",NULL));
    }
}
void doShowContentFolder(command cmd){
	    sendCommand(connSock,make_command(cmd.code,"success!",NULL));
		getAnyThingInFolder(currentFolder,connSock);
}

