#ifndef RADIXFUNC_H
#define RADIXFUNC_H

struct Node {
    char strings[500];
    int endOfWord;
    int root;
    struct Node * child[26];
    struct Node * parent[1];
    int nodeSize;
    int wordCount;
};

// A helper method for getting a bucket location for any char.
int getContainer(const char val[500],int spot);


// A method for inserting a word into the trie, if the search flag is active, the insert method will search and not insert
int insertWord(char val[500], struct Node *trie, int begin, int search,char initVal[500]);


// A method for searching if the word is in the trie already, calls the insert method with the search flag
int search(char val[500], struct Node *trie);


// A method for deleting the whole trie
int deleteTrie(struct Node *trie);


// A method for printing all of the words in a trie
int printTrieWords(struct Node *trie,char container[500],char concatContainer[500],int *flagForNext,int *q,int *offset);


// A method for printing the node length of the trie
int printNodeLength(struct Node *trie, struct Node *root);


// A method for printing the number of words in the trie
int printNumOfWords(struct Node *trie,struct Node *root);



#endif
