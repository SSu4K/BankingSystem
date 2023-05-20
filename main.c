//#include "account.h"
#include "data.h"

int main(void){
    data_open();

    create_new_account();
    //create_new_account();
    //create_new_account();
    //create_new_account();

    accounts_print();

    data_close();
    return 0;
}