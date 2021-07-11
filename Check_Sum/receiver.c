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
  int n=4,m=4;
  char str[] = "1001.1100.1010.0001.1101";
	int init_size = strlen(str);
	char delim[] = ".";

	char *ptr = strtok(str, delim);

    char ans[m];
    for(int i=0;i<m;i++) ans[i]='0';

	while(ptr != NULL)
	{
        char res[m];
		printf("%s\n", ptr);

        add(ans,ptr,m,res);

        for(int j=0;j<m;j++){
            ans[j]=res[j];
        }

		ptr = strtok(NULL, delim);
	}

    onesc(ans,m);

    printf("\nAns = %s",ans);



    return 0;
}
