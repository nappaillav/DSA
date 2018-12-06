#include <bits/stdc++.h>

using namespace std;

struct node
{
    long long int key;
    struct node *left, *right;
};
  
// A utility function to create a new BST node
struct node *newNode(int item)
{
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}
struct node* insert(struct node* root, int data)
    {   struct node *p;	
     	p=root;
        if (p == NULL)    //If the tree is empty, return a new,single node
            return newNode(data);
        else
        {
            
            if (data <= p->key)
                p->left  = insert(p->left, data);
            else
                p->right = insert(p->right, data);
            
            return root;
        }
    }
void inorder(struct node*root,long long int k,int result)
    { 
        if(root)
        {	 if((root->key==k)&&(k!=1))
        		result=1;
        	 if(result==1){	
             	cout<<root->key<<"\n";}
             	inorder(root->left,k,result);    //Go to left subtree
             	inorder(root->right,k,result);     //Go to right subtree
        }
    }

int main(){
struct node *root;

int n;
long long int temp,num;
cin>>n;
for(int i=0;i<n;i++){
cin>>temp;
root=insert(root,temp);


}
cin>>num;
inorder(root,num,0);

return 0;
}

