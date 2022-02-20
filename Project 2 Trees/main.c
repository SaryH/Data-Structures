#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

struct Node{
    char word[20];
    char meaning[100];
    struct Node *Left;
    struct Node *Right;
};

struct Node *makeEmpty(struct Node *T){
    if(T != NULL){
        makeEmpty(T->Right);
        makeEmpty(T->Left);
        free(T);
    }
    return NULL;
}

struct Node *Find(char X[20], struct Node *T){
    if(T==NULL)
        return NULL;
    else if(strcmp(X,T->word)<0){
        return Find(X,T->Left);
    }
    else if(strcmp(X,T->word)>0){
        return Find(X,T->Right);
    }
    else{
        return T;
    }
}

struct Node *Insert(char word[20], char meaning[100], struct Node *T){
    if(T==NULL){
        T=(struct Node*) malloc((sizeof (struct Node)));
        if(T==NULL) {
            printf("Memory is full!");
        }
        else{
            memset(T->word, 0, sizeof(T->word));
            memset(T->meaning, 0, sizeof(T->meaning));
            strcpy(T->word,word);
            strcpy(T->meaning,meaning);
            T->Right=T->Left=NULL;
        }
    }
    else if(strcmp(word,T->word)<0){
        T->Left=Insert(word,meaning,T->Left);
    }
    else if(strcmp(word,T->word)>0){
        T->Right= Insert(word,meaning,T->Right);
    }
    return T;
}

char *removeNumber(char *str, int x, int totalwords){//removes the number character in a string (used for reading file)
    if(x<totalwords-1) {
        int d = 10;
        int digits;
        int temp = x + 2;
        while (temp / d != 0) { //to find the number of digits in the number
            d *= 10;
        }
        digits = (int) log10(d); //the power of 10, which in fact is the number of digits

        int size = (int) strlen(str);
        str[size - digits] = '\0';
    }
    return str;
}

//function to get rid of the extra spaces/tabs after reading words and their meaning. code inspired from: https://www.delftstack.com/howto/c/trim-string-in-c/
char *trimString(char *str){
    char *ending;
    while(isspace((unsigned char)*str)) str++;
    if(*str == 0)
        return str;
    ending = str + strlen(str)-1;
    while(ending > str && isspace((unsigned char)*ending)) ending--;
    ending[1] = '\0';

    return str;
}

//finds the leftmost node
struct Node *findMin(struct Node *T){
    if(T==NULL)
        return NULL;
    else if(T->Left==NULL)
        return T;
    else
        return findMin(T->Left);
}

//function to delete a node
struct Node *Delete(char *word, struct Node *T){
    struct Node *temp;

    if(T==NULL)
        printf("Word not found!");
    else if(strcmp(word,T->word)<0)
        T->Left= Delete(word,T->Left);
    else if(strcmp(word,T->word)>0)
        T->Right= Delete(word,T->Right);
    else
        if(T->Left && T->Right){//if node to be deleted has 2 children
            temp= findMin(T->Right);
            strcpy(T->word,temp->word);
            strcpy(T->meaning,temp->meaning);
            T->Right= Delete(T->word,T->Right);
        }
        else{
            temp=T;
            if(T->Left==NULL)
                T=T->Right;
            else if (T->Right==NULL)
                T=T->Left;
            free(temp);
        }
    return T;
}

void printTree(struct Node *T){
    if(T==NULL)
        return;
    printTree(T->Left);
    printf("%s: %s", T->word, T->meaning);
    printf("\n");
    printTree(T->Right);
}

//prints the tree to a file
void printTreetoFile(struct Node *T, FILE *output){
    if(T==NULL)
        return;
    printTreetoFile(T->Left,output);
    fprintf(output,"%s: %s", T->word, T->meaning);
    fprintf(output,"\n");
    printTreetoFile(T->Right,output);
}

void printTreeStartsWith(char X, struct Node *T){
    if(T==NULL)
        return;
    char temp=T->word[0];
    printTreeStartsWith(X,T->Left);
    if(temp==X) {
        printf("%s: %s", T->word, T->meaning);
        printf("\n");
    }
    printTreeStartsWith(X,T->Right);
}

//used in deleting all words that start with a specific letter
struct Node *FindStartsWith(char X, struct Node *T){
    int temp1,temp2=0;
    if(T!=NULL){
        temp1=X;
        temp2=T->word[0];
    }
    if(T==NULL)
        return NULL;
    else if(temp1<temp2){
        return FindStartsWith(X,T->Left);
    }
    else if(temp1>temp2){
        return FindStartsWith(X,T->Right);
    }
    else{
        return T;
    }
}

//function that deletes all words starting with a specific letter from the tree
void deleteStartsWith(char X, struct Node *T){
    struct Node *temp= FindStartsWith(X,T);
    while(temp!=NULL){
        Delete(temp->word,T);
        temp= FindStartsWith(X,T);
    }
}

int main() {

    //counting number of words in dictionary
    FILE* inputlines;
    inputlines=fopen("dictionary.txt", "r");
    if(inputlines==NULL) {
        printf("Can't find text file!");
        exit(-1);
    }

    char character;
    int words=1;
    while(fscanf(inputlines,"%c",&character)!=EOF){
        if(character=='.')
            words+=1;
    }
    fclose(inputlines);//closing file to reopen it so that it resets the scanner

    FILE *input=fopen("dictionary.txt", "r");//opening file
    if(input==NULL){
        printf("Can't find text file!");
        exit(-1);
    }

    char X[100];
    char word[20];
    char meaning[100];
    memset(word, 0, sizeof(word));
    memset(meaning, 0, sizeof(meaning));
    struct Node *Dictionary=NULL;

    char s[100];
    memset(s, 0, sizeof(s));//resetting the string: solved the problem of printing strange symbols after reading
    int i=0;
    int nosymbols;
    char temp;
    temp=(char)fgetc(input);

    while (temp != '.') {//removing first number
        if (temp == '\n')
            temp = (char)fgetc(input);
        s[i] = temp;
        i++;
        temp = (char)fgetc(input);
    }
    temp = (char)fgetc(input);
    i = 0;
    memset(s, 0, sizeof(s));
    for (int j = 0; j < words; ++j) {//loops as many times as there are words
        while (temp != ':') {//taking word
            nosymbols=temp;
            if(nosymbols>=0) {//prevents scanning special characters that have a negative int value (cause trouble)
                s[i] = temp;
                i++;
                temp = (char) fgetc(input);
            }
            else{
                temp = (char) fgetc(input);
            }
        }
        temp = (char)fgetc(input);
        i = 0;
        memset(X, 0, sizeof(X));
        strcpy(X, s);
        memset(s, 0, sizeof(s));
        strcpy(word,trimString(X));
        while (temp != '.' && temp!=':' && !feof(input)) {//taking word's meaning
            nosymbols=temp;
            if(nosymbols>=0) {
                s[i] = temp;
                i++;
                temp = (char) fgetc(input);
            }
            else{
                temp = (char) fgetc(input);
            }
        }
        temp = (char)fgetc(input);
        i = 0;
        memset(X, 0, sizeof(X));
        strcpy(X, s);
        memset(s, 0, sizeof(s));
        strcpy(meaning, trimString(removeNumber(X,j,words)));
        Dictionary=Insert(word,meaning,Dictionary);//inserting the word and its meaning to the Dictionary BST
    }
    fclose(input);

    //menu
    int choice;
    struct Node *tempT;
    char tempS[20];
    char tempM[100];
    char tempC;
    FILE *output;
    printf("All words and their meanings were read and saved in the Dictionary!");
    do{
        printf("\n1. Search for a word and display its meaning.\n2. Update the meaning of an existing word.\n3. Insert a new word with its"
               " meaning.\n4. Print all words in the dictionary in an alphabetic order with their associated meanings.\n5. "
               "Print all words that start with a specific character in an alphabetic order.\n6. Delete a word from the dictionary."
               "\n7. Delete all words that start with a specific letter.\n8. Save all words back in file dictionary.txt.\n9. Exit\n");
        printf("Execute:");
        scanf("%d",&choice);
        switch (choice){
            case(1):
                memset(tempS, 0, sizeof(tempS));
                printf("Word to search for: ");
                scanf("%s",tempS);
                tempT= Find(tempS,Dictionary);
                if(tempT!=NULL) {
                    printf("%s means: %s", tempS, tempT->meaning);
                }
                else
                    printf("Word not found!");
                break;
            case(2):
                memset(tempS, 0, sizeof(tempS));
                memset(tempM, 0, sizeof(tempM));
                printf("Word to change meaning: ");
                scanf("%s",tempS);
                printf("New meaning for %s: ", tempS);
                scanf("%s", &tempM);
                tempT= Find(tempS,Dictionary);
                strcpy(tempT->meaning,tempM);
                printf("Done!");
                break;
            case(3):
                memset(tempS, 0, sizeof(tempS));
                memset(tempM, 0, sizeof(tempM));
                printf("Insert a new word: ");
                scanf("%s",tempS);
                printf("Insert word(%s)'s meaning: ", tempS);
                scanf("%s", &tempM);
                Dictionary=Insert(tempS,tempM,Dictionary);
                printf("Done!");
                break;
            case(4):
                printTree(Dictionary);
                break;
            case(5):
                printf("Print all words that start with: ");
                scanf(" %c", &tempC);
                printTreeStartsWith(tempC,Dictionary);
                break;
            case(6):
                memset(tempS, 0, sizeof(tempS));
                printf("Word to delete: ");
                scanf("%s",tempS);
                if(Find(tempS,Dictionary)!=NULL){
                    Delete(tempS,Dictionary);
                    printf("Done! Deleted %s from dictionary", tempS);
                }
                else
                    printf("%s is not even in the dictionary", tempS);
                break;
            case(7):
                printf("Delete all words that start with: ");
                scanf(" %c", &tempC);
                deleteStartsWith(tempC,Dictionary);
                printf("\nAll words starting with %c were removed from the dictionary", tempC);
                break;
            case(8):
                output= fopen("dictionary.txt","w");
                printTreetoFile(Dictionary,output);
                fclose(output);
                printf("Done!");
                break;
            case(9):
                printf("Thanks for stopping by...");
                break;
            default:
                printf("Wrong option, try again!");
                break;
        }
    }while(choice!=9);

    return 0;

}
