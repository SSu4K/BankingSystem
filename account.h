#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

#include <stdint.h>

#define NAME_SIZE 10
#define SURNAME_SIZE 10
#define ADDRESS_SIZE 30
#define PESEL_SIZE 12

typedef struct{
    uint32_t number;
    char name[NAME_SIZE];
    char surname[SURNAME_SIZE];
    char adress[ADDRESS_SIZE];
    char pesel[PESEL_SIZE];
    long regular_balance;
    long savings_balance;

}account_t;

account_t *new_account();
void print_account(account_t* account);
int user_input_account_data(account_t* account);

#endif