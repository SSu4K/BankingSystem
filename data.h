#ifndef __DATA_H__
#define __DATA_H__

#include <stdio.h>
#include <stdlib.h>
#include "account.h"

int data_open();
int data_close();
int create_new_account();
void accounts_print();
void account_balance_print(int number);

#endif