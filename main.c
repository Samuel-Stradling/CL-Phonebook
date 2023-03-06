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

    while (fgets(buffer, 1024, file)) {
        row_count++;

        char* field = strtok(buffer, delimiter);


        //while there is a field (data delimited by delimiter)

        while (field) {
            // runs until eol
            strcat(lineBuffer, field);
            strcat(lineBuffer, ",");
            //gets the next token in the line: next csv record
            field = strtok(NULL, delimiter);

        }
    }
    printf("\n\n%s\n", lineBuffer);
    fclose(file);
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

    search_name(file, delimiter, "doublemaker");


    return 0;
}
