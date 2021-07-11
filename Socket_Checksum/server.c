#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<unistd.h>
#define SIZE 100

void add(char* s1,char* s2,int n,char* res){
  char carry='0';
  //char res[n];
  for(int i=n-1; i>=0; i--){
      int c=0;
      if(carry=='1') c++;
      if(s1[i]=='1') c++;
      if(s2[i]=='1') c++;

      if(c==0) {res[i]='0';carry='0';}
      else if(c==1) {res[i]='1';carry='0';}
      else if(c==2){
          res[i]='0';
          carry='1';
      }else if(c==3){
          res[i]='1';
          carry='1';
      }
  }
  if(carry=='1'){
      char ans[n];
      char car[n];
      for(int i=0;i<n-1;i++){
          car[i]='0';
      }
      car[n-1]='1';
      //strcpy(ans,res);
      for(int i=0;i<n;i++){
          ans[i]=res[i];
      }
      add(ans,car,n,res);
  }
}

void onesc(char* arr,int n){
    for(int i=0;i<n;i++){
        if(arr[i]=='0') arr[i]='1';
        else arr[i]='0';
    }
}

void checksum(char* buffer){
  int n,m;
  scanf("%d %d",&n,&m);
  char packet[n][m];
  for(int i=0; i<n;i++){
      scanf("%s",packet[i]);
  }

  char codeword[10000]="";

  char ans[m];
  for(int j=0;j<m;j++) ans[j]=packet[0][j];


  char inter0[m];
  int k=0;
  for(int j=0;j<m;j++)
      inter0[j]=packet[0][j];

  for(int j=0;j<m;j++){
      codeword[k++]=inter0[j];
  }
  codeword[k++]='.';
  for(int i=1;i<n;i++){
      char res[m];
      char inter[m];

      add(ans,packet[i],m,res);

      for(int j=0;j<m;j++){
          ans[j]=res[j];
          inter[j]=packet[i][j];
      }

      for(int j=0;j<m;j++){
          codeword[k++]=inter[j];
      }
      codeword[k++]='.';

  }

  onesc(ans,m);
  for(int j=0;j<m;j++){
      codeword[k++]=ans[j];
  }
  printf("%s",codeword);
  for(int i=0; i<strlen(codeword); i++){
    buffer[i] = codeword[i];
  }
}

int main(int argc, char* argv[]){

  // Creating the server
  char buff[SIZE], data[SIZE];
  memset(buff,'\0',SIZE);

  // these struct will hold all the client and server details
  struct sockaddr_in server,client;

  int s_check, c_check;

  // create a socket. AD_INET is for IPV4 address scheme
  // SOCK_STREAM is for TCP socket
  // s_check will hold the stack details that is port number and ip of server
  s_check = socket(AF_INET, SOCK_STREAM, 0);

  // Initiating the server parameters
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(atoi(argv[1]));   // getting the port number from argv[1]

  // binds the socket to the address and port number specified in server
  bind(s_check, (struct sockaddr*)&server, sizeof(server));

  // It will listen to the client calls. 2 is the wait queue size
  listen(s_check,2);

  // an infinite while loop ensures that the server will never be terminated
  while(1){
    int size = sizeof(client);
    // accept() will receive the client and c_check will store the stack details of the actual communication channel
    // we need to typecast the client into sockaddr from sockaddr_in
    // the client structure is actually empty when passed as an argument
    // but c_check will set it with client details after it will be verified
    // thus security is maintained
    c_check = accept(s_check, (struct sockaddr*)&client, &size);

    memset(buff,'\0',SIZE);
    checksum(buff);
    printf("Success\n" );
    // strcpy(buff,data);

    // it will send data to the client
    send(c_check, buff, SIZE, 0);
    printf("\n client IP : %s\n", inet_ntoa(client.sin_addr));
    printf("\n client port : %d\n", (int)ntohs(client.sin_port));

    // it will recieve data from the client
    recv(c_check, buff, SIZE, 0);
    printf("\n Received data : %s\n", buff);

    // always close the communication channel
    close(c_check);
  }

  close(s_check);
  return 0;
}
