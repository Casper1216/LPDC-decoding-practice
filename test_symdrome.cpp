#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<stdbool.h>
int main(){
	
	int dv = 2;	//col weight
	int dc = 3; //row weight
	int u[6] = {0,0,0,0,0,0};
	int H[3][6]= {	{1,0,0,1,0,1},
					{1,1,0,0,1,0},
					{0,1,1,0,0,1}};

	int* s = (int *)malloc(sizeof(int) * 3);
	int* u_hat = (int *)malloc(sizeof(int) * 6);
	
	
	bool iszerovector = true;
	for(int j=0;j<3;j++){
		s[j] =0;
		for(int i=0;i<6;i++){
						
			s[j] += u[i]*H[j][i];
					
		}
		
		s[j] %=2;
		printf("%d\n",s[j]);
		
		if(s[j]!=0){
			iszerovector = false;
			
		}
					
	}
	printf("%d",iszerovector);
	
	return 0;
}

