#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>
using namespace std;

float *circular_conv(float x[],float h[] ,int N){
	float *y=new float[N];
	float total=0.0;
	int m=0,n,k;
	for(m=0;m<N;m++){
		total=0.0;
  		for(k=0;k<N;k++){
   			if((m-k)>=0)
    			n=m-k;
   			else
    			n=m-k+N;
			total=total+x[k]*h[n];
 	 	}
  	y[m]=total;

 }
	return y;
}

float *overlap_save(short int x[],float h[] ,int l, int n, int L){

	int m = l+n-1;
	float arr[50000]={0};
	float X[100]={0};
	float H[100]={0};
	float *y;
	int count=0;
	float *out=new float[100];
	int j,i,k;
	for(i=n-1;i<(L+n-1);i++){
		arr[i]=x[i-n+1];	
		}
	
	for(i=0;i<n;i++){
		H[i]=h[i];
		}
	j=0;
	while(j<(L+n-1)){
	
		for(i=j;i<(j+m);i++){
			X[i-j]=arr[i];
			}
		y=circular_conv(X,H,m);
	
		for(i=n-1;i<m;i++){
			out[count]=y[i];
			count++;
			}
	
		j=j+l;	
	}	
	return out;
	}


int main(){

short int a[12]={1,2,3,3,4,5,7,7,8,9,0,1};
//float b[17]={-0.0120787,0.024248,0.025792,-0.050285,-0.046996,-0.015378,0.133978,0.267828,0.345784,0.267828,0.133977,-0.015377,-0.046996,-0.050285,0.025792,0.024248,-0.012079};
float b[3]={1,2,1};
float *y; 

y=overlap_save(a,b,4,5,10);
for(int k=0;k<(12+3-1);k++)
		cout<<y[k]<<" ";	
	cout<<endl;	

return 0;
}
