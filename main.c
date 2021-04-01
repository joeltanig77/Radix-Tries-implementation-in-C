#include "radixFunc.h"
#include <stdio.h>
#include <stdlib.h>
#include "ctype.h"
#include <string.h>

/* The included makefile will build and run the program */

int main() {
    char val[500];
    char str[500];
    memset(str,'\0',500*sizeof(char));
    char container[500];
    memset(container,'\0',500*sizeof(char));
    char concatContainer[500];
    memset(concatContainer,'\0',500*sizeof(char));
    char input;
    int begin = 1;
    int flagForNext = 0;
    int offset = 0;
    int q = 0;
    int trieIsEmpty = 1;
    struct Node* root = NULL;
    root = (struct Node*)calloc(26,sizeof(struct Node));
    do {
        do {
            scanf("%c", &input);
        } while(isspace(input));

        switch (input) {
            case 'i': // insert a value
                // read value to insert
                scanf("%s", val);
                insertWord(val, root,begin,0,val);
                trieIsEmpty = 0;
                begin = 0;
                break;

            case 's':  // search for that value
                scanf("%s", val);
                search(val,root);
                break;

            case 'e':  // empty the trie
                deleteTrie(root);
                root = (struct Node*)calloc(26,sizeof(struct Node));
                begin = 1;
                trieIsEmpty = 1;
                break;

            case 'p': // print the words in the trie
                if (trieIsEmpty) break;
                printTrieWords(root,container,concatContainer,&flagForNext,&q,&offset);
                memset(container,'\0',500*sizeof(char));
                q = 0;
                break;

            case 'n': // print the strings in each node
                printNodeLength(root,root);
                printf("Trie contains %d nodes\n",root->nodeSize);
                root->nodeSize = 0;
                break;

            case 'w': // count how many words that are in the trie
                printNumOfWords(root, root);
                printf("Trie contains %d words\n",root->wordCount);
                root->wordCount = 0;
                break;
            case 'q': // empty the trie and leave
                deleteTrie(root);
                break;
            default:
                printf("That's not a legal command\n");
        }

    } while (input != 'q');

    return 0;
}