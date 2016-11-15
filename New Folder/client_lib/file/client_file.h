void sendCommandNewFolder(char *command){
    send (sockfd,command,strlen(command),0);
}
command reciveRespond(){
    recv(sockfd,buff,1024,0);
    return analyzeCommand(buff);
}