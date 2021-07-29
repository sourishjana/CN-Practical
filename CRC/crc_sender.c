#include <stdio.h>
#include <string.h>
#define s 100
int main(){
  char message[s], generator[s], message_copy[s];
  int i,j;
  long int old_msg_length;
  printf("Data : ");
  fgets(message, sizeof(message), stdin);
  printf("Generator : ");
  fgets(generator, sizeof(generator), stdin);

  message[strlen(message) - 1] = '\0';
  generator[strlen(generator) - 1] = '\0';

  old_msg_length = strlen(message);
  strcpy(message_copy, message);

  for(i=0; i< strlen(generator) - 1; i++){
    strcat(message, "0");
  }

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
  for(i=0;i<old_msg_length;i++){
    message[i] = message_copy[i];
  }
  printf("Message = %s\n",message);
  return 0;
}



/*

1010101010|0000
11001

011000
 11001

 000011010
     11001

     00011000
        11001

        000010


1010101010|0010
11001

011000
 11001

 000011010
     11001

     00011001
        11001

        000000




*/ 