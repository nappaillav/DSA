#include <bits/stdc++.h>

using namespace std;          // std::stack

typedef struct operation{
int op_num;
int pos;    //either position or length is stored
string s;

}op;


int main ()
{ string str,s;
  stack<op> mystack;
  
  op p;	
  long int t,position,n;
  int oper;
  cin>>t;
	  while(t--){
		  cin>>oper;
		  op temp;
		  if(oper==1){
		  		
		  		cin>>str;
		 		temp.op_num=1;
		 		temp.pos=s.length()-1; //you have the information of length from the string.
		 		temp.s=str;
		 		s+=str; 
		 		mystack.push(temp);
		 		//cout<<s<<"\n";
		  }
		  else if(oper==2){
		  		
		  		cin>>position;
		  		temp.op_num=2;
		  		temp.pos=position;
		  		n=s.length();
		  		temp.s=s.substr(n-position,position);
		  		s.erase(n-position,position);
		  		mystack.push(temp);
		  		//cout<<s<<"\n";
		  }
		  
		  else if(oper==3){
		  		cin>>position;
		  		cout<<s[position-1]<<"\n";
		  }
		  else if(oper==4){
		  		p=mystack.top();
		  		if(p.op_num==1){
			  		//cout<<"1.Deletion "<<p.s<<"\n";
			  		n=p.s.length();
			  		s.erase(s.length()-n,n);
			  		//cout<<s<<"\n";
		  		}
		  		if(p.op_num==2){
			  		//cout<<"2.Insertion "<<p.s<<"\n";
			  		s+=p.s;
			  		//cout<<s<<"\n";
		  		}
		  	mystack.pop();	
		  }
		  else
		  cout<<"ERROR";
	  
	  }
  


  return 0;
}

	
