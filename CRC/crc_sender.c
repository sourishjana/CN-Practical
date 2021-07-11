#include <stdio.h>
#include <string.h>
#define s 100
int main(){
  char message[s], generator[s], message_copy[s];
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
  printf("The encoded message is %s\n",message);
  return 0;
}
