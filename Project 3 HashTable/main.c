#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

struct hashelement{
    int index;
    int hash;
    char word[20];
    char meaning[100];
    int state;//0 for empty, 1 for occupied, 2 for deleted
    int collisions;
};

struct hashelement *hashtable;//creating hashtable (dynamic array)
int linearcollisions;
int quadraticcollisions;
int size;

void initializeHashtable(){
    for (int i = 0; i < size; i++) {
        hashtable[i].state=0;
        hashtable[i].collisions=0;//for quadratic
        hashtable[i].hash=0;
        hashtable[i].index=0;
        memset(hashtable[i].word, 0, sizeof(hashtable[i].word));
        memset(hashtable[i].meaning, 0, sizeof(hashtable[i].meaning));
    }
    linearcollisions=0;
    quadraticcollisions=0;
}

int hash(char *string){
    int hash=0;
    int counter=0;
    char x=string[counter];
    while(x!='\0'){
        hash+=x;
        counter+=1;
        x=string[counter];
    }
    return hash;
}

double loadFactor(){
    int filled=0;
    for (int i = 0; i < size; i++) {
        if(hashtable[i].state==1)
            filled+=1;
    }
    double factor=(double)filled/size;
    return factor;
}

int filledSlots(){
    int filled=0;
    for(int i=0; i<size; i++){
        if(hashtable[i].state==1)
            filled+=1;
    }
    return filled;
}

int isPrime(int number){
    int i;
    for(i=2;i<=number/2;i++)
    {
        if(number%i!=0)
            continue;
        else
            return 0;//is prime
    }
    return 1;//is not
}

int nextPrime(int number){
    number+=1;
    while(number>0){
        if(isPrime(number)==1)
            return number;
        else
            number+=1;
    }
}

void delete(char *word, int mode){
    int h=hash(word)%size;
    int temp=h;
    if(mode==1){
        while (hashtable[temp].hash == h) {
            if (strcmp(word, hashtable[temp].word) == 0) {
                memset(hashtable[temp].word, 0, sizeof(hashtable[temp].word));
                memset(hashtable[temp].meaning, 0, sizeof(hashtable[temp].meaning));
                hashtable[temp].index = 0;
                hashtable[temp].hash = 0;
                hashtable[temp].state = 2;
                hashtable[temp].collisions = 0;
                break;
            }
            temp += 1;
        }
    }
    else if(mode==2){
        int counter=1;
        while (hashtable[temp].hash == h) {
            if (strcmp(word, hashtable[temp].word) == 0) {
                memset(hashtable[temp].word, 0, sizeof(hashtable[temp].word));
                memset(hashtable[temp].meaning, 0, sizeof(hashtable[temp].meaning));
                hashtable[temp].index = 0;
                hashtable[temp].hash = 0;
                hashtable[temp].state = 2;
                hashtable[temp].collisions = 0;
                break;
            }
            temp=(hash(word)+counter*counter)%size;
            counter++;
        }
    }
}

void insertLinear(char *word, char *meaning){
    int index=hash(word)%size;
    if(index==size)
        index=0;
    int h=index;
    if(hashtable[index].state!=1) {
        strcpy(hashtable[index].word,word);
        strcpy(hashtable[index].meaning,meaning);
        hashtable[index].state=1;
        hashtable[index].index=index;
        hashtable[index].hash=h;
    }
    else if(hashtable[index].state==1){
        index+=1;
        linearcollisions+=1;
        while(hashtable[index].state==1){
            index+=1;
        }
        strcpy(hashtable[index].word,word);
        strcpy(hashtable[index].meaning,meaning);
        hashtable[index].state=1;
        hashtable[index].index=index;
        hashtable[index].hash=h;
    }
}

void insertQuad(char *word, char *meaning) {
    int index = hash(word)%size;
    if(index==size)
        index=0;
    int h=index;
    if(hashtable[index].state!=1) {
        strcpy(hashtable[index].word,word);
        strcpy(hashtable[index].meaning,meaning);
        hashtable[index].state=1;
        hashtable[index].index=index;
        hashtable[index].hash=h;
    }
    else{
        quadraticcollisions+=1;
        while(hashtable[index].state==1){
            hashtable[index].collisions+=1;
            index=(hash(word)+hashtable[index].collisions*hashtable[index].collisions)%size;
        }
        strcpy(hashtable[index].word,word);
        strcpy(hashtable[index].meaning,meaning);
        hashtable[index].state=1;
        hashtable[index].index=index;
        hashtable[index].hash=h;
    }
}

char *findMeaning(char *word, int mode){
    int h=hash(word)%size;
    int temp=h;
    if(mode==1) {
        while (hashtable[temp].state == 1) {
            if (strcmp(word, hashtable[temp].word) == 0) {
                return hashtable[temp].meaning;
            }
            temp += 1;
        }
        return NULL;
    }
    else if(mode==2){
        int counter=1;
        while (hashtable[temp].state==1) {
            if (strcmp(word, hashtable[temp].word) == 0) {
                return hashtable[temp].meaning;
            }
            temp=(hash(word)+counter*counter)%size;
            counter++;
        }
        return NULL;
    }
}

int findIndex(char *word, int mode){
    int h=hash(word)%size;
    int temp=h;
    if(mode==1){
        while (hashtable[temp].state==1) {
            if (strcmp(word, hashtable[temp].word) == 0) {
                return temp;
            }
            temp += 1;
        }
        return -1;
    }
    else if(mode==2){
        int counter=1;
        while (hashtable[temp].state==1) {
            if (strcmp(word, hashtable[temp].word) == 0) {
                return temp;
            }
            temp=(hash(word)+counter*counter)%size;
            counter++;
        }
        return -1;
    }
}

void printHashtable(){
    printf("Hashtable:\n");
    for (int i = 0; i < size; ++i) {
        if(hashtable[i].state==1){
            printf("%d. %s:%s (hash value=%d)\n", i, hashtable[i].word, hashtable[i].meaning,hashtable[i].hash);
        }
    }
}

void printHashtableFile(int mode){
    FILE *output= fopen("dictionary_new.txt", "w");
    if(mode==1)
        fprintf(output,"Linear Probing");
    else if(mode==2)
        fprintf(output,"Quadratic Probing");
    fprintf(output," Hashtable:\n");
    for (int i = 0; i < size; ++i) {
        if(hashtable[i].state==1){
            fprintf(output,"%d. %s:%s (hash value=%d)\n", i, hashtable[i].word, hashtable[i].meaning,hashtable[i].hash);
        }
    }
    fclose(output);
}

void printEntireHashtable(){
    printf("Entire Hashtable:\n");
    for (int i = 0; i < size; ++i) {
        if(hashtable[i].state==1){
            printf("%d. %s:%s (hash value=%d)\n", i, hashtable[i].word, hashtable[i].meaning,hashtable[i].hash);
        }
        else if(hashtable[i].state==0)
            printf("%d. Empty Slot\n", i);
        else if(hashtable[i].state==2)
            printf("%d. Deleted\n", i);
    }
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

void readLinear(){
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

    hashtable= calloc(words*2,sizeof(struct hashelement));
    size= nextPrime(words);

    initializeHashtable();//initializing all states to 0

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
        insertLinear(word,meaning);
    }

    fclose(input);
}

void readQuad(){
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

    hashtable= calloc(words*2,sizeof(struct hashelement));
    size= nextPrime(words);

    initializeHashtable();//initializing all states to 0

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
        insertQuad(word,meaning);
    }

    fclose(input);
}

void readLinearRehash(){
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
        insertLinear(word,meaning);
    }

    fclose(input);
}

void readQuadRehash(){
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
        insertQuad(word,meaning);
    }

    fclose(input);
}

void checkRehash(int mode){
    if(loadFactor()>0.65 && mode==1){
        printf("\nRehashing table because it is overloaded!");
        size= nextPrime(size*2);
        hashtable=realloc(hashtable,size*sizeof(struct hashelement));
        initializeHashtable();
        readLinearRehash();
    }
    else if(loadFactor()>0.65 && mode==2){
        printf("\nRehashing table because it is overloaded!");
        size= nextPrime(size*2);
        hashtable=realloc(hashtable,size*sizeof(struct hashelement));
        initializeHashtable();
        readQuadRehash();
    }
}

int main() {

    int choice,mode,index,collision;
    char tempW[20];
    char tempM[100];

    printf("Select a hashing method:\n1. Linear probing\n2. Quadratic probing\n");
    scanf("%d", &mode);
    if(mode==1) {
        readLinear();
        while(loadFactor()>0.65)
            checkRehash(1);
    }
    else if(mode==2) {
        readQuad();
        while(loadFactor()>0.65)
            checkRehash(2);
    }
    else {
        printf("Error! Did not select a correct option. Linear hashing (default) will be used.\n");
        readLinear();
    }

    do{
        printf("\n1. Search for a word and display its meaning.\n"
               "2. Update the meaning of an existing word.\n"
               "3. Insert a new word from the user with its meaning.\n"
               "4. Print all words in the dictionary with their associated meanings.\n"
               "5. Print the entire hash table including the empty slots.\n"
               "6. Delete a word from the dictionary.\n"
               "7. Print the number of occupied slots, hash table size and the load factor.\n"
               "8. Save all words back in file dictionary_modified.txt.\n"
               "9. Change hashing method.\n"
               "10. Exit.\n");
        printf("Execute:");
        scanf("%d", &choice);
        switch(choice){
            case(1):
                memset(tempW, 0, sizeof(tempW));
                printf("Word to search for:");
                scanf("%s",tempW);
                if(findMeaning(tempW,mode)!=NULL)
                    printf("%s means %s\n", tempW, findMeaning(tempW,mode));
                else
                    printf("Word does not exist!");
                break;
            case(2):
                memset(tempW, 0, sizeof(tempW));
                memset(tempM, 0, sizeof(tempM));
                printf("Word to change meaning:");
                scanf("%s",tempW);
                printf("New meaning for %s:", tempW);
                scanf("%s", &tempM);
                index=findIndex(tempW,mode);
                if(index!=-1)
                    strcpy(hashtable[index].meaning,tempM);
                else
                    printf("Word does not exist!");
                break;
            case(3):
                memset(tempW, 0, sizeof(tempW));
                memset(tempM, 0, sizeof(tempM));
                printf("Insert a new word: ");
                scanf("%s",tempW);
                printf("Insert word(%s)'s meaning: ", tempW);
                scanf("%s", &tempM);
                if(mode==1){
                    insertLinear(tempW,tempM);
                    while(loadFactor()>0.65)
                        checkRehash(1);
                }
                else if(mode==2){
                    insertQuad(tempW,tempM);
                    while(loadFactor()>0.65)
                        checkRehash(2);
                }
                break;
            case(4):
                printHashtable();
                break;
            case(5):
                printEntireHashtable();
                break;
            case(6):
                memset(tempW, 0, sizeof(tempW));
                printf("Word to delete:");
                scanf("%s",tempW);
                if(findMeaning(tempW,mode)!=NULL)
                    delete(tempW,mode);
                else
                    printf("Word already does not exist!");
                break;
            case(7):
                if(mode==1)
                    collision=linearcollisions;
                else if(mode==2)
                    collision=quadraticcollisions;
                printf("\nOccupied slots:%d, Table size:%d, Collisions:%d, Load Factor:%f", filledSlots(), size, collision, loadFactor());
                break;
            case(8):
                printHashtableFile(mode);
                break;
            case(9):
                if(mode==1) {
                    printf("\nSwitching from linear to quadratic...");
                    initializeHashtable();
                    readQuad();
                    mode=2;
                    while(loadFactor()>0.65)
                        checkRehash(mode);
                }
                else if(mode==2) {
                    printf("\nSwitching from quadratic to linear...");
                    initializeHashtable();
                    readLinear();
                    mode=1;
                    while(loadFactor()>0.65)
                        checkRehash(mode);
                }
                break;
            case(10):
                break;
            default:
                printf("Please choose a correct option!");
        }
    }while(choice!=10);

    return 0;
}