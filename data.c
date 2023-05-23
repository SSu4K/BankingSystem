#include <string.h>
#include "data.h"

#define filename "data.txt"

#define ACCOUNT_NUMBER_SHIFT 0x1111
#define ACCOUNT_NUMBER_MULTIPLY 0x0005

FILE * file;
int accounts_count = 0;
account_t* current_account;

int data_open(){
    file = fopen(filename, "rb+");
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
    number /=ACCOUNT_NUMBER_MULTIPLY;
    if(number>=accounts_count) return -1;
    return number;
}

int check_account_number(int number){
    return get_account_id(number)!=-1;
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

int create_new_account(char *name, char *surname, char *adress, char *pesel){
    if(file==NULL){
        return 0;
    }
    strcpy(current_account->name, name);
    strcpy(current_account->surname, surname);
    strcpy(current_account->adress, adress);
    strcpy(current_account->pesel, pesel);
    current_account->number=get_account_number(accounts_count);
    print_account(current_account);
    write_account(current_account, accounts_count);
    accounts_count++;
    return 1;
}

void account_print(account_t* account){
    print_account_header();
    print_account(account);
    print_account_footer();
}

int change_balances(int number, int regular, int savings){
    int id = get_account_id(number);
    read_account(current_account, id);
    print_account(current_account);
    current_account->regular_balance+=regular;
    current_account->savings_balance+=savings;
    printf("%ld", current_account->regular_balance);
    write_account(current_account, id);
    return 1;
}

void balance_print(long int balance){
    printf("%ld.%.2ld zl", balance/100, balance%100);
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

void accounts_print(){
    print_account_header();
    for(int i=0;i<accounts_count;i++){
        read_account(current_account, i);
        print_account(current_account);
    }
    print_account_footer();
    printf("\n");
}