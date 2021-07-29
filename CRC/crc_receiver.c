#include <stdio.h>
#include <string.h>
#define s 100
int main(){
  char message[s], generator[s], message_copy[s], actual_message[s];
  int i,j;
  long int old_msg_length;
  printf("Received data : ");
  fgets(message, sizeof(message), stdin);
  printf("Generator : ");
  fgets(generator, sizeof(generator), stdin);

  message[strlen(message) - 1] = '\0';
  generator[strlen(generator) - 1] = '\0';

  old_msg_length = strlen(message);
  strcpy(message_copy, message);

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

  for(i=0;i<strlen(message_copy) - strlen(generator) + 1;i++){
    actual_message[i] = message_copy[i];
  }
  actual_message[i] = '\0';

  for(int i=0; i<strlen(message); i++){
    if(message[i] != '0'){
      printf("Message received = %s\n", message_copy);
      return 0;
    }
  }

  printf("Actual Message is %s\n", actual_message);

  return 0;
}
