#include"AWGN.h"
#ifndef AWGN_H		//避免重複include 
#define AWGN_H
#endif


#include<stdio.h>
#include<stdlib.h>
#include <string.h>



int main(){
	const int n=1944;
	const int k=972;
	const double R=(double)k/n; //coderate
	
	//H   (n-k)*n
	
	int dv = 11;	//col weight
	int dc = 8; //row weight
	
					
	//Construct adjacency list
	
	//讀取有1之行數列數
	 
	FILE *fp1 = fopen("H_1944_972_optimal_update.txt", "r");
	if (fp1 == NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }
    
    int col[1944];		//number of colnonzero 
    
    for(int i=0;i<n;i++){
    	fscanf(fp1,"%d ",&col[i]);
    	
	}
	
	int row[972];		//number of colnonzero 
    
    for(int i=0;i<(n-k);i++){
    	fscanf(fp1,"%d ",&row[i]);	
	}	
	
	
	
	//Construct adjacency list
	//VN 
	int** VN_set = (int **)malloc(sizeof(int*) * n);
	for(int i=0;i<n;i++){
		VN_set[i] = (int *)malloc(sizeof(int) * col[i]);
	}
	//CN
	int** CN_set = (int **)malloc(sizeof(int*) * (n-k));
	for(int i=0;i<n-k;i++){
		CN_set[i] = (int *)malloc(sizeof(int) * row[i]);
	}	

	
	
	int i = 0;
	int c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11;
	while(fscanf(fp1,"%d %d %d %d %d %d %d %d %d %d %d",&c1,&c2,&c3,&c4,&c5,&c6,&c7,&c8,&c9,&c10,&c11)){
		//printf("%d %d %d %d %d %d %d %d %d %d %d\n",c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11);
		
		//col[i] 為該VN之權重 
		
		if(col[i]>0){
			if(c1!=0) 
				VN_set[i][0] = c1-1;
			else
				VN_set[i][0] = -1;
		}
		if(col[i]>1){
			if(c2!=0) 
				VN_set[i][1] = c2-1;
			else
				VN_set[i][1] = -1;
		} 
		if(col[i]>2){
			if(c3!=0) 
				VN_set[i][2] = c3-1;
			else
				VN_set[i][2] = -1;	
		} 
		if(col[i]>3){
			if(c4!=0) 
				VN_set[i][3] = c4-1;
			else
				VN_set[i][3] = -1;
		} 
		if(col[i]>4){
			if(c5!=0) 
				VN_set[i][4] = c5-1;
			else
				VN_set[i][4] = -1;
		} 
		if(col[i]>5){
			if(c6!=0) 
				VN_set[i][5] = c6-1;
			else
				VN_set[i][5] = -1;
		} 
		if(col[i]>6){
			if(c7!=0) 
				VN_set[i][6] = c7-1;
			else
				VN_set[i][6] = -1;
		} 
		if(col[i]>7){
			if(c8!=0) 
				VN_set[i][7] = c8-1;
			else
				VN_set[i][7] = -1;
		}
		if(col[i]>8){ 
			if(c9!=0) 
				VN_set[i][8] = c9-1;
			else
				VN_set[i][8] = -1;
		}
		if(col[i]>9){ 
			if(c10!=0) 
				VN_set[i][9] = c10-1;
			else
				VN_set[i][9] = -1;
		}
		if(col[i]>10){ 
			if(c11!=0) 
				VN_set[i][10] = c11-1;
			else
				VN_set[i][10] = -1;
		}
		
		if(i==n-1)
			break;
		i++;
	}
	i=0;
	while(fscanf(fp1,"%d %d %d %d %d %d %d %d",&c1,&c2,&c3,&c4,&c5,&c6,&c7,&c8)){
		//printf("%d %d %d %d %d %d %d %d\n",c1,c2,c3,c4,c5,c6,c7,c8);
		
		//row[i] 為該 CN之權重 
		
		if(row[i]>0){
			if(c1!=0) 
				CN_set[i][0] = c1-1;
			else
				CN_set[i][0] = -1;
		}
		if(row[i]>1){
			if(c2!=0) 
				CN_set[i][1] = c2-1;
			else
				CN_set[i][1] = -1;
		} 
		if(row[i]>2){
			if(c3!=0) 
				CN_set[i][2] = c3-1;
			else
				CN_set[i][2] = -1;	
		} 
		if(row[i]>3){
			if(c4!=0) 
				CN_set[i][3] = c4-1;
			else
				CN_set[i][3] = -1;
		} 
		if(row[i]>4){
			if(c5!=0) 
				CN_set[i][4] = c5-1;
			else
				CN_set[i][4] = -1;
		} 
		if(row[i]>5){
			if(c6!=0) 
				CN_set[i][5] = c6-1;
			else
				CN_set[i][5] = -1;
		} 
		if(row[i]>6){
			if(c7!=0) 
				CN_set[i][6] = c7-1;
			else
				CN_set[i][6] = -1;
		} 
		if(row[i]>7){
			if(c8!=0) 
				CN_set[i][7] = c8-1;
			else
				CN_set[i][7] = -1;
		}
		
		
		
		if(i==(n-k)-1)
			break;
		i++;
	}

	fclose(fp1);
	
	
					
	
	
	for(int i=0;i<n;i++){ 
		for(int j=0;j<col[i];j++){
			printf("%d ",VN_set[i][j]);
		}
		printf("\n");
	}
	 
	for(int i=0;i<(n-k);i++){ 
		for(int j=0;j<row[i];j++){
			printf("%d ",CN_set[i][j]);
		}
		printf("\n");
	}
	return 0;
}
	
