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
// we will use flag variable to synchronize the chat
int flag = 0;

int main(int x, char * argv[]) {
  struct sockaddr_in client;
  int c_check;
  char buff[100],data[100];
  memset(buff, '\0', 100);
  memset(data, '\0', 100);
  // setting client side socket
  c_check = socket(AF_INET, SOCK_DGRAM, 0);  // c_check is called socket file descriptor

  // setting client socket parameters
  client.sin_family = AF_INET;
  client.sin_addr.s_addr = inet_addr(argv[1]); // getting the server IP from command line args
  client.sin_port = htons(atoi(argv[2])); // getting the port number from command line args

  
  memset(buff,'\0',SIZE);
  printf("\n Enter Message >  ");
  fgets(buff, SIZE, stdin);
  sendto(c_check, buff, SIZE, 0, (struct sockaddr*)&client, sizeof(client));

  int size = sizeof(client);
  memset(buff,'\0',SIZE);
  recvfrom(c_check, buff, SIZE, 0, (struct sockaddr*)&client, &size);
  printf("\n Server message ::  %s", buff);

  close(c_check);
  return(0);
}
