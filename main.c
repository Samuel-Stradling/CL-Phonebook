#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// layout of csv: forename,surname,phonenumber <== str

int read_all(FILE *file, const char* delimiter){
    char buffer[1024];
    int row_count = 0;

    file = fopen("data.csv", "r");
    if (file == NULL) {
        printf("Could not open file, trying again\n");

        fclose(file);
        return -1;
    }

    // reads data from file stream. stores in buffer. reads 1024 characters (size of buffer).
    // reads from 'file'
    while (fgets(buffer, 1024, file)) {
        row_count++;

        char* field = strtok(buffer, delimiter);


        //while there is a field (data delimited by delimiter)

        printf("Contact %d:\n", row_count);
        while (field) {
            // runs until eol
            printf(" %s\n", field);
            //gets the next token in the line: next csv record
            field = strtok(NULL, delimiter);

        }
    }
    fclose(file);
    return 0;
}


int search_name(FILE *file, const char* delimiter, char target[]){

    char buffer[1024];
    char lineBuffer[1024]={'\0'};
    int row_count = 0;

    file = fopen("data.csv", "r");
    if (file == NULL) {
        printf("Could not open file, trying again\n");

        fclose(file);
        return -1;
    }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~ADD ALL ELEMENTS TO LINEBUFFER~~~~~~~~~~~~~~~~~~~~~  

    while (fgets(buffer, 1024, file)) {
        row_count++;

        char* field = strtok(buffer, delimiter);


        //while there is a field (data delimited by delimiter)

        while (field) {
            // runs until eol

            // concatinate the string linebuffer with the field
            strcat(lineBuffer, field);

            //conactinate the linebuffer with a comma (after each field to separate them)
            strcat(lineBuffer, ",");
            //gets the next token in the line: next csv record
            field = strtok(NULL, delimiter);

        }
    }
    fclose(file);



//~~~~~~~~~~~~~~~~~~~~~~~~~~FORMAT LINE BUFFER~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
    for(int i=0;lineBuffer[i]!='\0';i++){

        if (lineBuffer[i] == 10){ //if the character value (ascii 10) is present, replace with semicolon
            lineBuffer[i] = ';';

        }
    }

    int i = 0;
    while (i<1024){
        if (lineBuffer[i] == '\0'){
            lineBuffer[i-1] = ';';
            break;
        }
        i++;
    }


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~FIND SECTION OF CSV CONTAINING TARGET~~~~~~~~~~~~~~~~~~~
    char *result = strstr(lineBuffer, target);
    int startTargetPosition = result - lineBuffer;// index of the first letter of the first 
    //instance of the match with target
    int startTargetPositionSection; //index of semi colon before
    int endTargetPositionSection; //index of semi colon after

    for (int i = startTargetPosition; i>=0; --i){
        if (lineBuffer[i] == ';'){
            startTargetPositionSection = i+2; // a comma always follows a semicolon, so actually begins 
            //after the semicolon and after the comma
            // therefore indicates position of FIRST LETTER
        } else if (i==0){
            startTargetPositionSection=0;
        }

    }

    endTargetPositionSection = startTargetPosition;
    while (lineBuffer[endTargetPositionSection] != ';'){
        endTargetPositionSection++;
    }
    endTargetPositionSection--; // this indicates the index of the FINAL LETTER



//~~~~~~~~~~~~~~~~~~~~~~~~~PRINT ALL DETAILS OF TARGET~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    for (int i = startTargetPositionSection; i<=endTargetPositionSection; i++){
        printf("%c", lineBuffer[i]);
    }
    printf("\n");

    printf("%s\n", lineBuffer);
    printf("index of match: %d\n", startTargetPosition);
    printf("index of start: %d\n", startTargetPositionSection);
    printf("index of end: %d\n", endTargetPositionSection);

    return 0;
}


int main() {
    // creates variable 'file' of type pointer to a FILE
    FILE *file;
    const char* delimiter = ",";

    //int read = read_all(file, delimiter);    
    // while (read==-1){
    //     read = read_all(file, delimiter);
    // }

    search_name(file, delimiter, "darkness");


    return 0;
}
