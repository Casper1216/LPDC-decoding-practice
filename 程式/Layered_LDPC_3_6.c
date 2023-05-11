#include"AWGN.h"
#ifndef AWGN_H		//避免重複include 
#define AWGN_H
#endif

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
	// (6,3)LDPC
	//3 information bits
	//BPSK 1 or -1
	//Eav = 1/sqrt(2)
	
	const int n=6;
	const int k=3;
	const double R=(double)k/n; //coderate
	
	//H   (n-k)*n
	
	int dv = 2;	//col weight
	int dc = 3; //row weight
	int H[3][6]= {	{1,0,0,1,0,1},
					{1,1,0,0,1,0},
					{0,1,1,0,0,1}};
					
	int col[6] = {2,2,1,1,1,2};
	int row[3] = {3,3,3};
	//Construct adjacency list				
	//VN 
	int** VN_set = (int **)malloc(sizeof(int*) * n);
	for(int i=0;i<n;i++){
		VN_set[i] = (int *)malloc(sizeof(int) * col[i]);
	}
	int count=0;
	for(int i=0;i<n;i++){ 
	 	count=0;
		for(int j=0;j<(n-k);j++){
			if(H[j][i]==1){
				VN_set[i][count]=j;	//1~dv
				count++;
			}	
		}
	}

	/*
	for(int i=0;i<n;i++){ 
		for(int j=0;j<col[i];j++){
			printf("%d ",VN_set[i][j]);	
		}
		printf("\n");
	}
	*/
	//CN
	int** CN_set = (int **)malloc(sizeof(int*) * (n-k));
	for(int i=0;i<n-k;i++){
		CN_set[i] = (int *)malloc(sizeof(int) * row[i]);
	}	
	
	for(int j=0;j<(n-k);j++){
		count=0;
		for(int i=0;i<n;i++){
			if(H[j][i]==1){
				CN_set[j][count]=i;		//1~dv
				count++;
			}	
		}
	}

	/*
	printf("\n");
	for(int j=0;j<(n-k);j++){
		
		for(int i=0;i<dc;i++){
			printf("%d ",CN_set[j][i]);	
		}
		printf("\n");	
		
	}
	*/
	

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
	
	SNR_dB[0] = 0;
	/*
	SNR_dB[1] = 0.4;
	SNR_dB[2] = 0.8;
	SNR_dB[3] = 1.2;
	SNR_dB[4] = 1.6;
	SNR_dB[5] = 2;
	*/
	double *SNR = (double *)malloc(sizeof(double) * SNR_L);

	
	//sigal;
	
	//假設全為 0
	int *u = (int*)malloc(sizeof(int) * n);	//binary sequence
	int *x = (int*)malloc(sizeof(int) * n);
	
	for(int i=0;i<n;i++){
		u[i] = 0;
		*(x+i) = 1;		//Eb=1	Eav = R*1
	} 
	
	
	
	//**********************************************
	int numtime =1;
	int iteration = 1;	
	
	double *BER = (double*)malloc(sizeof(double) * SNR_L);
	double *FER = (double*)malloc(sizeof(double) * SNR_L);

	for(int q=0;q<SNR_L;q++){
		
		int error=0;
		int frameerror=0;
		
		for(int num=0;num<numtime;num++){
			
			
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
						tau[j][i]=1;
						
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
							//CN[j][i] = log((1.0+tau[j][i])/(1.0-tau[j][i]));
							if(tau[j][i]==1)
								CN[j][i] = 19.07;
							else if(tau[j][i]==-1)
								CN[j][i] = -19.07;
							else
								CN[j][i] = 2*atanh(tau[j][i]);
							
							//printf("VN node %d VN_idex %d\n",VN_node,VN_idex);
							VN_total[VN_node] = VN[VN_node][VN_idex] + CN[j][i];
							//printf("\n");
					}
				}
				/*
				for(int j=0;j<(n-k);j++){
					for(int i=0;i<dc;i++){	
						printf("%e ",CN[j][i]);	
					}
					printf("\n");	
				}
				*/
				
				
				
				//total LLR
				//decode
					
				for(int i=0;i<n;i++){ 				//go through all VN	
				
					//printf("VN_toatl %f\n",VN_total[i]);
					
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
	
	printf("%d %d   %f %f\n",error,frameerror,BER[q],FER[q]);
	
	
	} 
	
	// Record the end time
    time_t end = clock();

    double diff = end - start; // ms
    printf(" %f  sec", diff / CLOCKS_PER_SEC );
	
	return 0;
}







