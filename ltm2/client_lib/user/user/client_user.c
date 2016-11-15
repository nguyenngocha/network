// chi dung cac gia tri tu 20 tro len vd login = 20

char* make_login_command(){
  char loginname[30]; 
  char loginpass[30];
  do{
    printf("Nhap UserName: ");
    gets(loginname);  
  }while(!check_file_name_condition(loginname));
  do{  
    printf("Nhap Password: ");
    gets(loginpass);
  }while(!check_file_name_condition(loginpass));
  return make_command( login, loginname, loginpass);
}

char* make_logout_command(){
  return make_command( logout, NULL, NULL);
}

char* make_signup_command(){
  char signupname[30];
  char signuppass[30];
  do{
    printf("Nhap UserName: ");
    gets(signupname);
  }while(!check_file_name_condition(signupname));
  do{
    printf("Nhap Password: ");
    gets(signuppass);
  }while(!check_file_name_condition(signuppass));
  return make_command( signup, signupname, signuppass);
}
// save vao nhe?