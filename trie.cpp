#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
using namespace std;

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)
 
// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#define INDEX_TO_CHAR(c) (char(c + (int)'a'))


struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
 
    // isLeaf is true if the node represents
    // end of a word
    int occurrences;
    int isLeaf;
    string str;
};


/*struct Trienode *new_node(){
	struct TrieNode *pNode = NULL;
	pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
	for(int i=0;i<26;i++)
	pNode->children[i] = NULL;
	pNode->occurrences=0;
	pNode->isLeaf=0;
	return pNode;
}*/
 
struct TrieNode *new_node(void)
{
    struct TrieNode *pNode = NULL;
 
    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
 
    if (pNode)
    {
        int i;
 
        pNode->isLeaf = false;
 
        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;
    }
 
    return pNode;
}
  
void insert(struct TrieNode *root, string key){
	int level;
    int len = key.length();
    int index;
    
    
    struct TrieNode *pCrawl = root;
    
    for(level=0;level<len;level++){
	    index=CHAR_TO_INDEX(key[level]);
	    
    	if(!pCrawl->children[index]){
    		
    		pCrawl->children[index]=new_node();
    	}
    	pCrawl=pCrawl->children[index];
    	pCrawl->occurrences+=1;
    
    
    }
    pCrawl->isLeaf=1;
    pCrawl->str=key;



}
void print_trie(struct TrieNode *root){

	struct TrieNode *pCrawl = root;
	struct TrieNode *temp;
	int index=0;
	while(index<26){
		if(pCrawl->children[index]==NULL){
			index++; continue;
		}			
		temp=pCrawl->children[index];
		print_trie(temp);
		index++;
		}
		
		if(pCrawl->isLeaf)
			cout<<pCrawl->str<<"\n";
	}
	




void search(struct TrieNode *root, string key){
	int level,index;
	int found=0;
	int len = key.length();
	struct TrieNode *pCrawl = root;
	
	for(level=0;level<len;level++){
		index=CHAR_TO_INDEX(key[level]);
		if(pCrawl->children[index]==NULL){
			cout<<"Not Found"<<"\n";
			break;
		}
		pCrawl=pCrawl->children[index];
	}
	if(level==len)
	cout<<"Found";
	
}
int main(){
struct TrieNode *root = new_node();
string str;



cin>>str;
insert(root, str);


return 0;


}
