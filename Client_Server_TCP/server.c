#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<unistd.h>
#define SIZE 100


// socket is a combination of port, IP and protocols
// socket in c is BSD Berkey socket descriptor
// Two types of scoket TCP and UDP
// TCP is conncetion oriented and more secure
// max port number is 0 to s^16 - 1. Every port number is a 16 bit unsigned int

// We will be sending the Port number as command line argument
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
    printf("\n Enter Data");
    fgets(data, SIZE, stdin);
    strcpy(buff,data);

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
