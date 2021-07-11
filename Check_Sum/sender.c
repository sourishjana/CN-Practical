#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


void add(char* s1,char* s2,int n,char* res){
    char carry='0';
    //char res[n];
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
        //strcpy(ans,res);
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


int main(){
  int n,m;
  scanf("%d %d",&n,&m);
  char packet[n][m];
  for(int i=0; i<n;i++){
      scanf("%s",packet[i]);
  }

  char codeword[10000]="";

  char ans[m];
  for(int j=0;j<m;j++) ans[j]=packet[0][j];


  char inter0[m];
  int k=0;
  for(int j=0;j<m;j++)
      inter0[j]=packet[0][j];

  for(int j=0;j<m;j++){
      codeword[k++]=inter0[j];
  }
  codeword[k++]='.';
  for(int i=1;i<n;i++){
      char res[m];
      char inter[m];

      add(ans,packet[i],m,res);

      for(int j=0;j<m;j++){
          ans[j]=res[j];
          inter[j]=packet[i][j];
      }

      for(int j=0;j<m;j++){
          codeword[k++]=inter[j];
      }
      codeword[k++]='.';

  }

  onesc(ans,m);
  for(int j=0;j<m;j++){
      codeword[k++]=ans[j];
  }
  printf("%s",codeword);
  return 0;
}
