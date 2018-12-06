#include <bits/stdc++.h>
// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)
 
// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

using namespace std;

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
 
    // isLeaf is true if the node represents
    // end of a word
    string str="";
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
 
        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;
    }
 	
    return pNode;
}
 
// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, string key)
{
    int level;
    int length = key.length();
    int index;
 
    struct TrieNode *pCrawl = root;
 
    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
 
        pCrawl = pCrawl->children[index];
    }
 
    // mark last node as leaf
    pCrawl->str+=key;
    pCrawl->isLeaf = true;
}
 
// Returns true if key presents in trie, else false
bool search(struct TrieNode *root, string key)
{
    int level;
    int length = key.length();
    int index;
    struct TrieNode *pCrawl = root;
 
    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
 
        if (!pCrawl->children[index])
            return false;
 
        pCrawl = pCrawl->children[index];
    }
    
    return (pCrawl != NULL && pCrawl->isLeaf);
}
 
// Driver
int main()
{
    // Input keys (use only 'a' through 'z' and lower case)
    /*string keys[8] = {"the", "a", "there", "answer", "any",
                     "by", "bye", "their"};
 
    string output[32] = {"Not present in trie", "Present in trie"};
 */
 
    struct TrieNode *root = getNode();
 	string keys;
    // Construct trie
    int i;
    for (i = 0; i < 8; i++){
    	cin>>keys;
        insert(root, keys);}
 
    // Search for different keys
    cout<<search(root, "the")<<"\n";
    cout<<search(root, "these")<<"\n";
    cout<<search(root, "their")<<"\n";
    cout<<search(root, "thaw")<<"\n";
 
    return 0;
}
