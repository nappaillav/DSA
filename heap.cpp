#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
using namespace std;
int arr[1000]={0};

/******************************
insert_heap(element,position)
	position is length of array  
delete_heap(length)
	length of the array
build_heap(length)
 	builds heap 
*******************************/


void print_heap(int length){
	for(int i=1;i<=length;i++)
		cout<<arr[i]<<" ";
	cout<<"\n";	

}


void insert_heap(int element,int pos){
    int temp,parent;
    parent=pos/2;
    temp=pos;
    //cout<<pos<<" pos \n";
    //print_heap(pos-1);
    while(parent>0){
        if(arr[parent]>element){
           
            arr[temp]=arr[parent];
            temp=parent;
            //cout<<parent<<" ";
            parent=temp/2;
            //print_heap(pos-1);
        }
        else{
            
            break;
           
        }
        
    }
    arr[temp]=element;
    //cout<<"elements:";
    //print_heap(pos);
}

int delete_heap(int length){
    // pos: max array size is indexed from 0;
    int temp,array_size,left,right,min,i;
    //cout<<"Deletion";
    temp=arr[length];
    array_size=length-1;
    min=arr[1];
    i=1;
    while(i<=(length/2)){
    	left=2*i;
    	right=2*i+1;
    	if((arr[left]<temp)&&(arr[right]<temp)){
    		arr[i]=arr[left]<arr[right]?arr[left]:arr[right];
    		i=arr[left]<arr[right]?left:right;
    
    	}
    	else if((arr[left]<temp)&&(arr[right]>temp)){
    		arr[i]=arr[left];
    		i=left;
    	}
    	else if((arr[left]>temp)&&(arr[right]<temp)){
    		arr[i]=arr[right];
    		i=left;
    	}
    	else
    		break;
    
    }
    arr[i]=temp;
    
	return min;

}






int main(){
    int length,i;
    length=0;
	for(i=5;i>0;i--){
	
	length+=1;
	insert_heap(i,length);
	print_heap(length);
	
	}
	i=1;
	for(i=1;i<=5;i++){
	
	
	cout<<"min: "<<delete_heap(length)<<"\n";
	length=length-1;
	print_heap(length);
	
	
	}



    return 0;
}

