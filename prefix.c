#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
 
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
 
// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)
 
// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
 
// trie node
int perfect=1;

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
 
    // isLeaf is true if the node represents
    // end of a word
    int occur;
    bool isLeaf;
};
 
// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = NULL;
 
    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
 
    if (pNode)
    {
        int i;
 
        pNode->isLeaf = false;
 		pNode->occur=0;
        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;
    }
 
    return pNode;
}
 
// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, const char *key,int num)
{
    int level;
    int length = strlen(key);
    int index;
 
    struct TrieNode *pCrawl = root;
 
    for (level = num; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
 
        pCrawl = pCrawl->children[index];
        pCrawl->occur+=1;
        if((pCrawl->occur>1)&&(pCrawl->isLeaf)){
        	perfect=0;
        	 printf("BAD SET\n");
 			 printf("%s",key);
        	}
        //printf("char:%c occurance:%d\n",key[level],pCrawl->occur);
    }
 
    // mark last node as leaf
    pCrawl->isLeaf = true;
}
 
// Returns true if key presents in trie, else false
/*int search(struct TrieNode *root, const char *key,int num)
{
    int level;
    int length = strlen(key);
    int index;
    int found=0;
    struct TrieNode *pCrawl = root;
 
    for (level = num; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
 
        if (!pCrawl->children[index])
            return found;
 
        pCrawl = pCrawl->children[index];
    }
 	if(level==length){
 	//printf("function :%d\n",pCrawl->occur);
 	return pCrawl->occur;
 	
 	}
 	
    //return (pCrawl != NULL && pCrawl->isLeaf);
}
 */
// Driver
int main()
{
    // Input keys (use only 'a' through 'z' and lower case)
    /*
    char keys[][8] = {"the", "a", "there", "answer", "any",
                     "by", "bye", "their"};*/
 
    //char output[][32] = {"Not present in trie", "Present in trie"};
 
 
    struct TrieNode *root = getNode();
 
    // Construct trie
    int i;
    int number;
    char keys[21],temp[10];
    
    scanf("%d",&number);
    //printf("%d",number);
    
    while((number--)&&(perfect)){
    	scanf("%s",keys);
    	//printf("%s\n",keys);
        insert(root, keys, 0);
        
 }
 if(perfect==1)
 printf("GOOD SET");

    // Search for different keys

    
    /*printf("%s --- %s\n", "the", output[search(root, "the")] );
    printf("%s --- %s\n", "these", output[search(root, "these")] );
    printf("%s --- %s\n", "their", output[search(root, "their")] );
    printf("%s --- %s\n", "thaw", output[search(root, "thaw")] );*/
 
    return 0;
}
