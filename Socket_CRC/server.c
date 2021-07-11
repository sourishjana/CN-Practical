#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<unistd.h>
#define SIZE 100

void crc_sender(char* buffer){
  char message[SIZE], generator[SIZE], message_copy[SIZE];
  int i,j;
  long int old_msg_length;
  printf("Enter the original data : ");
  fgets(message, sizeof(message), stdin);
  printf("Enter the generator : ");
  fgets(generator, sizeof(generator), stdin);

  // removing the \n character from the end of the strings
  message[strlen(message) - 1] = '\0';
  generator[strlen(generator) - 1] = '\0';

  // holding the actual message and the actual message length
  old_msg_length = strlen(message);
  strcpy(message_copy, message);

  // concatenating strlen(generator) - 1 number of zeroes to the end of message
  for(i=0; i< strlen(generator) - 1; i++){
    strcat(message, "0");
  }

  // remainder finding algorithm
  // after this, the whole message will contain only the remainder
  for(i=0;i<old_msg_length;i++){
    if(message[i] == '1'){
      for(j=0;j<strlen(generator);j++){
        if(message[i+j] == generator[j]){
          message[i+j] = '0';
        }
        else{
          message[i+j] = '1';
        }
      }
    }
  }

  // printf("%s", message);

  // now copy the lost bits on the actual message from message_copy
  for(i=0;i<old_msg_length;i++){
    message[i] = message_copy[i];
  }
  strcpy(buffer,message);
}

int main(int argc, char* argv[]){

  // Creating the server
  char buff[SIZE], data[SIZE];
  memset(buff,'\0',SIZE);

  // these struct will hold all the client and server details
  struct sockaddr_in server,client;

  int s_check, c_check;

  s_check = socket(AF_INET, SOCK_STREAM, 0);
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
    c_check = accept(s_check, (struct sockaddr*)&client, &size);

    crc_sender(data);
    strcpy(buff,data);

    send(c_check, buff, SIZE, 0);

    recv(c_check, buff, SIZE, 0);
    printf("\nReceived dataword : %s\n", buff);

    close(c_check);
  }

  close(s_check);
  return 0;
}
