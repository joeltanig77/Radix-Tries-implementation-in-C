#include <stdio.h>
#include <stdlib.h>
#include "ctype.h"
#include <string.h>

//TODO: Implement parent reference
struct Node {
    char strings[500];
    int endOfWord;
    int root;
    struct Node * child[26];
    struct Node * parent[26];
};


int getContainer(const char val[500],int spot){
    // 97 == a
    // h == 7 after calc
    char letter = val[spot];
    int ascii = letter - 97;
    return ascii;
}


int insertWord(char val[500], struct Node *trie, int begin) {
    struct Node *travPoint = trie;
    int userAsciiTracker[500];
    memset(userAsciiTracker,0,500*sizeof(char));
    int asciiNodeTracker[500];
    memset(asciiNodeTracker,28,500*sizeof(char));
    char suffixArray[500];
    memset(suffixArray,0,500*sizeof(char));
    char checkIfSame[500];
    memset(checkIfSame,'\0',500*sizeof(char));
    int nodeStringLen = 0;
    int flagForMatch = 0; // 1 = suffix case
    // Insert the empty node when the trie is empty
   // printf("%s\n", val);
    int ascii = getContainer(val, 0);
    if (begin || (travPoint->root == 1 && travPoint->child[ascii] == NULL)) {
        travPoint->child[ascii] = NULL;
        travPoint->child[ascii] = (struct Node *) calloc(26,
                                                         sizeof(struct Node)); // Might have to make this 1 since I am using child inside of node
        travPoint->root = 1;
        // Link parent
        travPoint->child[ascii]->parent[ascii] = travPoint;
        begin = 0;
        strcpy(travPoint->child[ascii]->strings, val);
        travPoint->endOfWord = 1;
        travPoint = travPoint->child[ascii];
        return 0;
    }

    //Move down from the sentinel
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
    int lengthOfValString = ((int) strlen(val));
    int lengthOfNodeString = (int) strlen(travPoint->strings);

    if (strlen(travPoint->strings) < strlen(val)) {
        length = (int) strlen(val);
    } else {
        length = (int) strlen(travPoint->strings);
    }

    if(strcmp(travPoint->strings,val) == 0) {
        printf("%s","It enters");
        travPoint->endOfWord = 1;
        return 0;
    }





    int suffixFlag = 0;
    int j = 0;
    int v = 0;
    int w = 0;
    int remainderCount = 0;
    int lastLetterContainer = 0;
    int firstLetterContainer = 0;
    int savedFirstLetter = 0;
    char proFixSave[500];
    memset(proFixSave,'\0',500*sizeof(char));
    char remainUserString[500];
    memset(remainUserString,'\0',500*sizeof(char));
    for (int i = 0; i < length; i++) {
        // Suffix Case
        if(userAsciiTracker[i] != asciiNodeTracker[i] && asciiNodeTracker[i] == 471604252 || suffixFlag == 1) {
            //Save the suffix
            //memset(suffixArray,'\0',500*sizeof(char));
            suffixArray[j] = (char) (userAsciiTracker[i]+97);
            j++;
            suffixFlag = 1;
        }
        // Prefix Case for the backflip case, if the letters don't equal and there is still a letter after the cursor and all the prefixes matches split

        else if (userAsciiTracker[i] != asciiNodeTracker[i] && asciiNodeTracker[i+1] != 471604252 && lengthOfValString == 0) {
            // Let us first split it and delete the already saved prefix from checkIfSame
            for (int k = 0; k < strlen(checkIfSame); ++k) {
                //If the char is the same as the node string, delete it
                if (checkIfSame[k] == travPoint->strings[k]) {
                    travPoint->strings[k] = '?'; //I did "?" instead of '\0' as strlen stops when a null is first seen
                }
            }
            // Get the Profix
            //printf("%lu",strlen(travPoint->strings));
            for (int k = 0; k < strlen(travPoint->strings); ++k) {
                //Get the profix and skip where the prefix used to be
                if (travPoint->strings[k] != '?'){
                    if (savedFirstLetter == 0) {
                        savedFirstLetter = 1;
                        firstLetterContainer = getContainer(travPoint->strings,k);
                    }
                    proFixSave[v] = travPoint->strings[k]; //This should be Node 2 which is the profix and checkIfSame is the prefix
                    v+=1;
                }
            }
            //TODO: Figure out what node needs to go where for the prefix backflip case
            //Save the prefix first
            //Cleared out travPoint->strings first then copy
            memset(travPoint->strings,'\0',500*sizeof(char));
            strcpy(travPoint->strings,checkIfSame);
            travPoint->endOfWord = 1;

            //Then Save the profix
            travPoint->child[firstLetterContainer] = NULL;
            travPoint->child[firstLetterContainer] = (struct Node *)calloc(26,
                                                             sizeof(struct Node));
            strcpy(travPoint->child[firstLetterContainer]->strings,proFixSave);  //TODO Might have to flip proFixSave and checkIfSave
            travPoint->child[firstLetterContainer]->endOfWord = 1;
            return 0;

        }
        //TODO: Figure out what node node needs to go for the prefix non-backflip case
        // Prefix Case for the non-backfilp case
        //Need to save the stuff that was left out from checkIfSave
        else if (userAsciiTracker[i] != asciiNodeTracker[i] && asciiNodeTracker[i+1] != 471604252) {
            // Let us first split it and delete the already saved prefix from checkIfSame
            for (int k = 0; k < strlen(checkIfSame); ++k) {
                //If the char is the same as the node string, delete it
                if (checkIfSame[k] == travPoint->strings[k]) {
                    travPoint->strings[k] = '?'; //I did "?" instead of '\0' as strlen stops when a null is first seen
                    remainderCount += 1; //Save the remainder of what needs to be placed into the new node
                }
            }

                //Save the remaining user string not from checkIfSame
                for (int l = 0; l < lengthOfValString; ++l) {
                    remainUserString[w] = (char)(userAsciiTracker[remainderCount]+97);
                    //travPoint->strings[remainderCount] = '?';
                    remainderCount += 1;
                    w += 1;
                }


            for (int k = 0; k < strlen(travPoint->strings); ++k) {
                //Get the profix and skip where the prefix used to be
                if (travPoint->strings[k] != '?'){
                    if (savedFirstLetter == 0) {
                        savedFirstLetter = 1;
                        firstLetterContainer = getContainer(travPoint->strings,k);
                    }
                    proFixSave[v] = travPoint->strings[k]; //This should be Node 2 which is the profix and checkIfSame is the prefix
                    v+=1;
                }
            }

            //TODO: Need to somehow save these into nodes!!!! Also do not forget to getConatiner on the starting letters and find out about the parent



            return 0;

        }


        else {
            //If the node and the val given are the same, save the char
            lastLetterContainer = userAsciiTracker[i+1];
            checkIfSame[i] = (char)(userAsciiTracker[i]+97);
            lengthOfValString -= 1;

            //Suffix Case
            if (strcmp(checkIfSame,travPoint->strings ) == 0 && travPoint->child[lastLetterContainer] != NULL) {
                flagForMatch = 1;
            }
        }
    }

    if (flagForMatch) {
        travPoint = travPoint->child[lastLetterContainer];
        return insertWord(suffixArray,travPoint,0);
    }


    //if the child at the last letter of the suffix is empty, put the node in
    if (travPoint->child[lastLetterContainer] == NULL) {
        travPoint->child[lastLetterContainer] = (struct Node *) calloc(26,
                                                                       sizeof(struct Node));
        travPoint->child[lastLetterContainer]->endOfWord = 1;
        strcpy(travPoint->child[lastLetterContainer]->strings,suffixArray);
        travPoint->child[lastLetterContainer]->parent[lastLetterContainer] = travPoint;
        //memset(suffixArray,'\0',500*sizeof(char));
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
