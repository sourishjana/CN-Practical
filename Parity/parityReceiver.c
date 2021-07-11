#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define size 100
int main(){

  char stream[size];
  int count = 0, i, prompt;
  printf("Enter the data : ");
  fgets(stream, sizeof(stream), stdin);
  printf("Enter 1 for even check. 2 for odd check: ");
  scanf("%d", &prompt);
  for(int i=0;i < strlen(stream); i++){
    if(stream[i] == '1')  count++;
  }

  if(prompt == 1){
    if(count % 2 != 0)  printf("Error in the received data\n");
    else{
      printf("The data is error free\n");
      char code[size];
      for(i=0;i<strlen(stream) - 1;i++){
        code[i] = stream[i];
      }
      printf("Data : %s\n", code);
    }
    return 0;
  }
  else{
    if(count % 2 == 0)  printf("Error in the received data\n");
    else {
      printf("The data is error free\n");
      char code[size];
      for(i=0;i<strlen(stream)-2;i++){
        code[i] = stream[i];
      }
      printf("Data : %s\n", code);
    }
    return 0;
  }

  return 0;
}
