enum{
    download=1,
    delete_file=2,
    upload=3,
    new_folder=4
}command_file;
char* make_message(char*message){
    char* filename = (char*)malloc(100*sizeof(char));
    printf("%s",message);
    gets(filename);
    return filename;
}
char* make_download_command(){
    return make_command( download, make_message("download file name: "), NULL);
}
char* make_delete_command(){
    return make_command(delete,make_message("delete file name: "),NULL);
}
char* make_upload_command(){
    return make_command(upload,make_message("upload file name: "),NULL);
}
char* make_new_folder_command(){
    return make_command(new_folder,make_message("create folder name: "),NULL);    
}
int check_file_name_condition(char *filename){
    int i=0;
    if(strlen(filename)<=0) printf("File name must not empty");
    if(isdigit(filename[0])){printf("File name must not begin with number"); return 0;}
    while(filename[i]!='\0'){
        if((filename[i]<'a' || filename[i]>'z')&& 
           (filename[i]<'A' || filename[i]>'Z')&&
           (filename[i]<'0' || filename[i]>'9')&&
           filename[i]!='-'&&filename[i]!='_'){
            printf("File name only can have a-z A-Z 0-9 - _ \n");
            return 0;
           }
        i++;
    }
    return 1;
}
//client
void sendMessage(){
    
}
//Server
