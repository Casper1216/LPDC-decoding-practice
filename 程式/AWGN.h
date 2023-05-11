#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>


#define pi acos(-1)

/*
double* noise(int n,double mean,double variance){ 
	srand(time(0));

	double ans[n];
	double u=0,v=0 ;

	for(int i=0;i<n;i++){
		u = rand()/double(RAND_MAX);	//uniform 0~1
		v = rand()/double(RAND_MAX);
		
		ans[i] = sqrt(-2*log(u))*cos(2*pi*v)*sqrt(variance)+mean;
		//cout<<ans[i];
	}
	return ans;	
	
}
*/



double* normalvector(int n){ 	//n*1 normal vector
	srand(time(0));

	double *ans = (double *)malloc(sizeof(double) * n);
	double u ,v ;

	for(int i=0;i<n;i++){
		
		u = (double) rand() / (double)(RAND_MAX);	//uniform 0~1
		v = (double) rand() / (double)(RAND_MAX);
		
		*(ans+i) = sqrt(-2*log(u))*cos(2*pi*v);
		//printf("%f\n",*(ans+i));
		//printf("%f\n",ans[i]);
	}
	return ans;	
	
}



	
	
	

