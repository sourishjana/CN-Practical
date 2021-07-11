#include <stdio.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#define SIZE 100

int crc_receiver(char* message){
  char generator[SIZE], message_copy[SIZE], actual_message[SIZE];
  int i,j;
  long int old_msg_length;
  strcpy(generator, "11001");

  // holding the actual message and the actual message length
  old_msg_length = strlen(message);
  strcpy(message_copy, message);

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

  // decoding the codeword
  for(i=0;i<strlen(message_copy) - strlen(generator) + 1;i++){
    actual_message[i] = message_copy[i];
  }
  actual_message[i] = '\0';

  for(int i=0; i<strlen(message); i++){
    if(message[i] != '0'){
      return 1;
    }
  }
  strcpy(message, actual_message);
  return 0;
}

int main(int x, char * argv[]) {
  struct sockaddr_in client;
  int c_check;
  char buff[100],data[100];
  memset(buff, '\0', 100);
  memset(data, '\0', 100);
  // setting client side socket
  c_check = socket(AF_INET, SOCK_STREAM, 0);  // c_check is called socket file descriptor

  // setting client socket parameters
  client.sin_family = AF_INET;
  client.sin_addr.s_addr = inet_addr(argv[1]); // getting the server IP from command line args
  client.sin_port = htons(atoi(argv[2])); // getting the port number from command line args

  // connect() system call connects the file descriptor c_check to the address client.sin_addr.s_addr that is the server IP
  connect(c_check, (struct sockaddr*)&client, sizeof(client));

  // receives the data
  recv(c_check, buff, 100, 0);
  printf("\ncodeword recv from sender is %s \n",buff);
  int res = crc_receiver(buff);
  if(res == 0){
    // resends the received data to the server
    send(c_check, buff, 100, 0);
  }
  else{
    send(c_check, "Error in received message\n", SIZE, 0);
  }

  // closing the channel
  close(c_check);
  return(0);
}
