#include <stdio.h>
#include <stdlib.h>
#include "ctype.h"
#include <string.h>



struct Node {
    char strings[500];
    int endOfWord;
    int root;
    struct Node * child[26];
};


int getContainer(const char val[500],int spot){
    // 97 == a
    // h == 7 after calc
    char letter = val[spot];
    int ascii = letter - 97;
    return ascii;
}

char* asciiArrayStringConverter(char *convertArray[500]) {
    char* finalString[500];
    for (int i = 0; i < 500; ++i) {
       strcat(*finalString,convertArray[i]);
    }
    return *finalString;
}

char numToASCII(int num) {
    return (char)num;
}

int insertWord(char val[500], struct Node *trie, int begin) {
    struct Node *travPoint = trie;
    int userAsciiTracker[500];
    int asciiNodeTracker[500];
    int nodeStringLen = 0;
    int flagForMatch = 1; // 1 = suffix case
    // Insert the empty node when the trie is empty
    printf("%s\n", val);
        int ascii = getContainer(val, 0);
        if (begin || (travPoint->root == 1 && travPoint->child[ascii] == NULL)) {
            travPoint->child[ascii] = NULL;
            travPoint->child[ascii] = (struct Node *) calloc(26,
                                                             sizeof(struct Node)); // Might have to make this 1 since I am using child inside of node
            travPoint->root = 1;
            begin = 0;
            strcpy(travPoint->child[ascii]->strings, val);
            travPoint->endOfWord = 1;
            travPoint = travPoint->child[ascii];
            return 0;
        }
        //Move down from the sentinal
        if(travPoint->root == 1) {
            travPoint = travPoint->child[ascii];
        }

        for (int j = 0; j < strlen(val); j++) {
            userAsciiTracker[j] = getContainer(val, j);
        }

        for (int k = 0; k < strlen(travPoint->strings); ++k) {
            asciiNodeTracker[k] = getContainer(travPoint->strings, k);
        }

        int length;

        if (strlen(travPoint->strings) < strlen(val)) {
            length = (int) strlen(val);
        } else {
            length = (int) strlen(travPoint->strings);
        }

    if(strcmp(travPoint->strings,val) == 0) {
        printf("%s","It enters");
        return 0;
    }

        for (int j = 0; j < length; j++) {
                //Suffix case
                if (userAsciiTracker[j] != asciiNodeTracker[j] && asciiNodeTracker[j] == 0) {
                    char finalString[500];
                    memset(finalString,'\0',sizeof(char)*500); // Clear the junk
                    char paste;
                    char *ptr;
                    for (int k = j; k < length; ++k) {
                        //Save the suffix
                        paste = (char) (userAsciiTracker[j] + 97);//////////////////////////////////
                        strcat(finalString, &paste);
                    }
                    printf("%s",finalString);



                    // Should be the beginning letter of the suffix where we check if its there or not
                    if (travPoint->child[userAsciiTracker[j]] == NULL) {
                        //No node, put it in!
                        travPoint->child[userAsciiTracker[j]] = (struct Node *) calloc(26,
                                                                                       sizeof(struct Node));
                        travPoint->child[userAsciiTracker[j]]->endOfWord = 1;

                        strcpy(travPoint->child[userAsciiTracker[j]]->strings, finalString);

                        break;
                    }
                    // Need to add more stuff here
                    else if (travPoint->child[userAsciiTracker[j]] != NULL) {
                        travPoint = travPoint->child[userAsciiTracker[j]]; // Maybe  //TODO:Might need to do recursion instead, recurse everytime it is a suffix case, and only pass in the char suffix
                        return insertWord(finalString,travPoint,0);


                    }
                    //Need to fix if it is equal to
                    if(strcmp(travPoint->strings,finalString) == 0) {
                        printf("%s","It enters");
                        return 0;
                    }
                }

        }






















    return 0;
}






int search(char val[500], struct Node *trie){
    return 0;
}

int deleteTrie(struct Node *trie){
    return 0;
}

int printTrieWords(char val[500], struct Node *trie) {
    return 0;
}

int printNodeLength(char val[500],struct Node *trie) {
    return 0;
}

int printNumOfWords(char val[500],struct Node *trie) {
    return 0;
}






int main() {
    char val[500];
    char input;
    int begin = 1;
    struct Node* root = NULL;
    root = (struct Node*)calloc(26,sizeof(struct Node));
    //root[7].parent
    do {
        do {
            scanf("%c", &input);
        } while(isspace(input));

        switch (input) {
            case 'i': // insert a value
                // read value to insert
                scanf("%s", val);
                //printf("%s\n",val);
                // insert word into trie
/*                int i;
                int len;
                len = 0;
                for(i=0; val[i]; i++) {
                    if(val[i] != ' ') {
                        len++;
                    }
                }*/
                insertWord(val, root,begin);
                begin = 0;
                break;

            case 's':  // search for that value
                scanf("%s", val);
                printf("%s",val);
                search(val,root);
                break;

            case 'e':  // empty the trie
                deleteTrie(root);
                break;

            case 'p': // print the words in the trie
                scanf("%s", val);
                printTrieWords(val,root);
                break;

            case 'n': // print the strings in each node
                scanf("%s", val);
                printNodeLength(val,root);
                break;

            case 'w': // count how many words that are in the trie
                scanf("%s", val);
                printNumOfWords(val,root);
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
