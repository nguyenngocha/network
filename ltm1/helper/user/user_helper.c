// chi dung cac gia tri tu 20 tro len vd login = 20
enum{
  login = 20,
  logout = 21,
  signup = 22,
  delete = 23,
  add = 24
}command_user;
char* make_login_command(){
  char* name = (char*)malloc(100*sizeof(char));
  char* pass = (char*)malloc(100*sizeof(char));
  printf("Nhap UserName: \n");
  gets(name);
  printf("Nhap Password: \n");
  gets(pass);
  return make_command( login, name, pass);
}

char* make_logout_command(){
  return make_command( logout, NULL, NULL);
}

char* make_signup_command(){
  return make_login_command();
}
