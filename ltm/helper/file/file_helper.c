enum{
    download_file=1,
    delete_file=2,
    upload_file=3,
    new_folder=4,
    delete_folder =5,
    open_folder =6
}command_file;
char *make_command_client(int comCode, char* attr1, char* attr2){
    if(attr1==NULL) return NULL;
    return make_command(comCode,attr1,attr2);
}
char* make_message(char*message){
    while(1){
        printf(message);
        gets(currentFile);
        if(check_file_name_condition(currentFile))
            return currentFile;
        else if(!continueYesNo()) break;
    }
    return NULL;
}
char* make_message_folder(char*message){
    char* folder = (char*)malloc(100*sizeof(char));
    while(1){
        printf(message);
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
    return make_command_client( download_file, make_message("Download file name: "), NULL);
}
char* make_delete_file_command(){
    return make_command_client(delete_file,make_message("Delete file name: "),NULL);
}
char* make_upload_file_command(){
    return make_command_client(upload_file,make_message("Upload file name: "),NULL);
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
    if(strlen(filename)<=0) {printf("File name must not empty"); return 0;}
    if(isdigit(filename[0])){printf("File name must not begin with number"); return 0;}
    while(filename[i]!='\0'){
        if((filename[i]<'a' || filename[i]>'z')&& 
           (filename[i]<'A' || filename[i]>'Z')&&
           (filename[i]<'0' || filename[i]>'9')&&
           filename[i]!='_'){
            printf("File name only can have a-z A-Z 0-9 _ \n");
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
    recv(sock,buff,1024,0);
    return analyzeCommand(buff);
}
int yesNoQuestion(char * question){
    char* answer;
    printf(question);
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
void lower(char * str){
	int i = 0;	
	while(str[i]!='\0'){
		if(str[i]>='A'&&str[i]<='Z'){
			str[i]+=32;
		}
		i++;
	}
}
//Kiem tra ten file da ton tai chua neu chua return 1
int checkFileExistInClientFolder(char *filename){
    return fopen(filename,"r")!=NULL?1:0;
}
