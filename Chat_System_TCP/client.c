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

  while(1){ // sends the data
    memset(buff,'\0',SIZE);
    printf("\n Enter Message >  ");
    fgets(buff, SIZE, stdin);
    // client will send the message first
    send(c_check, buff, 100, 0);
    if(strcmp(buff, "bye") == 10){
      // close(c_check);
      break;
    }
    memset(buff,'\0',SIZE);
    recv(c_check, buff, 100, 0);
    printf("\n Server message ::  %s", buff);
    if(strcmp(buff,"bye") == 10){
      break;
    }
  }
  // closing the channel
  close(c_check);
  return(0);
}
