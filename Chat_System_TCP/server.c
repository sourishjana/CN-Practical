#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<unistd.h>
#define SIZE 100

int main(int argc, char* argv[]){

  // Creating the server
  char buff[SIZE], data[SIZE];
  memset(buff,'\0',SIZE);

  // these struct will hold all the client and server details
  struct sockaddr_in server,client;

  int s_check, c_check;

  // create a socket. AF_INET is for IPV4 address scheme
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
  
  // ensures that multiple server process can be spawned for multiple clients
  int p_id = fork();
  while(1){ 
    // while loop to receive multiple clients as individual server process
    c_check = accept(s_check, (struct sockaddr*)&client, &size);
    
    while(1){ 
      // while loop to keep client channel alive
      memset(buff,'\0',SIZE);
      
      // server will receive the message from client first
      recv(c_check, buff, SIZE, 0);
      printf("\n Client Message ::  %s", buff);
      if(strcmp(buff, "bye") == 10){
        break;
      }
      memset(buff,'\0',SIZE);
      
      // after client's message is received, server can send message
      printf("\n Enter Message >  ");
      fgets(buff, SIZE, stdin);
      send(c_check, buff, SIZE, 0);
      
      // if client typed bye, then break from the loop and close connection
      if(strcmp(buff, "bye") == 10){
        break;
      }
    }
    close(c_check);
  }
  close(s_check);
  return 0;
}
