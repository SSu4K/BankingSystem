#include "data.h"

#define filename "data.txt"

#define ACCOUNT_NUMBER_SHIFT 0x1111
#define ACCOUNT_NUMBER_MULTIPLY 0x0005

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

int get_account_number(int id){
    return id*ACCOUNT_NUMBER_MULTIPLY+ACCOUNT_NUMBER_SHIFT;
}

int get_account_id(uint16_t number){
    if(number < ACCOUNT_NUMBER_SHIFT) return -1;
    number-=ACCOUNT_NUMBER_SHIFT;
    if(number%ACCOUNT_NUMBER_MULTIPLY!=0) return -1;
    return number/ACCOUNT_NUMBER_MULTIPLY;
}

int read_account(account_t* account, int id){
    fseek(file, id*sizeof(account_t), SEEK_SET);
    fread(account, sizeof(account_t), 1, file);
    return 1;
}

int write_account(account_t* account, int id){
    fseek(file, id*sizeof(account_t), SEEK_SET);
    fwrite(account, sizeof(account_t), 1, file);
    return 1;
}

int create_new_account(){
    if(file==NULL){
        return 0;
    }
    printf("\tCreating a new account:\n");
    user_input_account_data(current_account);
    current_account->number=get_account_number(accounts_count);
    write_account(current_account, accounts_count);
    accounts_count++;
    return 1;
}

void balance_print(int balance){
    printf("%d.%.2d zl", balance/100, balance%100);
}

void account_balance_print(int number){
    int id = get_account_id(number);
    if(id<0||id>=accounts_count){
        fprintf(stderr, "Account %.4x does not exist!\n", number);
        return;
    }
    read_account(current_account, id);
    account_print(current_account);
    printf("\nRegular balance: ");
    balance_print(current_account->regular_balance);
    printf("\nSavings balance: ");
    balance_print(current_account->savings_balance);
    printf("\n");
}

void account_print(account_t* account){
    print_account_header();
    print_account(account);
    print_account_footer();
}

void accounts_print(){
    print_account_header();
    for(int i=0;i<accounts_count;i++){
        read_account(current_account, i);
        print_account(current_account);
    }
    print_account_footer();
    printf("\n");
}