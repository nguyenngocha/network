enum{
    download_file=1,
    delete_file=2,
    upload_file=3,
    new_folder=4,
    delete_folder =5,
    open_folder =6
}command_file;
long getFileSize(FILE *f){
    long size;
    fseek(f, 0L, SEEK_END);
    size=ftell(f);
    fseek(f, 0L, SEEK_SET);
    return size;
}
long sendFileSize(FILE *f,int sock){
    long fileSize;
    char *size=(char*)malloc(12*sizeof(char));
    sprintf(size,"%ld",fileSize=getFileSize(f));
    send(sock,size,strlen(size),0);
    return fileSize;
}
void saveContentFile(int sock, char * action){
    FILE *f=fopen(currentFile,"wb");
    int fileSize=reciveFileSize(sock),countByteRecived=0,reciveBytes;
    send(sock,"ready",1024,0);
    printf("%sing................\n",action);
    while(countByteRecived<fileSize){
	    reciveBytes = recv(sock,buff,1024,0);
	    send(sock,"ok",1024,0);
	    countByteRecived +=reciveBytes;
	    if(reciveBytes<=0){
	    	break;	
	    }
	    fwrite(buff, 1, reciveBytes, f);
    }
    printf("Done\n");
}
// send ten file lay tu currentFile o bien toan cuc 
void sendContentFile(int sock,char * action){
    FILE *f = fopen(currentFile,"rb");
    int n,fileSize,sentBytes,countByteSend=0;
    fileSize = (int)sendFileSize(f,sock);
    printf("Waiting for other side ready to %s\n",action);
    recv(sock,buff,1024,0);// wait client respone when it ready
    printf("OK. Other side is ready!\n");
    printf("Doing.....\n");
    while(countByteSend<fileSize){
        n=fread(buff,1,1024,f);
        sentBytes= send(sock,buff,n,0);
        recv(sock,buff,1024,0);
        countByteSend+=sentBytes;
    }
    printf("done\n");
    fclose(f);
}
// tra ve filesize
int reciveFileSize(int sock){
    char fileSize[1024];
    recv(sock,fileSize,1024,0);
    return atoi(fileSize);
}

void lower(char * str){
    int i = 0;  
    while(str[i]!='\0'){
        if(str[i]>='A'&&str[i]<='Z'){
            str[i]+=32;
        }
        i++;
    }
}
int yesNoQuestion(char * question){
    char answer[10];
    printf("%s",question);
    // printf("Do you want to continue(Yes/No)? ");
    while(1){
        gets(answer);
        lower(answer);
        if(strcmp(answer,"yes")==0||strcmp(answer,"y")==0)
            return 1;
        else if(strcmp(answer,"no")==0||strcmp(answer,"n")==0)
            return 0;
        printf("Please input yes no to answer!\n");
    }    
}
int continueYesNo(){
    return yesNoQuestion("Do you want to continue(Yes/No)? ");
}
//Kiem tra ten file da ton tai chua neu chua return 1
int checkFileExist(char *filename){
    // if(fopen(filename,"r")!=NULL)
    //     return 1;
    // return 0;
    return fopen(filename,"r")==NULL?0:1;
}
int checkFolderExist(char *folderName){
    char command[256];
    sprintf(command,"cd %s",folderName);
    return popen(command,"r")==NULL?0:1;
    // if(popen(command,"r")!=NULL)
    //     return 1;
    // return 0;
}
char *make_command_client(int comCode, char* attr1, char* attr2){
    if(attr1==NULL) return NULL;
    return make_command(comCode,attr1,attr2);
}
//Luu ten file dang xu ly vao currentFile
char* make_message(char*message,int check_file_exist){
    while(1){
        printf("%s",message);
        gets(currentFile);
        if(check_file_name_condition(currentFile))
            if(check_file_exist){
              if(checkFileExist(currentFile)) return currentFile;
              printf("File name is not exist\n");
            }else return currentFile;
        if(!continueYesNo())  break;
    }
    return NULL;
}
char* make_message_folder(char*message){
    char* folder = (char*)malloc(100*sizeof(char));
    while(1){
        printf("%s",message);
        gets(folder);
        strcat(folder,"-folder");
        if(check_file_name_condition(folder))
            return folder;
        else if(!continueYesNo()) break;
    }
    return NULL;
}
// tao lenh cho file
char* make_download_file_command(){ 
    return make_command_client( download_file, make_message("Download file name: ",0), NULL);
}
char* make_delete_file_command(){
    return make_command_client(delete_file,make_message("Delete file name: ",0),NULL);
}
char* make_upload_file_command(){
    return make_command_client(upload_file,make_message("Upload file name: ",1),NULL);
}
//tao lenh cho folder
char* make_delete_folder_command(){
    return make_command_client(delete_folder,make_message_folder("Delete folder name: "),NULL);    
}
char* make_open_folder_command(){
    return make_command_client(open_folder,make_message_folder("Open folder name: "),NULL);    
}
char* make_new_folder_command(){
    return make_command_client(new_folder,make_message_folder("create folder name: "),NULL);    
}
int check_file_name_condition(char *filename){
    int i=0;
    if(strlen(filename)<=0) {printf("File name must not empty\n"); return 0;}
    if(isdigit(filename[0])){printf("File name must not begin with number\n"); return 0;}
    while(filename[i]!='\0'){
        if((filename[i]<'a' || filename[i]>'z')&& 
           (filename[i]<'A' || filename[i]>'Z')&&
           (filename[i]<'0' || filename[i]>'9')&&
           filename[i]!='_'&&filename[i]!='.'){
            printf("File name only can have a-z A-Z 0-9 _ .\n");
            return 0;
           }
        i++;
    }
    return 1;
}

///////////////////////////////////////////////////////////////////////////////
int sendCommand(int sock,char *command){
    if(command==NULL){
        return 0;
    }
    send (sock,command,strlen(command),0);
    return 1;
}
command reciveRespond(int sock){
    char buff[1024];
    int reciveBytes;
    reciveBytes= recv(sock,buff,1024,0);
    buff[reciveBytes]='\0';
    return analyzeCommand(buff);
}
void changeFilenameToDifferrent(){
    while(1){
        if(checkFileExist(currentFile))// doi ten file den khi nao k trung thi thoi
            changeFilename();
        else
            break;
    }
}
void changeFilename(){
    char temp[200],afterPoint[100];
    int lenCurrentFile = strlen(currentFile);
    int i = lenCurrentFile-1,j=lenCurrentFile-1,k,l;
    while(currentFile[i]!='.'&&i>=0){// tim xem co dau'. hay k
      i--;  
    }
    k=i;
    if(i>=0){
        while(currentFile[k]!='\0'){// lay chuoi ki tu sau dau .
            afterPoint[k-i]=currentFile[k+1];
            k++;
        }
    }
    if(i>0){
        j=i-1;
        while(currentFile[j]!='_'&&j>=0){// tim xem co dau'_trc dau .  hay k
          j--;  
        }
    }else{
        while(currentFile[j]!='_'&&j>=0){// tim xem co dau'_ hay k
          j--;  
        }
    }
    if(j<i&&j>=0){// neu la chuoi co dang *_*.*
        k=i;
        temp[i-j-1]='\0';
        while(i>j+1){// lay chuoi ki tu nam giua _ va .
            temp[i-j-2]=currentFile[i-1];
            i--;
        }
        printf("%s\n",temp);
        if((i=atoi(temp))){//neu temp la so !=0
            currentFile[j]='\0';
            sprintf(currentFile,"%s_%d.%s",currentFile,i+1,afterPoint);
        }else{// neu giua dau _ va . k phai la so thi them _1 dang sau
            sprintf(currentFile,"_%s_1.%s",temp,afterPoint);
        }
    }else if(j>=0&&i<0){ // neu la chuoi ki tu co dang *_* va k co dau .
        i=0;
        k=j;
        while(j<lenCurrentFile){//temp la chuoi ki tu sau dau _
            j++;
            temp[i]=currentFile[j];
            i++;
        }
        if((i=atoi(temp))){//neu temp la so !=0
            currentFile[k]='\0';
            sprintf(currentFile,"%s_%d",currentFile,i+1);
        }else{// neu sau dau _ k phai la so thi them _1 dang sau
            sprintf(currentFile,"%s_1",currentFile);
        }
    }else if(i>=0){//neu chuoi co dang .* thi in cai _1 vao cuoi
        currentFile[i]='\0';
        sprintf(currentFile,"%s_1.%s",currentFile,afterPoint);
    }else
        sprintf(currentFile,"%s_1",currentFile);
}
