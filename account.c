#include <stdio.h>
#include <stdlib.h>
#include "account.h"

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x) 
#define S(size) "%" STR(size) "s"
#define WS(size) "%" STR(size) "[^\n]s"

#define FORMAT(size, F) F(size)

#define ACCOUNT_FORMAT "%4x: " FORMAT(NAME_SIZE, S) ", " FORMAT(SURNAME_SIZE, S) ", " FORMAT(ADDRESS_SIZE, S) ", " FORMAT(PESEL_SIZE, S) "\n"

account_t *new_account(){
    account_t* account = (account_t*)malloc(sizeof(account_t));
    account->number = -1;
    account->regular_balance = 0;
    account->savings_balance = 0;
    return account;
}

void print_account(account_t* account){
    printf(ACCOUNT_FORMAT, account->number, account->surname, account->name, account->adress, account->pesel);
}

void clear_buffer(){
    char c;
    while(c = getchar(), c!='\n' && c!=EOF);
}

int user_input_account_data(account_t* account){
    int incorrect = 4;
    printf("Input user name: ");
    incorrect -= scanf(FORMAT(NAME_SIZE, S), account->name);
    printf("Input user surname: ");
    incorrect -= scanf(FORMAT(SURNAME_SIZE, S), account->surname);
    clear_buffer();
    printf("Input user address: ");
    incorrect -= scanf(FORMAT(ADDRESS_SIZE, WS), account->adress);
    printf("Input user pesel: ");
    incorrect -= scanf(FORMAT(PESEL_SIZE, S), account->pesel);

    return incorrect==0;
}