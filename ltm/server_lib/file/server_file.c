void doDownloadFile(){
    command cmd=reciveRespond(connSock);
    sendCommand(connSock,make_command(download_file,"true",""));
    strcpy(currentFile,cmd.param[0]);
    sendContentFile(connSock);   
}
void sendContentFile(int sock){
    FILE *f = fopen(currentFile,"rb");
    int n;
    while((n=fread(buff,1,1024,f))>0){
        sentBytes= send(sock,buff,n,0);
    }
    fclose(f);
}