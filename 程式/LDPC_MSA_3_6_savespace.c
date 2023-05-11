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
					
	//Construct adjacency list				
	//VN 
	int** VN_set = (int **)malloc(sizeof(int*) * n);
	for(int i=0;i<n;i++){
		VN_set[i] = (int *)malloc(sizeof(int) * dv);
	}
	int count=0;
	for(int i=0;i<n;i++){ 
	 	count=0;
		for(int j=0;j<(n-k);j++){
			if(H[j][i]==1){
				VN_set[i][count]=j+1;	//1~dv
				count++;
			}	
		}
	}
	//將相連的node 變成-1 
	for(int i=0;i<n;i++){ 
		for(int j=0;j<dv;j++){
			VN_set[i][j]-=1;	
			
		}
	}
	/* 
	for(int i=0;i<n;i++){ 
	 	
		for(int j=0;j<dv;j++){
			printf("%d ",VN_set[i][j]);	
		}
		printf("\n");
	}
	*/
	//CN
	int** CN_set = (int **)malloc(sizeof(int*) * (n-k));
	for(int i=0;i<n-k;i++){
		CN_set[i] = (int *)malloc(sizeof(int) * dc);
	}	
	
	for(int j=0;j<(n-k);j++){
		count=0;
		for(int i=0;i<n;i++){
			if(H[j][i]==1){
				CN_set[j][count]=i+1;		//1~dv
				count++;
			}	
		}
	}
	for(int j=0;j<(n-k);j++){
		for(int i=0;i<dc;i++){
			CN_set[j][i]-=1;		//1~dv		
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
	const int SNR_L = 6;
	double *SNR_dB = (double *)malloc(sizeof(double) * SNR_L);
	
	SNR_dB[0] = 0;
	
	SNR_dB[1] = 0.4;
	SNR_dB[2] = 0.8;
	SNR_dB[3] = 1.2;
	SNR_dB[4] = 1.6;
	SNR_dB[5] = 2;
	
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
	int numtime =10000;
	int iteration = 50;	
	
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
				U = (double) rand() / (double)(RAND_MAX);	//uniform 0~1
				V = (double) rand() / (double)(RAND_MAX);
				*(noise+i) = sqrt(-2*log(U))*cos(2*pi*V);
				*(noise+i) = sigma* (*(noise+i)) ;
			
				
				*(y+i) = *(x+i) + (*(noise+i));
				
			} 
			
			//initialization
			
			for(int i=0;i<n;i++){
				Fn[i] = 2*y[i]/(pow(sigma,2));	
				for(int j=0;j<dv;j++){	
					if(VN_set[i][j]==-1)
						VN[i][j] =0;
					else
						VN[i][j] = 2*y[i]/(pow(sigma,2));	
					
				}	
				
			}
			
			//iterative decoding
			int iter=0;
			
			for(iter=0;iter<iteration;iter++){
				
				//CN update	
				for(int j=0;j<(n-k);j++){	
					for(int i=0;i<dc;i++){
						CN[j][i]=1;	
					}
				}
			
				
				for(int j=0;j<(n-k);j++){				//go through all CN	
					for(int i=0;i<dc;i++){				//相連之 VN 
						if(CN_set[j][i]==-1){
							continue;	
						}
							double min_beta = pow(10,6);
							//printf("CN:%d to VN:%d\n",j,CN_set[j][i]);
							for(int np=0 ; np<dc ; np++){			//n'
								if(CN_set[j][np]>=0&&CN_set[j][i]!=CN_set[j][np]){	//n != n'
									
									//printf("VN:%d to CN:%d\n",CN_set[j][np],j); //N(m) set
									for(int f=0;f<dv;f++){
										//找到VN 中之index 
										if(VN_set[CN_set[j][np]][f]==j){
											
											//printf("%d %d\n",CN_set[j][np],f);
											if(fabs(VN[CN_set[j][np]][f])<min_beta)
												min_beta = fabs(VN[CN_set[j][np]][f]);
											if(VN[CN_set[j][np]][f]<0)
												CN[j][i]*=-1;
											
										}
										
									}
											
								}		
							}
						
						//計算完tau 
						CN[j][i] *= min_beta;
						
						
					}
				}
				/*
				for(int j=0;j<(n-k);j++){
					for(int i=0;i<dc;i++){	
						
						CN[j][i] = log((1.0+tau[j][i])/(1.0-tau[j][i]));	
						printf("%f ",CN[j][i]);	
					}
					printf("\n");
				}
				*/
				
				//VN update
	
				for(int i=0;i<n;i++){ 				//go through all VN	
					for(int j=0;j<dv;j++){			//相連之 CN 
						if(VN_set[i][j]==-1){
							continue;
						}
							VN[i][j] = Fn[i];
								
							//printf("VN:%d to CN:%d\n",i,VN_set[i][j]);
							for(int mp=0 ; mp<dv ; mp++){			//m'
								if(VN_set[i][mp]>=0&&VN_set[i][j]!=VN_set[i][mp]){	//m != m'
									
									//printf("from CN:%d to VN:%d\n",VN_set[i][mp],i);
									for(int p=0;p<dc;p++){
										//找到CN 中之index 
										
										if(CN_set[VN_set[i][mp]][p]==i){
											//printf("%d %d\n",VN_set[i][mp],p);
											VN[i][j] += CN[VN_set[i][mp]][p];		
										}
										
									}
											
								}		
							}
							
						
							
					}
					
				}
				/*
				for(int i=0;i<n;i++){ 				//go through all VN	
					for(int j=0;j<dv;j++){
						printf("%f ",VN[i][j]);
					}
					printf("\n");
				}*/
				
				
				//total LLR
				//decode
					
				for(int i=0;i<n;i++){ 				//go through all VN	
					VN_total[i] =  Fn[i]; 			
					for(int j=0;j<dv;j++){	
						if(VN_set[i][j]==-1)
							continue;				
						for(int m=0;m<dc;m++){
							if(CN_set[VN_set[i][j]][m]==i){		//找到與VN相連之 CN 
								//printf("VN %d CN %d to %d\n",i,VN_set[i][j],CN_set[VN_set[i][j]][m]);
								VN_total[i] += CN[VN_set[i][j]][m];
								
							}
						}
	
					}
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
					for(int i=0;i<n;i++){
						
						s[j] += u_hat[i]*H[j][i];
					
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







