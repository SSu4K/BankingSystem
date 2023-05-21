#include "interface.h"
#include <string.h>

#define INTERFACE_WIDTH 40

#define LABELS_COUNT 5
char* labels[LABELS_COUNT] = {"BANKING SYSYTEM", "1. List all accounts" , "2. Add an account", "3. Get accounts balance", "0. Exit"};

int system_open(){
    if(data_open()){
        printf("Sucessfully opened the Banking System!\n");
        return 1;
    }
    return 0;
}
int system_close(){
    if(data_close()){
        printf("Sucessfully closed the Banking System!\n");
        return 1;
    }
    return 0;
}

void print_multiple(char c, int n){
    for(int i = 0; i<n;i++, printf("%c", c));
}

int get_action(){
    print_multiple('_', INTERFACE_WIDTH);
    printf("\n| ");
    print_multiple(' ', (INTERFACE_WIDTH-4-strlen(labels[0]))/2);
    printf("%s", labels[0]);
    print_multiple(' ', INTERFACE_WIDTH-4-(INTERFACE_WIDTH-4-strlen(labels[0]))/2-strlen(labels[0]));
    printf(" |\n|");
    print_multiple(' ', INTERFACE_WIDTH-2);
    printf("|\n");
    for(int i=1;i<LABELS_COUNT;i++){
        printf("| ");
        printf("%s", labels[i]);
        print_multiple(' ', INTERFACE_WIDTH-4-strlen(labels[i]));
        printf(" |\n");
    }
    printf("|");
    print_multiple('_', INTERFACE_WIDTH-2);
    printf("|\n\n  Choose action: ");
    
    int action;
    scanf("%d", &action);
    return action;
}

int system_run(){
    int action;
    while(action = get_action()){
        if(action==1){
            accounts_print();
        }
        if(action==2){
            create_new_account();
        }
        if(action==3){
            unsigned int number;
            printf("Input account number: ");
            scanf("%x", &number);
            account_balance_print(number);
        }
    }
}