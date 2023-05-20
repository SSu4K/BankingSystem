#include "data.h"

#define filename "data.txt"

#define ACCOUNT_NUMBER_SHIFT 0X1111

FILE * file;
int accounts_count = 0;
account_t* current_account;

int data_open(){
    file = fopen(filename, "ab+");
    if(file == NULL){
        fprintf(stderr, "Failed to open data file!\n");
        return 0;
    }
    fprintf(stderr, "Data file opened succesfully!\n");
    current_account = new_account();
    fseek(file, 0, SEEK_END);
    accounts_count=ftell(file)/sizeof(account_t);

    printf("Founf %d accounts.\n", accounts_count);
    //accounts_count = ftell(file)/sizeof(account_t);
    return 1;
}

int data_close(){
    fclose(file);
    free(current_account);
    fprintf(stderr, "File closed!\n");
    return 1;
}

//int write_account()
int create_new_account(){
    if(file==NULL){
        return 0;
    }
    user_input_account_data(current_account);
    current_account->number=accounts_count+ACCOUNT_NUMBER_SHIFT;
    fseek(file, accounts_count*sizeof(account_t), SEEK_SET);
    fwrite(current_account, sizeof(account_t), 1, file);
    accounts_count++;
    return 1;
}

int read_account(account_t* account, int number){
    fseek(file, number*sizeof(account_t), SEEK_SET);
    fread(account, sizeof(account_t), 1, file);
    return 1;
}

void accounts_print(){
    print_account_header();
    for(int i=0;i<accounts_count;i++){
        read_account(current_account, i);
        print_account(current_account);
    }
}