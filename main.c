#include "account.h"
#include "data.h"

int main(void){
    account_t* user;
    user = new_account();
    user_input_account_data(user);
    print_account(user);

    //data_open();
    //data_close();
    return 0;
}