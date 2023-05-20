#include "data.h"

#define filename "data.txt"

FILE * file;
size_t accounts_count = 0;
account_t* current_account;

int data_open(){
    file = fopen(filename, "wb+");
    if(file == NULL){
        fprintf(stderr, "Failed to open data file!\n");
        return 0;
    }
    fprintf(stderr, "Data file opened succesfully!\n");
    return 1;
}

int data_close(){
    fclose(file);
    fprintf(stderr, "File closed!\n");
    return 1;
}