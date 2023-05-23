#ifndef __DATA_H__
#define __DATA_H__

#include <stdio.h>
#include <stdlib.h>
#include "account.h"

int data_open();
int data_close();
int check_account_number(int number);
int create_new_account(char *name, char *surname, char *adress, char *pesel);
void accounts_print();
void account_balance_print(int number);
int change_balances(int number, int regular, int savings);
void data_clean();

#endif