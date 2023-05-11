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
	//(1944,972)LDPC
	//BPSK 1 or -1
	
	
	const int n=1944;
	const int k=972;
	const double R=(double)k/n; //coderate
		
	int dv = 11;	//col weight
	int dc = 8; //row weight
	
	//Construct H   (n-k)*n

	double** H = (double **)malloc(sizeof(double*) * (n-k));
	for(int i=0;i<(n-k);i++){
		H[i] = (double *)malloc(sizeof(double) * n);
	}
	
	//讀檔建立 H  972*1944
	for(int i=0;i<(n-k);i++){
		for(int j=0;j<n;j++){
			H[i][j] = 0;
		}
		
	}
	
	
	FILE *fp1 = fopen("H_1944_972_2.txt", "r");
	if (fp1 == NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }
	
	int r = 0;
	int c1,c2,c3,c4,c5,c6,c7,c8;

	while(fscanf(fp1,"%d %d %d %d %d %d %d %d",&c1,&c2,&c3,&c4,&c5,&c6,&c7,&c8)){
		//printf("%d %d %d %d %d %d %d %d\n",c1,c2,c3,c4,c5,c6,c7,c8);
		
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
		
		
		if(r==(n-k)-1)
			break;
		r++;
	}

	fclose(fp1);
	
	
	

	//***************************************************************************
	//channel information
	double* Fn = (double *)malloc(sizeof(double) * n);
	//tau
	double** tau= (double **)malloc(sizeof(double*) * (n-k));
	for(int i=0;i<(n-k);i++){
		tau[i] = (double *)malloc(sizeof(double) * n);
	}
	
	//CN update //CN[j][i]  CN j to CN i
	double** CN = (double **)malloc(sizeof(double*) * (n-k));
	for(int i=0;i<(n-k);i++){
		CN[i] = (double *)malloc(sizeof(double) * n);
	}
	
	//VN update //VN[i][j]  VN i to CN j
	double** VN = (double **)malloc(sizeof(double*) * (n-k));
	for(int i=0;i<(n-k);i++){
		VN[i] = (double *)malloc(sizeof(double) * n);
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
	SNR_dB[0] = 1.2;

	
	//sigal;
	
	//假設全為 0
	int *u = (int*)malloc(sizeof(int) * n);	//binary sequence
	int *x = (int*)malloc(sizeof(int) * n);
	
	for(int i=0;i<n;i++){
		u[i] = 0;
		x[i] = 1;		//Eb=1	Eav = R*1
	} 
	
	
	
	//**********************************************
	int numtime =1;
	int iteration = 50;
	
	double *BER = (double*)malloc(sizeof(double) * SNR_L);
	double *FER = (double*)malloc(sizeof(double) * SNR_L);

	for(int q=0;q<SNR_L;q++){
		
		int error=0;
		int frameerror=0;
		
		for(int num=0;num<numtime;num++){
			
			printf("%d  ",num);	
		
		
			//iteration	
			double* noise = (double *)malloc(sizeof(double) * n);
			double U ,V ;
			double sigma = sqrt((1/(2*R))*pow(10,-(SNR_dB[q]/10)));
			
			for(int i=0;i<n;i++){
				U = (double) rand() / (double)(RAND_MAX+1.0);	//uniform 0~1
				V = (double) rand() / (double)(RAND_MAX+1.0);
				noise[i]= sqrt(-2*log(U))*cos(2*pi*V);
				noise[i] = sigma* noise[i] ;
			
				
				y[i] = x[i] + noise[i];
				
			} 
			
			//initialization
			
			for(int i=0;i<n;i++){
				Fn[i] = 2*y[i]/(pow(sigma,2));	
				for(int j=0;j<(n-k);j++){	
					if(H[j][i]==1)
						VN[j][i] = 2*y[i]/(pow(sigma,2));
					else
						VN[j][i] =0;
					
				}	
				
			}
			
			
			//iterative decoding
			int iter=0;
			
			for(iter=0;iter<iteration;iter++){
				
				//CN update	
				
				for(int j=0;j<(n-k);j++){
					for(int i=0;i<n;i++){ 
						tau[j][i] = H[j][i];
						CN[j][i] = H[j][i];
					}
				}
				
				
				
				for(int j=0;j<(n-k);j++){
					for(int i=0;i<n;i++){   //計算CN j to VN i 
						if(H[j][i]==0)
							continue;
						//printf("CN %d to VN %d\n",j,i);
						for(int t=0;t<n;t++){
							if(H[j][t]==1&&t!=i){
								tau[j][i] *= tanh(VN[j][t]/2);
								//printf("%d ",t);
							}
								
						}
						//printf("\n");
						CN[j][i] = log((1.0+tau[j][i])/(1.0-tau[j][i]));
						
					}
				} 
				
				/*
				for(int j=0;j<(n-k);j++){
					//for(int i=0;i<n;i++){ 
						//printf("%f ",tau[j][0] );
						printf("%f ",CN[j][0] );
					//}
					printf("\n");
				}*/
				
				
				//VN update
				for(int i=0;i<n;i++){	
					for(int j=0;j<(n-k);j++){	//計算VN i to CN j  
						if(H[j][i]==0)
							continue;
						//printf("VN %d to CN %d\n",i,j);
						VN[j][i] = Fn[i];
						for(int t=0;t<(n-k);t++){
							if(H[t][i]==1&&t!=j){
								VN[j][i] += CN[t][i];
								//printf("%d ",t);
							}
						}
						//printf("\n");
					}
				}
				/*
				for(int j=0;j<(n-k);j++){
					for(int i=0;i<n;i++){ 
						
						printf("%f ",VN[j][i] );
					}
					printf("\n");
				}
				*/
				
				
				//total LLR
				//decode
					
				for(int i=0;i<n;i++){ 				//go through all VN	
					VN_total[i] =  Fn[i]; 				
					for(int j=0;j<(n-k);j++){	
						if(H[j][i]==1)
							VN_total[i] += CN[j][i];
					}
					
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
			/*
			for(int i=0;i<n;i++){ 
				printf("%f ",VN_total[i] );
			}
			printf("\n");
			for(int i=0;i<n;i++){ 		
				printf("%d ",u_hat[i] );
			}
			printf("\n");
			*/
			
			
			printf("%d\n",iter);
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
	
		printf("%d %d   %E %E\n",error,frameerror,BER[q],FER[q]);
	
	
	} 
	
	// Record the end time
    time_t end = clock();

    double diff = end - start; // ms
    printf(" %f  sec", diff / CLOCKS_PER_SEC );
    
	/*
	//寫入 CSV
	FILE *fp = fopen("LDPC_1944_SPA.csv", "w");
    
    //避免開啟失敗 
    if (fp == NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }
    
    
    for(int i=0;i<3;i++){
    	//printf("%d %d\n",q++,H[i][0]);
		for(int j=0;j<SNR_L;j++){
			if(i==0)
				fprintf(fp, "%f,",SNR_dB[j]);
			else if(i==1)
				fprintf(fp, "%f,",BER[j]);
			else
				fprintf(fp, "%f,",FER[j]);
		}	
		
		fprintf(fp, "\n");
	}

	fclose(fp);
	*/
	
	return 0;
}







