#include<stdio.h>
#include<stdlib.h>

int main()
{
    

	//讀取 txt 
	FILE *fp1 = fopen("H_1944_972_2.txt", "r");
	if (fp1 == NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }
	int row = 972;
	int col = 1944;
	
	int** H = (int**)malloc(sizeof(int*)*row);
	for(int i=0;i<row;i++){
		H[i] = (int*)malloc(sizeof(int)*col);
	}
	
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			H[i][j] = 0;
		}	
	}
	
	int r = 0;
	int c1,c2,c3,c4,c5,c6,c7,c8;
	while(fscanf(fp1,"%d %d %d %d %d %d %d %d",&c1,&c2,&c3,&c4,&c5,&c6,&c7,&c8)){
		//printf("%d %d %d %d %d %d %d %d",c1,c2,c3,c4,c5,c6,c7,c8);
		
		if(c1!=0) 
			H[r][c1-1] = 1;
		if(c2!=0) 
			H[r][c2-1] = 1;
		if(c3!=0) 
			H[r][c3-1] = 1;
		if(c4!=0) 
			H[r][c4-1] = 1;
		if(c5!=0) 
			H[r][c5-1] = 1;
		if(c6!=0) 
			H[r][c6-1] = 1;
		if(c7!=0) 
			H[r][c7-1] = 1;
		if(c8!=0) 
			H[r][c8-1] = 1;
		
		if(r==row-1)
			break;
		r++;
		
	}

	
	
	fclose(fp1);
	
	
	
	//寫入 CSV
	FILE *fp = fopen("H_matrix.csv", "w");
    
    //避免開啟失敗 
    if (fp == NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }
    //int q=1;
    for(int i=0;i<row;i++){
    	//printf("%d %d\n",q++,H[i][0]);
		for(int j=0;j<col;j++){
			
			fprintf(fp, "%d,",H[i][j]);
			
		}	
		
		fprintf(fp, "\n");
	}
	
	/*
    fprintf(fp, "ID,Name,Points\n");	// 換一列  \n		
    fprintf(fp, "1,qwe,1.1\n");
	fprintf(fp, "3,\"z,xc\",3.3\n");
	
    // special symbols
    fprintf(fp, "3,\"z,xc\",3.3\n");
    fprintf(fp, "4,\"qw\nas\",4.4\n");
    fprintf(fp, "5,\"\"aszx\"\",5.5\n");
    */

	fclose(fp1);
    fclose(fp);
    
    

    
    
    return 0;
}
