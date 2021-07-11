#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<unistd.h>
#define SIZE 100

int parity_check(char* stream){
  int count = 0;
  int i = 0;
  for(i=0;i < strlen(stream); i++){
    if(stream[i] == '1')  count++;
  }
  if(count % 2 != 0)  return 0;
  else{
    char code[SIZE];
    for(i=0;i<strlen(stream) - 1;i++){
      code[i] = stream[i];
    }
    printf("Data : %s\n", code);
  }
  return 1;
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

  int size = sizeof(client);
  while(1){
    c_check = accept(s_check, (struct sockaddr*)&client, &size);
    while(1){
        memset(buff,'\0',SIZE);
        recv(c_check, buff, SIZE, 0);
        printf("\n Client Code Word ::  %s\n", buff);
        int check = parity_check(buff);
        if(strcmp(buff, "bye") == 10){
          break;
        }

        memset(buff,'\0',SIZE);
        if(check == 0)
          send(c_check, "Data is corrupted", SIZE, 0);
        else
          send(c_check, "Data is error free", SIZE, 0);

        if(strcmp(buff, "bye") == 10){
          break;
        }
    }
    close(c_check);
  }

  close(s_check);
  return 0;
}
