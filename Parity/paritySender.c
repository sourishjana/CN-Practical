#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define size 100
int main(){
  char stream[size], code[size];
  int prompt, count = 0, i;
  printf("Enter the data stream: ");
  fgets(stream, sizeof(stream), stdin);
  do{
    printf("1 even parity. \n2 odd parity. \n3 exit:\n");
    scanf("%d", &prompt);
    for(int i=0; i<strlen(stream); i++){
      if(stream[i] == '1')  count++;
    }
    switch(prompt){
      case 1:
        for(i=0;i<strlen(stream);i++){
          code[i] = stream[i];
        }
        if(count % 2 != 0){
          code[i-1] = '1';
          code[i] = '\0';
        }
        else{
          code[i - 1] = '0';
          code[i] = '\0';
        }
        printf("The code is : %s\n", code);
        return 0;

      case 2:
        for(i=0;i<strlen(stream);i++){
          code[i] = stream[i];
        }
        if(count % 2 == 0){
          code[i-1] = '1';
          code[i] = '\0';
        }
        else{
          code[i - 1] = '0';
          code[i] = '\0';
        }
        printf("The code is : %s\n", code);
        return 0;

      case 3 : return 0;
      default:
        printf("Wrong input\n");
    }

  }while(1);

  return 0;
}



/*

101000011

no of 1's = 4 = even

even parity: (as the no of 1's are even) -> add 0

1010000110

101000000 0


odd parity: (if no of 1's are even -> add 1 -> make it odd)


disadvantage:
It can only detect only one bit error


*/