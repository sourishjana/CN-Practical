#include <stdio.h>
#include <string.h>
#define s 100
int main(){
  char message[s], generator[s], message_copy[s], actual_message[s];
  int i,j;
  long int old_msg_length;
  printf("Enter the received data : ");
  fgets(message, sizeof(message), stdin);
  printf("Enter the generator : ");
  fgets(generator, sizeof(generator), stdin);

  // removing the \n character from the end of the strings
  message[strlen(message) - 1] = '\0';
  generator[strlen(generator) - 1] = '\0';

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
      printf("Error message received\n");
      printf("Message received is %s\n", message_copy);
      return 0;
    }
  }

  printf("Correct message received\n");
  printf("Actual Message is %s\n", actual_message);

  return 0;
}
