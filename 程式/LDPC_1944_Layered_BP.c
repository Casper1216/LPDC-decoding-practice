#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<stdbool.h>
#define pi acos(-1)




int main(){
	
	srand(time(0));
	// Start Record the time
    time_t  start = clock();
	
	//***************************************************************************
	//(1944,972)LDPC
	//BPSK 1 or -1
	
	
	const int n=1944;
	const int k=972;
	const double R=(double)k/n; //coderate
	
	//H   (n-k)*n
	
	int dv = 11;	//col weight
	int dc = 8; //row weight
	
	
	
	FILE *fp1 = fopen("H_1944_972_optimal_update.txt", "r");
	if (fp1 == NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }
    
    //建立 number of col row nonzero location
	 
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
	
	


	//***************************************************************************
	//channel information
	double* Fn = (double *)malloc(sizeof(double) * n);
	//tau
	double** tau= (double **)malloc(sizeof(double*) * (n-k));
	for(int i=0;i<(n-k);i++){
		tau[i] = (double *)malloc(sizeof(double) * dc);
	}
	
	
	
	//CN update //CN[j][i]  CN j to CN i
	double** CN = (double **)malloc(sizeof(double*) * (n-k));
	for(int i=0;i<(n-k);i++){
		CN[i] = (double *)malloc(sizeof(double) * dc);
	}
	
	//VN update //VN[i][j]  VN i to CN j
	double** VN = (double **)malloc(sizeof(double*) * n);
	for(int i=0;i<n;i++){
		VN[i] = (double *)malloc(sizeof(double) * dv);
	}
	
	//total LLR VN[i]
	double* VN_total = (double *)malloc(sizeof(double) * n);
	
	//decoded sequence
	int* u_hat = (int *)malloc(sizeof(int) * n);
	
	double *y = (double*)malloc(sizeof(double) * n);
	
	//**********************************************

	
	//SNR
	const int SNR_L = 1;
	double *SNR_dB = (double *)malloc(sizeof(double) * SNR_L);
	/*
	SNR_dB[0] = 0;
	SNR_dB[1] = 0.4;
	
	SNR_dB[2] = 0.8;
	
	SNR_dB[3] = 1.2;
	
	SNR_dB[4] = 1.6;
	SNR_dB[5] = 2;
	*/
	SNR_dB[0] = 0;
	
	
	//**********************************************
	//平均 iteration 
	double *avgIter = (double *)malloc(sizeof(double) * SNR_L);

	
	//sigal;
	
	//假設全為 0
	int *u = (int*)malloc(sizeof(int) * n);	//binary sequence
	int *x = (int*)malloc(sizeof(int) * n);
	
	for(int i=0;i<n;i++){
		u[i] = 0;
		x[i] = 1;		//Eb=1	Eav = R*1
	} 
	
	
	
	//**********************************************
	
	int numtime =100;
	int iteration = 50;	
	
	
	double *BER = (double*)malloc(sizeof(double) * SNR_L);
	double *FER = (double*)malloc(sizeof(double) * SNR_L);

	for(int q=0;q<SNR_L;q++){
		
		avgIter[q] = 0;
		long long error=0;
		long long frameerror=0;
		int counting=1;
		
		for(int num=0;num<numtime;num++){
			
			
			if(counting==10000){
				printf("%d\n",counting);
				counting=0;
			}
			counting++;
			//printf("%d ",num);
			
			
			//noise
			double* noise = (double *)malloc(sizeof(double) * n);
			double U ,V ;
			double sigma = sqrt((1/(2*R))*pow(10,-(SNR_dB[q]/10)));
			
			for(int i=0;i<n;i++){
				U = (double) rand() / (double)(RAND_MAX);	//uniform (0~1) 0<U<1
				while(U==0||U==1)
					U = (double) rand() / (double)(RAND_MAX);	
				
				
				V = (double) rand() / (double)(RAND_MAX);
				while(V==0||V==1)
					V = (double) rand() / (double)(RAND_MAX);	
				
				noise[i] = sqrt(-2*log(U))*cos(2*pi*V);
				noise[i] = sigma* noise[i] ;
				
				
				y[i] = x[i] + noise[i];
				
			} 
			
			//initialization
			for(int i=0;i<n;i++){
				VN_total[i] = 2*y[i]/(pow(sigma,2));
				
			}
			
			for(int j=0;j<(n-k);j++){	
				for(int i=0;i<row[j];i++){
						
					CN[j][i] = 0;	
				}
			}
			//iterative decoding
			int iter=0;
			
			for(iter=0;iter<iteration;iter++){
				
				
				
				
				//CN update	
				for(int j=0;j<(n-k);j++){	
					for(int i=0;i<row[j];i++){
						
						tau[j][i] = 1;	
					}
				}
				
				
				for(int j=0;j<(n-k);j++){					//go through all CN	
				
				
					//對此CN 相連之VN 先update (用上一個 layer 所得之 VN_total 
					
					for(int i=0;i<row[j];i++){				//相連之 VN
					
						//printf("CN:%d to VN:%d\n",j,CN_set[j][i]);
						for(int f=0;f<col[CN_set[j][i]];f++){
							
										
							if(VN_set[CN_set[j][i]][f]==j){
								//找到VN 中之index 
								
								//printf("update VN %d to CN %d\n" ,CN_set[j][i],j);
								
								//printf("VN_set idex: %d\n",f);
								VN[CN_set[j][i]][f] = VN_total[CN_set[j][i]] - CN[j][i];
											
							}
										
						}
					}
					
					for(int i=0;i<row[j];i++){				//相連之 VN 
						
							
							//printf("CN:%d to VN:%d\n",j,CN_set[j][i]);
							int VN_node,VN_idex;
							for(int np=0 ; np<row[j] ; np++){			//n'
								if(CN_set[j][i]==CN_set[j][np]){		//n == n'
								
									VN_node = CN_set[j][np];
									
									//printf("VN:%d to CN:%d\n",CN_set[j][np],j); //N(m) set
									for(int f=0;f<col[CN_set[j][np]];f++){
										//找到VN 中之index 
										//printf("VN_set idex: %d\n",f);
										
										if(VN_set[VN_node][f]==j){
											//找到VN 中之index 
											//printf("VN_set idex: %d\n",f);
											VN_idex = f;
						
											break;
										}
										
									}	
									
								}
								//else if(CN_set[j][i]!=CN_set[j][np])
								else{	//n != n'
									
									//printf("VN:%d to CN:%d\n",CN_set[j][np],j); //N(m) set
									for(int f=0;f<col[CN_set[j][np]];f++){
										//找到VN 中之index 
										if(VN_set[CN_set[j][np]][f]==j){
											
											//printf("VN_set idex: %d\n",f);
											tau[j][i] *=tanh(VN[CN_set[j][np]][f]/2);	
											
										}
										
									}	
								}
									
									
							}
							
							//計算完tau 
							//printf("%f\n",tau[j][i]);
							
							if(tau[j][i]==1)
								CN[j][i] = 19.07;
							else if(tau[j][i]==-1)
								CN[j][i] = -19.07;
							else
								CN[j][i] = 2*atanh(tau[j][i]);
							
							//printf("VN node %d VN_idex %d\n",VN_node,VN_idex);
							VN_total[VN_node] = VN[VN_node][VN_idex] + CN[j][i];
							
					}
				}
				
				
				/*
				for(int j=0;j<(n-k);j++){
					
						printf("%e ",CN[j][0]);	
					
					printf("\n");	
				}
				*/
				

				
				//total LLR
				//decode
					
				for(int i=0;i<n;i++){ 				//go through all VN	
					
					
					if(VN_total[i]>=0)
						u_hat[i] = 0;
					else
						u_hat[i] = 1;
				}
				
				
				
				
				//判斷symdrome
				int* s = (int *)malloc(sizeof(int) * (n-k));
				bool iszerovector = true;
				
				for(int j=0;j<(n-k);j++){
					s[j] =0;
					for(int i=0;i<row[j];i++){
						if(CN_set[j][i]>=0&&u_hat[CN_set[j][i]]==1)
							s[j] += 1;
					}
					
					s[j] %=2;
					
					if(s[j]!=0){
						iszerovector = false;
						break;
					}	
				}
				
				if(iszerovector){
					break;
				}
				
			}
			//printf("%d\n",iter);
			avgIter[q] +=iter;
			
			for(int i=0;i<n;i++){	
				if(u[i]!=u_hat[i])
					error++;
			}
			
			for(int i=0;i<n;i++){
				if(u[i]!=u_hat[i]){
					frameerror++;
					break;
				}
					
			}
			
			
		}
		
		
	
		BER[q] = ((double)error)/((double)n*numtime);
		FER[q] = ((double)frameerror)/((double)numtime);
		
		printf("BER: %E, FER: %E Average iteration: %f\n",BER[q],FER[q],avgIter[q]/numtime);
	
	
	} 
	
	// Record the end time
    time_t end = clock();

    double diff = end - start; // ms
    printf(" %f  sec", diff / CLOCKS_PER_SEC );
    
	
	
	//寫入檔案 CSV
	FILE *fp = fopen("LDPC_1944_Layered_BP.csv", "w");
    
    //避免開啟失敗 
    if (fp == NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }
    
    
    for(int i=0;i<4;i++){
    	//printf("%d %d\n",q++,H[i][0]);
		for(int j=0;j<SNR_L;j++){
			if(i==0)
				fprintf(fp, "%f,",SNR_dB[j]);
			else if(i==1)
				fprintf(fp, "%E,",BER[j]);
			else if(i==2)
				fprintf(fp, "%E,",FER[j]);
			else
				fprintf(fp, "%E,",avgIter[j]/numtime);
		}	
		
		fprintf(fp, "\n");
	}

	fclose(fp);
	
	
	return 0;
}







