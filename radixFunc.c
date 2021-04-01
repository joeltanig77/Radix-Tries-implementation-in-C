#include "radixFunc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* This is a function file that contains all of the functionality for the radix trie */

int getContainer(const char val[500],int spot){
    char letter = val[spot];
    int ascii = letter - 97;
    return ascii;
}


int insertWord(char val[500], struct Node *trie, int begin, int search,char initVal[500]) {
    struct Node *travPoint = trie;
    int userAsciiTracker[500];
    memset(userAsciiTracker,1,498*sizeof(char));
    int asciiNodeTracker[500];
    memset(asciiNodeTracker,1,498*sizeof(char));
    char suffixArray[500];
    memset(suffixArray,0,500*sizeof(char));
    char checkIfSame[500];
    memset(checkIfSame,'\0',500*sizeof(char));
    int flagForMatch = 0; // 1 = suffix case
    // Insert the empty node when the trie is empty
    int firstLetterBucket = getContainer(val, 0);
    // If there is not root, insert the root with the sentinel
    if (begin || (travPoint->root == 1 && travPoint->child[firstLetterBucket] == NULL && search == 0)) {
        travPoint->child[firstLetterBucket] = NULL;
        travPoint->child[firstLetterBucket] = (struct Node *) calloc(26,
                                                         sizeof(struct Node)); // Might have to make this 1 since I am using child inside of node
        travPoint->root = 1;
        // Link parent here
        travPoint->child[firstLetterBucket]->parent[0] = travPoint;
        begin = 0;
        strcpy(travPoint->child[firstLetterBucket]->strings, val);
        if (trie->root) {
            travPoint->endOfWord = 0;
        }
        travPoint->child[firstLetterBucket]->endOfWord = 1;
        return 0;
    }

    // Move down from the sentinel
    if(travPoint->root == 1) {
        travPoint = travPoint->child[firstLetterBucket];
    }

    // Turn the user string into a bucket slot
    for (int j = 0; j < strlen(val); j++) {
        userAsciiTracker[j] = getContainer(val, j);
    }

    if (travPoint == NULL && search == 1) {
        printf("%s is missing\n", initVal);
        return 0;
    }

    // Turn the node string into a bucket slot
    for (int k = 0; k < strlen(travPoint->strings); ++k) {
        asciiNodeTracker[k] = getContainer(travPoint->strings, k);
    }

    int length;
    int lengthOfValString = ((int) strlen(val));

    // Take the highest length of the node string or the user string and assign it to the length var
    if (strlen(travPoint->strings) < strlen(val)) {
        length = (int) strlen(val);
    } else {
        length = (int) strlen(travPoint->strings);
    }

    if(strcmp(travPoint->strings,val) == 0) {
        if (travPoint->endOfWord == 1) {
            printf("%s is present\n",initVal);
        }
        else if (search == 0){
            travPoint->endOfWord = 1;
        }
        else if (search == 1) {
            printf("%s is missing\n", initVal);
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
        if((userAsciiTracker[i] != asciiNodeTracker[i] && asciiNodeTracker[i] == 16843009) || suffixFlag == 1) {
            // Save the suffix
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
            struct Node *temp = (struct Node*)calloc(26,sizeof(struct Node));
            strcpy(temp->strings,checkIfSame);
            temp->endOfWord = 1;
            temp->parent[0] = travPoint->parent[0];
            temp->child[getContainer(proFixSave,0)] = travPoint;
            travPoint->parent[0]->child[getContainer(checkIfSame,0)] = temp;
            travPoint->parent[0] = temp;
            memset(travPoint->strings,'\0',500*sizeof(char));
            strcpy(travPoint->strings,proFixSave);
            return 0;
        }
            // Prefix Case for the non-backfilp case
            // Need to save the stuff that was left out from checkIfSave
        else if (userAsciiTracker[i] != asciiNodeTracker[i] && search == 0) {
            // Let us first split it and delete the already saved prefix from checkIfSame
            for (int k = 0; k < strlen(checkIfSame)+1; ++k) {
                // If the char is the same as the node string, delete it
                if (checkIfSame[k] == travPoint->strings[k]) {
                    // I did "?" instead of '\0' as strlen stops when a null is first seen
                    travPoint->strings[k] = '?';
                    // Save the remainder of what needs to be placed into the new node
                    remainderCount += 1;
                }
            }

            // Save the remaining user string not from checkIfSame
            for (int l = 0; l < lengthOfValString; ++l) {
                remainUserString[w] = (char)(userAsciiTracker[remainderCount]+97);
                remainderCount += 1;
                w += 1;
            }


            for (int k = 0; k < strlen(travPoint->strings); ++k) {
                // Get the profix and skip where the prefix used to be
                if (travPoint->strings[k] != '?'){
                    if (savedFirstLetter == 0) {
                        savedFirstLetter = 1;
                    }
                    // This should be in Node 2 which is the profix and checkIfSame is the prefix
                    proFixSave[v] = travPoint->strings[k];
                    v+=1;
                }
            }

            // Save the profix which is "flip"
            memset(travPoint->strings,'\0',500*sizeof(char));
            strcpy(travPoint->strings,proFixSave);
            if (travPoint->endOfWord == 1) {
                travPoint->endOfWord = 1;
            }
            else {
                travPoint->endOfWord = 0;
            }

            /*  If we added s to a word like flip are values would be....
            ProfixSave = flip, remainUserString = s, checkIfSame = back == insert this
            temp is the "back" and not the end of word  */

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

            // If we reach here we have a suffix case to deal with
            if (strcmp(checkIfSame,travPoint->strings) == 0 && travPoint->child[lastLetterContainer] != NULL) {
                flagForMatch = 1;
            }
        }
    }


    if (strlen(travPoint->strings) == strlen(val) && userAsciiTracker[strlen(val)] != asciiNodeTracker[strlen(travPoint->strings)]) {
        // Let us first split it and delete the already saved prefix from checkIfSame
        for (int k = 0; k < strlen(checkIfSame)+1; ++k) {
            // If the char is the same as the node string, delete it
            if (checkIfSame[k] == travPoint->strings[k]) {
                travPoint->strings[k] = '?'; //I did "?" instead of '\0' as strlen stops when a null is first seen
                remainderCount += 1; //Save the remainder of what needs to be placed into the new node
            }
        }


        // Save the remaining user string not from checkIfSame
        for (int l = 0; l < 1; ++l) {
            remainUserString[w] = (char)(userAsciiTracker[strlen(val)-1]+97);
            remainderCount += 1;
            w += 1;
        }


        for (int k = 0; k < strlen(travPoint->strings); ++k) {
            // Get the profix and skip where the prefix used to be
            if (travPoint->strings[k] != '?'){
                if (savedFirstLetter == 0) {
                    savedFirstLetter = 1;
                }
                // This should be Node 2 which is the profix and checkIfSame is the prefix
                proFixSave[v] = travPoint->strings[k];
                v+=1;
            }
        }
        // Save the profix which is "flip"
        memset(travPoint->strings,'\0',500*sizeof(char));
        strcpy(travPoint->strings,proFixSave);
        travPoint->endOfWord = 1;

        // Start the insert process here
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

    // If we are searching turn on the search flag and keep recursing down the tree for the suffix case
    if (flagForMatch && search == 1) {
        travPoint = travPoint->child[lastLetterContainer];
        return insertWord(suffixArray,travPoint,0,1,initVal);
    }

    // If we are not searching, recurse down the tree and turn off the search flag
    if (flagForMatch) {
        travPoint = travPoint->child[lastLetterContainer];
        return insertWord(suffixArray,travPoint,0,0,initVal);
    }

    // If the child at the last letter of the suffix is empty, put the node in
    if (lastLetterContainer != 16843009 && travPoint->child[lastLetterContainer] == NULL && search == 0) {
        travPoint->child[lastLetterContainer] = (struct Node *) calloc(26,
                                                                       sizeof(struct Node));
        travPoint->child[lastLetterContainer]->endOfWord = 1;
        strcpy(travPoint->child[lastLetterContainer]->strings,suffixArray);
        travPoint->child[lastLetterContainer]->parent[0] = travPoint;
    }
    // If we get to this point, we know that our string is not in the tree
    else if (search == 1) {
        printf("%s is missing\n", initVal);
        return 0;
    }
    return 0;
}



int search(char val[500], struct Node *trie){
    // Call the insert flag but pass in the search flag to not activate any insert function
    insertWord(val,trie,0,1,val);
    return 0;
}



int deleteTrie(struct Node *trie){
    if (trie == NULL) {
        return 0;
    }
    // Pre-order walk
    for (int i = 0; i < 26; ++i) {
        deleteTrie(trie->child[i]);
    }
    printf("%s %s\n","Deleting the node", trie->strings);
    free(trie);
    return 0;
}



int printTrieWords(struct Node *trie,char container[500],char concatContainer[500],int *flagForNext,int *q,int *offset) {
    if (trie == NULL) {
        return 0;
    }

    // Root case for if we are the end of word
    if (trie->endOfWord == 1 && trie->root == 0 && trie->parent[0]->root == 1) {
        *q = 0;
        memset(container,'\0',500*sizeof(char));
        for (int i = 0; i < 40; ++i) {
            if (container[i] == '\0') {
                container[i] = trie->strings[i];
            }
        }
        printf("%s\n",trie->strings);
    }
    // Root case for if we are not the end of word
    else if (trie->endOfWord == 0 && trie->root == 0 && trie->parent[0]->root == 1) {
        memset(container,'\0',500*sizeof(char));
        *q = 0;
        for (int i = 0; i < 40; ++i) {
            if (container[i] == '\0') {
                container[i] = trie->strings[i];
            }
        }
    }

    // Print the string we added to our container
    else if (trie->endOfWord == 1 && trie->root == 0 && *flagForNext == 0) {
        char showContainer[500];
        memset(showContainer,'\0',500*sizeof(char));
        strcpy(showContainer,container);
        int offset2 = 0;
        for (int i = 0; i < 40; ++i) {
            if (trie->strings[i] != '\0') {
                showContainer[*q] = trie->strings[i];
                *q+=1;
                offset2 += 1;
            }
        }
        *q = *q - offset2;
        *offset = (int) strlen(trie->strings);
        printf("%s\n",showContainer);
    }

    // Add the string into the master container so we can add to the container
    if (trie->root == 0) {
        for (int i = 0; i < 40; ++i) {
            if (trie->strings[i] != '\0') {
                container[*q] = trie->strings[i];
                *q+=1;
            }
        }
    }
    // Delete the suffix in order to put the next word in
    int i;
    for (i = 0; i < 26; ++i) {
        if (trie->root == 0 && *flagForNext == 1) {
            for (int j = 40; j > 0; --j) {
                if (container[j] != '\0' && *offset != 0) {
                    container[j] = '\0';
                    *offset -= 1;
                    *q -= 1;
                }
            }
        }
        *flagForNext = 0;
        printTrieWords(trie->child[i],container,concatContainer,flagForNext,q,offset);
    }
    *flagForNext = 1;
    // If we reach here, the node has no children left, so prime the node string container for deletion
    if (i == 26) {
        *offset = (int) strlen(trie->strings);
    }
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



int printNumOfWords(struct Node *trie,struct Node *root) {
    if (trie == NULL) {
        return 0;
    }
    for (int i = 0; i < 26; ++i) {
        printNumOfWords(trie->child[i],root);
    }
    if (trie->endOfWord == 1) {
        root->wordCount += 1;
    }
    return 0;
}

