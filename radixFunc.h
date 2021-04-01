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

int getContainer(const char val[500],int spot);



int insertWord(char val[500], struct Node *trie, int begin, int search,char initVal[500]);



int search(char val[500], struct Node *trie);



int deleteTrie(struct Node *trie);



int printTrieWords(struct Node *trie,char container[500],char concatContainer[500],int *flagForNext,int *q,int *offset);



int printNodeLength(struct Node *trie, struct Node *root);



int printNumOfWords(struct Node *trie,struct Node *root);





#endif //RADIXTREES_RADIXFUNC_H
