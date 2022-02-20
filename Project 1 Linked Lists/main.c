#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//student node structure and functions
struct snode{//structure of student nodes
    char sname[50];
    char sid[20];
    char courses[10][50];
    struct snode *next;
    int cregistered;//number of courses registered
    int cw;//courses wanted
};

struct snode *makeEmptys(struct snode *L){//creates header

    if(L!=NULL){
        printf("List already exists!");
    }
    else{
        L=(struct snode*)malloc(sizeof(struct snode));
    }
    if(L==NULL)
        printf("Memory is full!");

    L->next=NULL;

    return L;
}

int isEmptys(struct snode *L){
    return L->next==NULL;
}

int isLasts(struct snode *P, struct snode *L){
    return P->next==NULL;
}

void insertS(char sname[50], char sid[20], char courses[10][50], int cw, struct snode *P, struct snode *L){//inserting a node with course data
    struct snode *temp;
    temp=(struct snode*)malloc(sizeof(struct snode));
    strcpy(temp->sname,sname);
    strcpy(temp->sid,sid);
    for (int i = 0; i < 10; ++i) {
        strcpy(temp->courses[i],courses[i]);
    }
    temp->cregistered=0;//sets courses registered to 0 until the courses wanted to be registered are checked
    temp->cw=cw;

    temp->next=P->next;
    P->next=temp;
}

void prints(struct snode *L){//printing list
    struct snode *P=L;
    if(isEmptys(L))
        printf("List is empty!");
    else
        do{
            P=P->next;
            printf("Name: %s, ID: %s, Courses Wanted:\n", P->sname, P->sid);
            for (int i = 0; i < P->cw; ++i) {
                printf("%s\n",P->courses[i]);
            }
        }while(!isLasts(P,L));
}

struct snode *findLasts(struct snode *L) {//finds the last node in linked list
    struct snode *P;
    P=L;
    while (!isLasts(P,L)) {
        P=P->next;
    }
    return P;
}

void swaps(struct snode *L, struct snode *P){
    struct snode *T= makeEmptys(NULL);
    for (int i = 0; i < 10; ++i) {
        strcpy(T->courses[i],L->courses[i]);
    }
    strcpy(T->sname,L->sname);
    strcpy(T->sid,L->sid);
    T->cregistered=L->cregistered;
    T->cw=L->cw;

    for (int i = 0; i < 10; ++i) {
        strcpy(L->courses[i],P->courses[i]);
    }
    strcpy(L->sname,P->sname);
    strcpy(L->sid,P->sid);
    L->cregistered=P->cregistered;
    L->cw=P->cw;

    for (int i = 0; i < 10; ++i) {
        strcpy(P->courses[i],T->courses[i]);
    }
    strcpy(P->sname,T->sname);
    strcpy(P->sid,T->sid);
    P->cregistered=T->cregistered;
    P->cw=T->cw;

}

struct snode *finds(char sid[50], struct snode *L){
    struct snode *P;
    P=L->next;

    while(P!=NULL && strcmp(sid,P->sid)!=0){
        P=P->next;
    }

    return P;
}

void bubbles(struct snode *L){//bubble sort algorithm for students based on ID reference code is from: https://www.geeksforgeeks.org/c-program-bubble-sort-linked-list/
    int swap;
    struct snode *P1;
    struct snode *P2=NULL;

    if(L!=NULL){
        do {
            swap=0;
            P1=L;
            while(P1->next!=P2){
                if(atoi(P1->sid)>atoi(P1->next->sid)){
                    swaps(P1,P1->next);
                    swap=1;
                }
                P1=P1->next;
            }
            P2=P1;
        }while(swap);
    }
}

//course node structure and functions
struct cnode{//structure of course nodes
    char cname[50];
    char cid[20];
    int year;
    int maxstudents;
    struct cnode *next;
    struct snode *students[2];//array of student linked list,[0] for those registered in this course, [1] is the waiting list
    int sregistered;//number of students registered
    int swaiting;
};

struct cnode *makeEmpty(struct cnode *L){//creates header

    if(L!=NULL){
        printf("List already exists!");
    }
    else{
        L=(struct cnode*)malloc(sizeof(struct cnode));
    }
    if(L==NULL)
        printf("Memory is full!");

    L->next=NULL;

    return L;
}

int isEmpty(struct cnode *L){
    return L->next==NULL;
}

int isLast(struct cnode *P, struct cnode *L){
    return P->next==NULL;
}

void insertC(char cname[50], char cid[20], int year, int maxstudents, struct cnode *P, struct cnode *L){//inserting a node with course data
    struct cnode *temp;
    temp=(struct cnode*)malloc(sizeof(struct cnode));
    strcpy(temp->cid,cid);
    strcpy(temp->cname,cname);
    temp->maxstudents=maxstudents;
    temp->year=year;
    temp->sregistered=0;//sets students registered to 0 until the students are processed
    temp->swaiting=0;
    temp->students[0]=makeEmptys(NULL);
    temp->students[1]=makeEmptys(NULL);

    temp->next=P->next;
    P->next=temp;
}

void printC(struct cnode *L){//printing list
    struct cnode *P=L;
    if(isEmpty(L))
        printf("List is empty!");
    else
        do{
            P=P->next;
            printf("%s %s %d %d\n", P->cname, P->cid, P->year, P->maxstudents);
        }while(!isLast(P,L));
}

struct cnode *findLast(struct cnode *L) {//finds the last node in linked list
    struct cnode *P;
    P=L;
    while (!isLast(P,L)) {
        P=P->next;
    }
    return P;
}

struct cnode *findc(char cid[50], struct cnode *L){
    struct cnode *P;
    P=L->next;

    while(P!=NULL && strcmp(cid,P->cid)!=0){
        P=P->next;
    }

    return P;
}

void swapc(struct cnode *L, struct cnode *P){
    struct cnode *T= makeEmpty(NULL);

    strcpy(T->cname,L->cname);
    strcpy(T->cid,L->cid);
    T->year=L->year;
    T->maxstudents=L->maxstudents;
    T->sregistered=L->sregistered;
    T->swaiting=L->swaiting;
    T->students[0]=L->students[0];
    T->students[1]=L->students[1];

    strcpy(L->cname,P->cname);
    strcpy(L->cid,P->cid);
    L->year=P->year;
    L->maxstudents=P->maxstudents;
    L->sregistered=P->sregistered;
    L->swaiting=P->swaiting;
    L->students[0]=P->students[0];
    L->students[1]=P->students[1];

    strcpy(P->cname,T->cname);
    strcpy(P->cid,T->cid);
    P->year=T->year;
    P->maxstudents=T->maxstudents;
    P->sregistered=T->sregistered;
    P->swaiting=T->swaiting;
    P->students[0]=T->students[0];
    P->students[1]=T->students[1];

}

void bubblec(struct cnode *L){//bubble sort algorithm for courses based on course name, reference code is from: https://www.geeksforgeeks.org/c-program-bubble-sort-linked-list/
    int swap,cmp;
    struct cnode *P1;
    struct cnode *P2=NULL;

    if(L!=NULL){
        do {
            swap=0;
            P1=L;
            while(P1->next!=P2){
                cmp=strcmp(P1->next->cname,P1->cname);
                if(cmp>0){
                    swapc(P1,P1->next);
                    swap=1;
                }
                P1=P1->next;
            }
            P2=P1;
        }while(swap);
    }
}

int main(){

    //counting number of lines in file
    FILE* input;
    input=fopen("Courses.txt", "r");
    if(input==NULL) {
        printf("Can't find text file!");
        exit(-1);
    }

    const char EOL = '\n';//end of line reading
    char character;
    int lines=1;
    while(fscanf(input,"%c",&character)!=EOF){
        if(character==EOL)
            lines+=1;
    }
    fclose(input);//closing file to reopen it so that it resets the scanner

    FILE *inputc=fopen("Courses.txt", "r");//opening file
    if(inputc==NULL){
        printf("Can't find text file!");
        exit(-1);
    }
    char cname[50];
    char cid[20];
    int year;
    int maxstudents;

    char s[50];
    memset(s, 0, sizeof(s));//resetting the string: solved the problem of printing strange symbols after reading
    int i=0;
    char temp=fgetc(inputc);

    struct cnode *headc;
    headc=makeEmpty(NULL);//creating head of the courses linked list

    //reading from file
    for (int j=0; j<lines; j++) {
        while (temp != ',') {//1: course name
            if (temp == '\n')
                temp = fgetc(inputc);
            s[i] = temp;
            i++;
            temp = fgetc(inputc);
        }
        temp = fgetc(inputc);
        i = 0;
        strcpy(cname, s);
        memset(s, 0, sizeof(s));

        while (temp != ',') {//2: course id
            if (temp == '\n')
                temp = fgetc(inputc);
            s[i] = temp;
            i++;
            temp = fgetc(inputc);
        }
        temp = fgetc(inputc);
        i = 0;
        strcpy(cid, s);
        memset(s, 0, sizeof(s));

        while (temp != ',') {//3: course year
            if (temp == '\n')
                temp = fgetc(inputc);
            s[i] = temp;
            i++;
            temp = fgetc(inputc);
        }
        temp = fgetc(inputc);
        i = 0;
        year = atoi(s);
        memset(s, 0, sizeof(s));

        while (temp != '\n' && temp!=-1) {//4: max students
            s[i] = temp;
            i++;
            temp = fgetc(inputc);
        }
        if(temp=='\n')
            temp = fgetc(inputc);
        i = 0;
        maxstudents = atoi(s);
        memset(s, 0, sizeof(s));

        insertC(cname, cid, year, maxstudents, findLast(headc), headc);//inserting course node into linked list
    }

    fclose(inputc);

    //reading from student file
    //counting number of lines in file
    FILE* input2;
    input2=fopen("Students.txt", "r");
    if(input2==NULL) {
        printf("Can't find text file!");
        exit(-1);
    }

    char character2;
    int lines2=1;
    while(fscanf(input,"%c",&character2)!=EOF){
        if(character2==EOL)
            lines2+=1;
    }
    fclose(input2);//closing file to reopen it so that it resets the scanner

    FILE *inputs=fopen("Students.txt", "r");//opening file
    if(inputs==NULL){
        printf("Can't find text file!");
        exit(-1);
    }
    char sname[50];
    char sid[20];
    char courses[10][50];

    memset(courses, 0, sizeof(courses));//resetting the string array because random symbols are printed otherwise

    char x[50];
    memset(x, 0, sizeof(x));//resetting the string: solved the problem of printing strange symbols after reading
    i=0;
    int c=0;
    char temps=fgetc(inputs);

    struct snode *heads;
    heads=makeEmptys(NULL);//creating head of the students linked list

    //reading from file
    for (int j=0; j<lines2; j++) {
        c=0;
        while (temps != '#') {//1: student name
            if (temps == '\n')
                temps = fgetc(inputs);
            x[i] = temps;
            i++;
            temps = fgetc(inputs);
        }
        temps = fgetc(inputs);
        i = 0;
        strcpy(sname, x);
        memset(x, 0, sizeof(x));

    while (temps != '#') {//2: student id
        if (temps == '\n')
            temps = fgetc(inputs);
        x[i] = temps;
        i++;
        temps = fgetc(inputs);
    }
    temps = fgetc(inputs);
    i = 0;
    strcpy(sid, x);
    memset(x, 0, sizeof(x));

    do {//3: courses for student
        while (temps != '#' && temps!='\n' && temps!=-1) {
            x[i] = temps;
            i++;
            temps = fgetc(inputs);
        }
        if(temps!='\n')
            temps = fgetc(inputs);
        i = 0;
        strcpy(courses[c], x);
        memset(x, 0, sizeof(x));
        c++;
    }while(temps!=-1 && temps!='\n');

        insertS(sname,sid,courses, c, findLasts(heads),heads);
        memset(courses, 0, sizeof(courses));

    }

    fclose(inputs);

    //adding students to their courses
    int studentyear;
    struct snode *tempstudent=heads->next;
    struct cnode *tempcourse;
    while(tempstudent!=NULL){
        studentyear=atoi(tempstudent->sid)/10000;//student's year
        for(int j=0; j<tempstudent->cw; j++){//goes through all courses that the student wishes to register
            tempcourse=findc(tempstudent->courses[j], headc);
            if(tempstudent->cregistered<5){//if students registered courses are less than 5 proceed, else don't
                if(tempcourse!=NULL){//if course is offered this semester proceed, else don't
                    if(studentyear<=tempcourse->year){//checks if course year matches student year, if not doesn't proceed
                        if(tempcourse->sregistered<tempcourse->maxstudents){//checks if course is full, if yes, it adds student to the waiting list
                            insertS(tempstudent->sname,tempstudent->sid, tempstudent->courses, tempstudent->cw,
                                    findLasts(tempcourse->students[0]), tempcourse->students[0]);
                            tempcourse->sregistered++;
                            tempstudent->cregistered++;
                            printf("%s is added to %s(%s)!\n", tempstudent->sname, tempcourse->cname, tempcourse->cid);
                        }
                        else{
                            printf("%s course is full! %d students are enrolled. Student is added to waiting list\n",
                                   tempstudent->courses[j], tempcourse->maxstudents);
                            insertS(tempstudent->sname,tempstudent->sid,tempstudent->courses,tempstudent->cw,
                                    findLasts(tempcourse->students[1]),tempcourse->students[1]);
                            tempcourse->swaiting++;
                        }
                    }
                    else{
                        printf("%s's year (%d) does not match %s requirements (%d or earlier)!\n", tempstudent->sname,
                               studentyear, tempcourse->cid, tempcourse->year);
                    }
                }
                else{
                    printf("%s is not available this semester!\n", tempstudent->courses[j]);
                }
            }
            else{
                printf("%s already has 5 registered courses!\n", tempstudent->sname);
            }
        }
        tempstudent=tempstudent->next;
        printf("--------------------------\n");
    }

    //menu
    int option=0;
    int max;
    char coursename[50];
    char studentid[20];
    struct cnode *course=makeEmpty(NULL);
    struct snode *student=makeEmptys(NULL);
    struct snode *studentw=makeEmptys(NULL);
    FILE *output=fopen("output.txt","w");
    printf("Student and course information was read from the file and where applicable, students were registered! Read above.\n");
    do{
        printf("What would you like to do now?\n1. Print the students list that contains all students information (ordered based on students ID) in each\n"
               "course in a table format.\n2. Print a course list (ordered based on course name) that contains, the course name, course id, number\n"
               "of registered students in that course, and number of students in the waiting list for that course.\n3. Print a list of all courses that have less than 5 students."
               "\n4. Search for any course based on course ID, if found, print all students ids and names in this course.\n5. Search for any student based on student ID, in a given course.\n6. Exit.\n");
        scanf("%d", &option);
        switch(option) {
            case(1):
                course=headc->next;
                while(course!=NULL){
                    bubbles(course->students[0]);
                    bubbles(course->students[1]);
                    student=course->students[0]->next;
                    studentw=course->students[1]->next;
                    fprintf(output, "\t%s(%s):\n",course->cname,course->cid);
                    fprintf(output, "-------------------------------------------------------\n");
                    fprintf(output, "\tRegistered (%d)\t|\tWaiting List (%d)\n",course->sregistered,course->swaiting);
                    fprintf(output, "-------------------------------------------------------\n");
                    if(course->swaiting<course->sregistered){
                        max=course->sregistered;
                    }
                    else{
                        max=course->swaiting;
                    }
                    for(int j=0; j<max; j++){
                        if(studentw==NULL && student!=NULL){
                            fprintf(output,"%s(%s)\t|\t\n",student->sname,student->sid);
                            student=student->next;
                        }
                        else if(student==NULL && studentw!=NULL){
                            fprintf(output,"\t\t\t\t|\t%s(%s)\n",studentw->sname,studentw->sid);
                            studentw=studentw->next;
                        }
                        else if(student!=NULL && studentw!=NULL){
                            fprintf(output,"%s(%s)\t|\t%s(%s)\n",student->sname,student->sid,studentw->sname,studentw->sid);
                            studentw=studentw->next;
                            student=student->next;
                        }
                    }
                    fprintf(output, "-------------------------------------------------------\n\n");
                    course=course->next;
                }
                printf("Done! Results are saved in output.txt\n");
                break;
            case(2):
                bubblec(headc);
                course=headc->next;
                fprintf(output,"Courses of this semester:\n");
                while(course!=NULL){
                    fprintf(output,"*%s (%s): %d students registered, and %d students on the waiting list.\n",course->cname,course->cid,course->sregistered,course->swaiting);
                    course=course->next;
                }
                printf("Done! Results are saved in output.txt\n");
                break;
            case(3):
                course=headc->next;
                fprintf(output,"Courses with less than 5 students:\n");
                while(course!=NULL){
                    if(course->sregistered<5){
                        fprintf(output,"*%s (%s)\n",course->cname, course->cid);
                    }
                    course=course->next;
                }
                printf("Done! Results are saved in output.txt\n");
                break;
            case(4):
                printf("Enter course ID:");
                scanf("%s",&coursename);
                if(findc(coursename,headc)!=NULL){
                    course=findc(coursename,headc);
                    fprintf(output,"%s has:\n",coursename);
                    student=course->students[0]->next;
                    for (int j=0; j<course->sregistered; j++) {
                        fprintf(output,"*%s (ID: %s)\n", student->sname, student->sid);
                        student=student->next;
                    }
                }
                printf("Done! Results are saved in output.txt\n");
                break;
            case(5):
                printf("Enter course ID:");
                scanf("%s",&coursename);
                printf("Enter Student ID to search for:");
                scanf("%s",&studentid);
                course=findc(coursename,headc);
                if(course!=NULL) {
                    student = finds(studentid, course->students[0]);
                    if (student != NULL) {
                        fprintf(output, "%s (ID: %s) is found registered in %s.\n", student->sname, student->sid,
                                course->cid);
                    } else {
                        fprintf(output, "Student with ID:%s is not found registered in %s.\n", studentid, coursename);
                    }
                    student = finds(studentid, course->students[1]);
                    if (student != NULL) {
                        fprintf(output, "%s (ID: %s) is found on the waiting list for %s.\n", student->sname,
                                student->sid, course->cid);
                    }
                }
                else
                    fprintf(output, "%s course is not available this semester!\n",coursename);
                printf("Done! Results are saved in output.txt\n");
                break;
            case(6):
                printf("Shutting down...");
                break;
            default:
                printf("Invalid option! Retry please!");
        }
    }while(option!=6);

    fclose(output);

    return 0;
}