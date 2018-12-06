#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
using namespace std;

struct ARRAY
{
    int value;
    int arr_num;
    
};
struct ARRAY Arr[10001]={0};
int curSize=0;

int genRand(int lower, int high){
	static bool first = true;
   if ( first ) 
   {  
      srand(time(NULL)); //seeding for the first time only!
      first = false;
   }
	return (lower + (rand()%(high-lower+1)));
	//25 + ( std::rand() % ( 63 - 25 + 1 ) )
}

void swap(int *a, int *b){
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;

}
void print_array(int arr[],int start,int en){
	for(int i=start;i<=en;i++)
		cout<<arr[i]<<" ";
	cout<<"\n";	

}


// Quick sort procedure
int partition(int arr[], int lower, int high){
	// generate random pivot
	int pivot,i,pos,j;
	pos=genRand(lower,high);
	//cout<<"pos"<<pos<<endl;
	pivot=arr[pos];
	//cout<<"pivot"<<pivot<<endl;
	swap(arr[pos],arr[high]);
	//print_array(arr,lower,high);
	j=lower-1;
	for(i=lower;i<=high-1;i++){
		if(arr[i]<=pivot){
			j=j+1;
			//cout<<arr[i]<<" "<<arr[j]<<" "<<i<<" "<<j<<endl;
			swap(arr[i],arr[j]);
			//print_array(arr,lower,high);

		}
		

	}
	swap(arr[j+1],arr[high]);

	return j+1;

}


void quickSort(int arr[], int low, int high){
	int pi;
	if(low<high){
		pi = partition(arr, low, high);
		
		quickSort(arr,low,pi-1);
		quickSort(arr,pi+1,high);

	}

}

int findpivort(int arr[], int low, int high, int middle){
	// returns the middle element

	int pi;

	
		pi = partition(arr, low, high);
		if(pi==middle){
			quickSort(arr,low,middle);
			return arr[pi];
		}
		else if(pi>middle)
			findpivort(arr, low, pi-1,middle);
		else if(pi<middle)
			findpivort(arr, pi+1, high,middle);
		else
			cout<<"error";
		

	

}
//************ K-min using looping************************************

void kmin(int arr[],int k,int n){
	int min,pos;
	
	//int min=FLT_MAX;

	for(int i=0; i<n-1;i++){
		if(i<=k){
			min=arr[i];
			pos=i;
			for(int j=i+1;j<n;j++){
				if(arr[j]<min){
					min=arr[j];
					pos=j;
				}
			}
		swap(arr[pos],arr[i]);
		}
	else
		break;
}
}

//************************** max heap procedure ******************************

void print_heap(int length){
	cout<<"current size:"<<curSize<<endl; 
    for(int i=1;i<=length;i++)
		cout<<Arr[i].value<<" ";
	cout<<"\n";	

}

int maxChild(int pos){

    if((2*pos+1)>curSize)
        return (2*pos);
    else{
            if(Arr[2*pos].value>Arr[2*pos+1].value)
              return (2*pos);
            else
              return (2*pos+1);
      }

}


void percolate_up(int pos){
    // i can still find the element from "pos" 
    int parent,temp;
    temp=Arr[pos].value;
    parent=floor(pos/2);
    if(parent>0){
        if(Arr[pos].value>Arr[parent].value){
            Arr[pos].value=Arr[parent].value;
            Arr[parent].value=temp;

            percolate_up(parent);
        }
    }

}

void percolate_down(int pos){
    // only if it has child it will come to this method

    int temp,m;
    temp=Arr[pos].value;
    if((2*pos)<=curSize){

        m=maxChild(pos);
        if(temp<Arr[m].value){
            Arr[pos].value=Arr[m].value;
            Arr[m].value=temp;
            percolate_down(m);
        } 
    }
}



void insert_heap(int element){
    curSize+=1;
    Arr[curSize].value=element;
    Arr[curSize].arr_num=1;
    //cout<<"element"<<element<<"\n";
    //cout<<"Current size"<<curSize<<"\n";
    percolate_up(curSize);
        
    
}
int findMax(){
    return Arr[1].value;
}

int delete_max(){
    // pos: max array size is indexed from 0;
    int m;
    m=findMax();
    Arr[1].value=Arr[curSize].value;
    curSize-=1;
    //cout<<"Current size"<<curSize<<"\n";
    percolate_down(1);
	return m;

}

void build_heap(int arr_list[],int num){
    // add all the elements to the array
    // now run this build heap for loop
    for(int iter=0;iter < num;iter++){
        curSize+=1;
        Arr[curSize].value=arr_list[iter];
        Arr[curSize].arr_num=1;
        //print_heap(curSize);
    }

    int i;
    for(i=floor(curSize/2);i>0;i--) {
        percolate_down(i);
        //print_heap(curSize);

    }
    print_heap(curSize);
}

//************************************************************************

int main(){
	int choice,A[10005]={0},n,k,i,pi;
	
	cout<<"1.Repeatedly finding the minimum\n";
	cout<<"2.Using a heap\n";
	cout<<"3.quicksort (random pivot)\n";
	cin>>choice;
	cout<<"Enter the value of n and k\n";
    cin>>n>>k;
    cout<<"Enter the elements\n";
    for(i=0;i<n;i++)
    	cin>>A[i];

	if(choice==1){
		cout<<"Repeatedly finding the minimum\n";
		kmin(A,k,n);
		print_array(A,0,k-1);
	}
	else if(choice==2){
		cout<<"Using a heap\n";	
		int result[k]={0};
		for(i=0;i<n;i++){
	    	
	        if(curSize < k){
	            insert_heap(A[i]);
	            //print_heap(curSize);
	        }
	        else if(curSize==k){
	            if(A[i]<findMax()){
	               Arr[1].value=A[i];
	               percolate_down(1);
	               //print_heap(curSize);
	            }

	        }
	        else 
	            cout<<"ERROR";    
		}

	    for(i=0;i<k;i++){
	        result[k-1-i]=findMax();
	        
	        delete_max();
	    }
	    for(i=0;i<k;i++){
	        
	        cout<<result[i]<<" ";
	        
	    }

	}
	else if(choice==3){
		cout<<"quicksort\n";	
		
		pi=findpivort(A,0,n-1,k-1);
		quickSort(A,0,pi-1);
		print_array(A,0,k-1);
	}
	else 
		cout<<"ERROR\n";
	return 0;
}
