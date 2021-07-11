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

void add(char* s1,char* s2,int n,char* res){
  char carry='0';
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

int cheksum_checker(char *str){
  int n=4,m=4;  // static may change
  // char str[] = "1001.1100.1010.0001.1101";
	int init_size = strlen(str);
	char delim[] = ".";

	char *ptr = strtok(str, delim);

    char ans[m];
    for(int i=0;i<m;i++) ans[i]='0';

	while(ptr != NULL){
    char res[m];
    printf("%s\n", ptr);

    add(ans,ptr,m,res);

    for(int j=0;j<m;j++){
        ans[j]=res[j];
    }

		ptr = strtok(NULL, delim);
	}

    onesc(ans,m);
    for(int i=0;i<m;i++){
      if(ans[i] != '0') return 0;
    }
    return 1;
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
  printf("\n codeword recv from sender is %s \n",buff);

  int res = cheksum_checker(buff);
  if(res){
    send(c_check, "correct data received", 100, 0);
  }
  else {
    send(c_check, "wrong data", 100, 0);
  }

  // // resends the received data to the server
  // send(c_check, buff, 100, 0);

  // closing the channel
  close(c_check);
  return(0);
}
