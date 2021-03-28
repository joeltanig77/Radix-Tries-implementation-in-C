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
    int wordCount;
};


int getContainer(const char val[500],int spot){
    // 97 == a
    // h == 7 after calc
    char letter = val[spot];
    int ascii = letter - 97;
    return ascii;
}


int insertWord(char val[500], struct Node *trie, int begin, int search,char initVal[500]) {
    struct Node *travPoint = trie;
    int userAsciiTracker[500];
    memset(userAsciiTracker,28,500*sizeof(char));
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
        printf("%s is missing\n", initVal);
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
            printf("%s is present\n",initVal);
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
        return insertWord(suffixArray,travPoint,0,1,initVal);
    }

    if (flagForMatch) {
        travPoint = travPoint->child[lastLetterContainer];
        return insertWord(suffixArray,travPoint,0,0,initVal);
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
        printf("%s is missing\n", initVal);
        return 0;
    }

    return 0;
}





int search(char val[500], struct Node *trie){
    insertWord(val,trie,0,1,val);
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


int printTrieWords(struct Node *trie,char container[500],int flagForAdd,int *q,char concatContainer[500],int *w) {
    if (trie == NULL) {
        return 0;
    }
    if (trie->parent[0] != NULL && trie->endOfWord == 0 && trie->parent[0]->endOfWord == 1){
        printf("%s",trie->parent[0]->strings);
    }
    //This is for the bart case
    else if (trie->endOfWord == 1 && flagForAdd == 1 && trie->root == 0 && trie->parent[0]->endOfWord == 1) {
        char showContainer[500];
        memset(showContainer,'\0',500*sizeof(char));
        memset(concatContainer,'\0',500*sizeof(char));
        strcpy(showContainer,container);
        *w = 0;
        for (int i = 0; i < 40; ++i) {
            if (trie->strings[i] != '\0') {
                concatContainer[*w] = trie->parent[0]->strings[i];
                *w+=1;
            }
        }
        for (int i = 0; i < 40; ++i) {
            if (trie->strings[i] != '\0') {
                concatContainer[*w] = trie->strings[i];
                *w+=1;
            }
        }
        int t = 0;
        for (int i = 0; i < 40; ++i) {
            if (showContainer[i] == '\0') {
                showContainer[i] = concatContainer[t];
                t += 1;
            }
        }
        printf("%s\n", showContainer);
        //memset(concatContainer,'\0',500*sizeof(char));



    }
    // If we reach back to our parent and its a prefix, add the suffix
    //This is for bar
    else if (trie->endOfWord == 1 && flagForAdd == 1 && trie->root == 0 && trie->parent[0]->endOfWord == 0) {
        char showContainer[500];
        memset(showContainer,'\0',500*sizeof(char));
        strcpy(showContainer,container);
        int offset = 0;
        for (int i = 0; i < 40; ++i) {
            if (trie->strings[i] != '\0') {
                showContainer[*q] = trie->strings[i];
                *q+=1;
                offset += 1;
            }
        }
        *q = *q - offset;
        printf("%s\n", showContainer);
        //flagForAdd = 0;
    }

    // If we reach the add it to the container
    else if (trie->endOfWord == 0 && trie->root == 0) {
        memset(container,'\0',500*sizeof(char));
        memset(concatContainer,'\0',500*sizeof(char));
        *w = 0;
        flagForAdd = 1;
        for (int i = 0; i < 40; ++i) {
            if (trie->strings[i] != '\0') {
                container[*q] = trie->strings[i];
                *q+=1;
            }
        }
        //printf("%s\n", container);
    }
    else if (trie->endOfWord == 1 && flagForAdd == 0 && trie->root == 0) {
        printf("%s\n", trie->strings);
        *q = 0;
        //memset(root->strings,'\0',500*sizeof(char));
    }
    for (int i = 0; i < 26; ++i) {
        printTrieWords(trie->child[i],container,flagForAdd,q,concatContainer,w);
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
    int q = 0;
    int w = 0;
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
                printTrieWords(root,container,0,&q,concatContainer,&w);
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
                //DELETE THIS LATER
                //free(root);
                break;
            default:
                printf("That's not a legal command\n");
        }

    } while (input != 'q');

    return 0;
}