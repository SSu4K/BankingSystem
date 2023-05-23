#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

#include <stdint.h>

#define NAME_SIZE 15
#define SURNAME_SIZE 20
#define ADDRESS_SIZE 40
#define PESEL_SIZE 12

typedef struct{
    uint16_t number;
    char name[NAME_SIZE];
    char surname[SURNAME_SIZE];
    char adress[ADDRESS_SIZE];
    char pesel[PESEL_SIZE];
    long regular_balance;
    long savings_balance;

}account_t;

account_t *new_account();
void print_account_header();
void print_account_footer();
void print_account(account_t* account);

int comp_number(account_t *account1, account_t *account2);
int comp_name(account_t *account1, account_t *account2);
int comp_surname(account_t *account1, account_t *account2);
int comp_adress(account_t *account1, account_t *account2);
int comp_pesel(account_t *account1, account_t *account2);

#endif