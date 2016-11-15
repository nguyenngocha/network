enum{
    download_file = 1,
    delete_file=2,
    upload_file=3,
    new_folder=4,
    delete_folder =5,
    open_folder =6,
    back_folder =7,
    show_content_folder=8
}command_file;
void makeNewFolder(char * folderName){
    char command[256];
    sprintf(command,"mkdir %s",folderName);
    printf("%s\n",command);
    system(command);
}
char *commandOpenFolder(char *name){
    char command[256];
    sprintf(command,"ls %s",name);
    return command;
}
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
void saveContentFile(int sock, char * action, char* filePath){
    printf("Save Content File:\n");
    FILE *f=fopen(filePath,"wb");
    printf("File name is: %s\n", filePath);
    int fileSize=reciveFileSize(sock),countByteRecived=0,reciveBytes;
    printf("File size: %d\n",fileSize);
    send(sock,"ready",1024,0);
    printf("%sing................\n",action);
    while(countByteRecived<fileSize){
	    reciveBytes = recv(sock,buff,1024,0);
	    send(sock,"ok",1024,0);
	    countByteRecived +=reciveBytes;
	    printf("\rRecived: %d%%",countByteRecived*100/fileSize);
	    if(reciveBytes<=0){
	    	break;	
	    }
	    fwrite(buff, 1, reciveBytes, f);
    }
    fclose(f);
    printf("\nDone\n");
}
// send ten file lay tu currentFile o bien toan cuc 
void sendContentFile(int sock,char * action,char *filePath){
    FILE *f = fopen(filePath,"rb");
    int n,fileSize,sentBytes,countByteSend=0;
    fileSize = (int)sendFileSize(f,sock);
    printf("Waiting for other side ready to %s\n",action);
    while(strcmp(buff,"ready")!=0)
        recv(sock,buff,1024,0);// wait client respone when it ready
    printf("OK. Other side is ready!\n");
    printf("Doing.....\n");
    while(countByteSend < fileSize){
        n=fread(buff,1,1024,f);
        sentBytes= send(sock,buff,n,0);
        while(strcmp(buff,"ok"))
            recv(sock,buff,1024,0);
        countByteSend+=sentBytes;
        printf("\rsend: %d%%",countByteSend*100/fileSize);
    }
    printf("\ndone\n");
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
    printf("%s%s",KYEL,question,KGRN);
    // printf("Do you want to continue(Yes/No)? ");
    while(1){
        gets(answer);
        lower(answer);
        printf("%s",KNRM);
        if(strcmp(answer,"yes")==0||strcmp(answer,"y")==0)
            return 1;
        else if(strcmp(answer,"no")==0||strcmp(answer,"n")==0)
            return 0;
        printf("%sPlease input yes no to answer!\n",KYEL);
    }    
}
int continueYesNo(){
    return yesNoQuestion("Do you want to continue(Yes/No)? ");
}
//Kiem tra ten file da ton tai chua neu chua return 1
int checkFileExist(char *filename){
    FILE *f;
    if((f=fopen(filename,"r"))==NULL)// neu k mo dc thi van la null nen k phai close nua
        return 0;
    fclose(f);
    return 1;
}

int checkFolderExist(char *folderName){
    char command[256];
    sprintf(command,"cd %s",folderName);
    if(system(command)){
        return 0;
    }
    return 1;
}

char *make_command_client(int comCode, char* attr1, char* attr2){
    if(attr1==NULL) return NULL;
    return make_command(comCode,attr1,attr2);
}
//Luu ten file dang xu ly vao currentFile
//Chua sau ve convention
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
        if(check_file_name_condition(folder)){
			strcat(folder,"-folder");
            return folder;
		}
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
char* make_show_content_folder_command(){
    return make_command_client(show_content_folder,"",NULL);
}
char* make_back_folder_command(){
    return make_command_client(back_folder,"",NULL);
}
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
    if(strlen(filename)<=0) {printf("Input string must not empty\n"); return 0;}
    
    if(strlen(filename)>30){
	printf("Input string too long\n");
	return 0;
    }
    if(isdigit(filename[0])){printf("Input string must not begin with number\n"); return 0;}
    while(filename[i]!='\0'){
        if((filename[i]<'a' || filename[i]>'z')&& 
           (filename[i]<'A' || filename[i]>'Z')&&
           (filename[i]<'0' || filename[i]>'9')&&
           filename[i]!='_'&&filename[i]!='.'){
            printf("Input string only can have a-z A-Z 0-9 _ .\n");
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
//Chua sau ve convention
char * changeFilename(char *name){
    char temp[200],afterPoint[100];
    int lenCurrentFile = strlen(name);
    int i = lenCurrentFile-1,j=lenCurrentFile-1,k,l;
    while(name[i]!='.'&&i>=0){// tim xem co dau'. hay k
      i--;  
    }
    k=i;
    if(i>=0){
        while(name[k]!='\0'){// lay chuoi ki tu sau dau .
            afterPoint[k-i]=name[k+1];
            k++;
        }
    }
    if(i>0){
        j=i-1;
        while(name[j]!='_'&&j>=0){// tim xem co dau'_trc dau .  hay k
          j--;  
        }
    }else{
        while(name[j]!='_'&&j>=0){// tim xem co dau'_ hay k
          j--;  
        }
    }
    if(j<i&&j>=0){// neu la chuoi co dang *_*.*
        k=i;
        temp[i-j-1]='\0';
        while(i>j+1){// lay chuoi ki tu nam giua _ va .
            temp[i-j-2]=name[i-1];
            i--;
        }
        if((i=atoi(temp))){//neu temp la so !=0
            name[j]='\0';
            sprintf(name,"%s_%d.%s",name,i+1,afterPoint);
        }else{// neu giua dau _ va . k phai la so thi them _1 dang sau
            sprintf(name,"_%s_1.%s",temp,afterPoint);
        }
    }else if(j>=0&&i<0){ // neu la chuoi ki tu co dang *_* va k co dau .
        i=0;
        k=j;
        while(j<lenCurrentFile){//temp la chuoi ki tu sau dau _
            j++;
            temp[i]=name[j];
            i++;
        }
        if((i=atoi(temp))){//neu temp la so !=0
            name[k]='\0';
            sprintf(name,"%s_%d",name,i+1);
        }else{// neu sau dau _ k phai la so thi them _1 dang sau
            sprintf(name,"%s_1",name);
        }
    }else if(i>=0){//neu chuoi co dang .* thi in cai _1 vao cuoi
        name[i]='\0';
        sprintf(name,"%s_1.%s",name,afterPoint);
    }else
        sprintf(name,"%s_1",name);
}

void* changeNameToDifferrent(char *name){
    while(1){
        if(checkFileExist(name)){// doi ten file den khi nao k trung thi thoi
            changeFilename(name);
        }
        else
            break;
    }
}

char * changeFolderName(char * name){
    int nameSize = strlen(name),i,j,k;
    char temp[256];
    name[nameSize-7]='\0';
    i=strlen(name);
    while(name[i]!='_'&&i>0){
        i--;
    }
    j=strlen(name)-1;
    k=j;
    while(j>i&&j>=0){
        temp[j-i-1]=name[j];
        j--;
    }
    temp[k-i]='\0';
    j=atoi(temp);
    if(j){
        name[i+1]='\0';
        sprintf(name,"%s%d-folder",name,j+1);
    }else{
        if(i>0){
            name[k]='\0';
        }
        sprintf(name,"%s_1-folder",name);
    }
    return name;
}
char* getPathOfCurrentFolder(char *folder){
    char path[256],temp[256];
    if(strlen(currentFolder)){
        strcpy(temp,folder);
        sprintf(path,"%s/%s",currentFolder,temp);
    }else{
        sprintf(path,"%s",folder);
    }
    return path;
}
void changeFolderNameToDifferrence(char *name){
    char path[256];
    while(1){
        strcpy(path,getPathOfCurrentFolder(name));
        if(checkFolderExist(path)){// doi ten file den khi nao k trung thi thoi
            changeFolderName(name);
        }
        else
            break;
    }
}

char* getPathOfCurrentFile(){
    char path[256];
    if(strlen(currentFolder)){
        sprintf(path,"%s/%s",currentFolder,currentFile);
    }else{
        sprintf(path,"%s",currentFile);
    }    
    return path;
}
void backFolder(){
    splitFromEnd(currentFolder,'/');
}
void * getAnyThingInFolder(char *folderPath,int sock){
    char command[1024];
    strcpy(command,commandOpenFolder(folderPath));
    FILE *folder = popen(command,"r");
    while (fgets(buff, sizeof(buff)-1, folder) != NULL) {
        send(sock,buff,1024,0);
        buff[0]="\0";
        while(strcmp(buff,"ok"))
            recv(sock,buff,1024,0);
    }
    send(sock,"done-all\n",1024,0);// them \n o day cho cung form vs luc doc folder o phia tren
    pclose(folder);
}
void reciveNameOfFileAndFolder(int sock){
    buff[0]='\0';
    int lenBuff;
    char word[7]="-folder";
    while(1){
        recv(sock,buff,1024,0);
        buff[strlen(buff)-1]='\0';
        if(strcmp(buff,"done-all")==0){ 
            return;
        }
        if(strstr(buff, word) != NULL){
            buff[strlen(buff)-7]='\0';// bo duoi -folder di
            printf("     %s%s/%s\n",BKGRN,buff,KNRM);
        }
        else
            printf("     %s\n",buff);
        send(sock,"ok",1024,0);
    }
    
}