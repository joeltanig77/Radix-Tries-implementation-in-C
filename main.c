#include <stdio.h>
#include <stdlib.h>
#include "ctype.h"
#include <string.h>


struct Node {
    char strings[500];
    int endOfWord;
    int root;
    struct Node * child[26];
    struct Node * parent[1];
    int nodeSize;
};


int getContainer(const char val[500],int spot){
    // 97 == a
    // h == 7 after calc
    char letter = val[spot];
    int ascii = letter - 97;
    return ascii;
}


int insertWord(char val[500], struct Node *trie, int begin, int search) {
    struct Node *travPoint = trie;
    int userAsciiTracker[500];
    memset(userAsciiTracker,0,500*sizeof(char));
    int asciiNodeTracker[500];
    memset(asciiNodeTracker,28,500*sizeof(char));
    char suffixArray[500];
    memset(suffixArray,0,500*sizeof(char));
    char checkIfSame[500];
    memset(checkIfSame,'\0',500*sizeof(char));
    int flagForMatch = 0; // 1 = suffix case
    // Insert the empty node when the trie is empty
    int ascii = getContainer(val, 0);
    if (begin || (travPoint->root == 1 && travPoint->child[ascii] == NULL && search == 0)) {
        travPoint->child[ascii] = NULL;
        travPoint->child[ascii] = (struct Node *) calloc(26,
                                                         sizeof(struct Node)); // Might have to make this 1 since I am using child inside of node
        travPoint->root = 1;
        // Link parent
        travPoint->child[ascii]->parent[0] = travPoint;
        begin = 0;
        strcpy(travPoint->child[ascii]->strings, val);
        if (trie->root) {
            travPoint->endOfWord = 0;
        }
        travPoint->child[ascii]->endOfWord = 1;

        return 0;
    }

    // Move down from the sentinel
    if(travPoint->root == 1) {
        travPoint = travPoint->child[ascii];
    }

    for (int j = 0; j < strlen(val); j++) {
        userAsciiTracker[j] = getContainer(val, j);
    }

    if (travPoint == NULL && search == 1) {
        printf("%s","Word was not found\n");
        return 0;
    }

    for (int k = 0; k < strlen(travPoint->strings); ++k) {
        asciiNodeTracker[k] = getContainer(travPoint->strings, k);
    }

    int length;
    int lengthOfValString = ((int) strlen(val));


    if (strlen(travPoint->strings) < strlen(val)) {
        length = (int) strlen(val);
    } else {
        length = (int) strlen(travPoint->strings);
    }

    if(strcmp(travPoint->strings,val) == 0) {
        if (travPoint->endOfWord == 1) {
            printf("%s","Word is already in the trie\n");
        }
        else {
            travPoint->endOfWord = 1;
        }
        return 0;
    }



    int suffixFlag = 0;
    int j = 0;
    int v = 0;
    int w = 0;
    int remainderCount = 0;
    int lastLetterContainer = 0;
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
        else if (userAsciiTracker[i] != asciiNodeTracker[i] && lengthOfValString == 0 && search == 0) {
            // Let us first split it and delete the already saved prefix from checkIfSame
            for (int k = 0; k < strlen(checkIfSame); ++k) {
                // If the char is the same as the node string, delete it
                if (checkIfSame[k] == travPoint->strings[k]) {
                    travPoint->strings[k] = '?'; //I did "?" instead of '\0' as strlen stops when a null is first seen
                }
            }
            // Get the Profix
            for (int k = 0; k < strlen(travPoint->strings); ++k) {
                // Get the profix and skip where the prefix used to be
                if (travPoint->strings[k] != '?'){
                    if (savedFirstLetter == 0) {
                        savedFirstLetter = 1;
                    }
                    proFixSave[v] = travPoint->strings[k]; // This should be Node 2 which is the profix and checkIfSame is the prefix
                    v+=1;
                }
            }
            // Save the prefix first
           // travPoint->parent[getContainer(travPoint->strings,0)]
            struct Node *temp = (struct Node*)calloc(26,sizeof(struct Node));
            strcpy(temp->strings,checkIfSame);
            temp->endOfWord = 1;
            temp->parent[0] = travPoint->parent[0];
            temp->child[getContainer(proFixSave,0)] = travPoint;

            travPoint->parent[0]->child[getContainer(checkIfSame,0)] = temp;
            travPoint->parent[0] = temp;


            memset(travPoint->strings,'\0',500*sizeof(char));
            strcpy(travPoint->strings,proFixSave);
            //travPoint->endOfWord = 1;
            return 0;

        }
        // Prefix Case for the non-backfilp case
        //Need to save the stuff that was left out from checkIfSave
        else if (userAsciiTracker[i] != asciiNodeTracker[i] && search == 0) {
            // Let us first split it and delete the already saved prefix from checkIfSame
            for (int k = 0; k < strlen(checkIfSame)+1; ++k) {
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
                    }
                    proFixSave[v] = travPoint->strings[k]; //This should be Node 2 which is the profix and checkIfSame is the prefix
                    v+=1;
                }
            }
            // Save the profix which is "flip"
            memset(travPoint->strings,'\0',500*sizeof(char));
            strcpy(travPoint->strings,proFixSave);
            travPoint->endOfWord = 1;

            //ProfixSave = flip
            //remainUserString = s
            //checkIfSame = back == insert this
            //temp is the "back" and not the end of word
            struct Node *temp = (struct Node*)calloc(26,sizeof(struct Node));
            struct Node *temp2 = (struct Node*)calloc(26,sizeof(struct Node));
            strcpy(temp->strings,checkIfSame);
            temp->endOfWord = 0;
            temp->parent[0] = travPoint->parent[0];
            temp->child[getContainer(proFixSave,0)] = travPoint;
            // Save the second node
            strcpy(temp2->strings,remainUserString);
            temp2->endOfWord = 1;
            temp->child[getContainer(remainUserString,0)] = temp2;
            temp2->parent[0] = temp;

            // Now need to save the nodes already in the trie!
            travPoint->parent[0]->child[getContainer(checkIfSame,0)] = temp;
            travPoint->parent[0] = temp;
            return 0;

        }

        else {
            // If the node and the val given are the same, save the char
            lastLetterContainer = userAsciiTracker[i+1];
            checkIfSame[i] = (char)(userAsciiTracker[i]+97);
            lengthOfValString -= 1;

            //Suffix Case
            if (strcmp(checkIfSame,travPoint->strings) == 0 && travPoint->child[lastLetterContainer] != NULL) {
                flagForMatch = 1;
            }
        }
    }

    //TODO: Clean this bloat fix up
    if (strlen(travPoint->strings) == strlen(val) && userAsciiTracker[strlen(val)] != asciiNodeTracker[strlen(travPoint->strings)]) {
        // Let us first split it and delete the already saved prefix from checkIfSame
        for (int k = 0; k < strlen(checkIfSame)+1; ++k) {
            //If the char is the same as the node string, delete it
            if (checkIfSame[k] == travPoint->strings[k]) {
                travPoint->strings[k] = '?'; //I did "?" instead of '\0' as strlen stops when a null is first seen
                remainderCount += 1; //Save the remainder of what needs to be placed into the new node
            }
        }

        //Save the remaining user string not from checkIfSame
        for (int l = 0; l < 1; ++l) {
            remainUserString[w] = (char)(userAsciiTracker[strlen(val)-1]+97);
            //travPoint->strings[remainderCount] = '?';
            remainderCount += 1;
            w += 1;
        }


        for (int k = 0; k < strlen(travPoint->strings); ++k) {
            //Get the profix and skip where the prefix used to be
            if (travPoint->strings[k] != '?'){
                if (savedFirstLetter == 0) {
                    savedFirstLetter = 1;
                }
                proFixSave[v] = travPoint->strings[k]; //This should be Node 2 which is the profix and checkIfSame is the prefix
                v+=1;
            }
        }
        // Save the profix which is "flip"
        memset(travPoint->strings,'\0',500*sizeof(char));
        strcpy(travPoint->strings,proFixSave);
        travPoint->endOfWord = 1;

        //ProfixSave = flip
        //remainUserString = s
        //checkIfSame = back == insert this
        //temp is the "back" and not the end of word
        struct Node *temp = (struct Node*)calloc(26,sizeof(struct Node));
        struct Node *temp2 = (struct Node*)calloc(26,sizeof(struct Node));
        int size = (int) strlen(checkIfSame);
        checkIfSame[size-1] = '\0';
        strcpy(temp->strings,checkIfSame);
        temp->endOfWord = 0;
        temp->parent[0] = travPoint->parent[0];
        temp->child[getContainer(proFixSave,0)] = travPoint;
        // Save the second node
        strcpy(temp2->strings,remainUserString);
        temp2->endOfWord = 1;
        temp->child[getContainer(remainUserString,0)] = temp2;
        temp2->parent[0] = temp;

        // Now need to save the nodes already in the trie!
        travPoint->parent[0]->child[getContainer(checkIfSame,0)] = temp;
        travPoint->parent[0] = temp;
        return 0;
    }


    if (flagForMatch && search == 1) {
        travPoint = travPoint->child[lastLetterContainer];
        return insertWord(suffixArray,travPoint,0,1);
    }

    if (flagForMatch) {
        travPoint = travPoint->child[lastLetterContainer];
        return insertWord(suffixArray,travPoint,0,0);
    }

    // If the child at the last letter of the suffix is empty, put the node in
    if (travPoint->child[lastLetterContainer] == NULL && search == 0) {
        travPoint->child[lastLetterContainer] = (struct Node *) calloc(26,
                                                                       sizeof(struct Node));
        travPoint->child[lastLetterContainer]->endOfWord = 1;
        strcpy(travPoint->child[lastLetterContainer]->strings,suffixArray);
        travPoint->child[lastLetterContainer]->parent[0] = travPoint;
    }

    else if (search == 1) {
        printf("%s","Word was not found\n");
        return 0;
    }

    return 0;
}





int search(char val[500], struct Node *trie){
    insertWord(val,trie,0,1);
    return 0;
}


int deleteTrie(struct Node *trie){
    if (trie == NULL) {
        return 0;
    }

    for (int i = 0; i < 26; ++i) {
        deleteTrie(trie->child[i]);
    }

    printf("%s %s\n","Deleting the node", trie->strings);
    free(trie);
    return 0;
}

int printTrieWords(char val[500], struct Node *trie) {
    return 0;
}




int printNodeLength(struct Node *trie, struct Node *root) {
    if (trie == NULL) {
        return 0;
    }

    for (int i = 0; i < 26; ++i) {
        printNodeLength(trie->child[i],root);
    }
    root->nodeSize += 1;

    return 0;
}








int printNumOfWords(char val[500],struct Node *trie) {
    return 0;
}






int main() {
    char val[500];
    char input;
    int begin = 1;
    int delStart = 0;
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
                insertWord(val, root,begin,0);
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
                //printf("%s",val);
                break;

            case 'p': // print the words in the trie
                scanf("%s", val);
                printTrieWords(val,root);
                break;

            case 'n': // print the strings in each node
                printNodeLength(root,root);
                printf("The node length is %d\n",root->nodeSize);
                root->nodeSize = 0;
                break;

            case 'w': // count how many words that are in the trie
                scanf("%s", val);
                printNumOfWords(val,root);
                break;
            case 'q': // empty the trie and leave
                deleteTrie(root);
                //DELETE THIS LATER
                //free(root);
                break;
            default:
                printf("That's not a legal command\n");
        }

    } while (input != 'q');

    return 0;
}