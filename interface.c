#include <string.h>
#include <ctype.h>
#include "interface.h"

#define INTERFACE_WIDTH 40
#define MIN_NAME 3
#define MIN_SURNAME 3

#define SYSTEM_PAD(str) "|  " str

#define LABELS_COUNT 8
char labels[LABELS_COUNT][30] = {
    "BANKING SYSYTEM", "1. List all accounts" ,
    "2. Add an account", "3. Get accounts balance",
    "4. Make a deposit", "5. Make a witdrawal.",
    "6. Clean database.", "0. Exit",
    };

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

void clear_buffer(){
    char c;
    while(c = getchar(), c!='\n' && c!=EOF);
}

int confirm(){
    printf("This operation will cause permament changes tot the database.");
    printf("Continue? Y/n ");
    clear_buffer();
    char c;
    c=getchar();
    if(c=='Y'||c=='y') return 1;
    
    return 0;
}

void print_multiple(char c, int n){
    for(int i = 0; i<n;i++, printf("%c", c));
}

int is_alpha(char *str){
    while(*str!='\0'){
        if(!isalpha(*str)) return 0;
        str++;
    }
    return 1;
}

int is_num(char *str){
    while(*str!='\0'){
        if(!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

int is_alnum(char *str){
    while(*str!='\0'){
        if(!isdigit(*str)&&!isalpha(*str)&&*str!=' '&&*str!='/') return 0;
        str++;
    }
    return 1;
}

int add_account(){
    char name[NAME_SIZE];
    char surname[SURNAME_SIZE];
    char adress[ADDRESS_SIZE];
    char pesel[PESEL_SIZE];

    clear_buffer();
    printf("Creating new account...\n");
    printf(SYSTEM_PAD("Input name: "));
    scanf("%[^\n]s", name);
    if(strlen(name)<MIN_NAME||strlen(name)>NAME_SIZE-1||!is_alpha(name)) goto incorrect_data;
    clear_buffer();
    printf(SYSTEM_PAD("Input surname: "));
    scanf("%[^\n]s", surname);
    if(strlen(surname)<MIN_NAME||strlen(surname)>SURNAME_SIZE-1||!is_alpha(surname)) goto incorrect_data;
    clear_buffer();
    printf(SYSTEM_PAD("Input adress: "));
    scanf("%[^\n]s", adress);
    if(strlen(adress)<1||strlen(adress)>ADDRESS_SIZE-1||!is_alnum(adress)) goto incorrect_data;
    clear_buffer();
    printf(SYSTEM_PAD("Input pesel: "));
    scanf("%[^\n]s", pesel);
    if(strlen(pesel)!=PESEL_SIZE-1||!is_num(pesel)) goto incorrect_data;
    clear_buffer();

    if(!confirm()) return 0;


    create_new_account(name, surname, adress, pesel);
    return 1;

    incorrect_data:
    printf("Incorrect data!\n");
    return 0;
}

int check_balance(){
    unsigned int number;
    printf("Checking balance...\n");
    printf(SYSTEM_PAD("Input account number: "));
    scanf("%x", &number);
    if(check_account_number(number)){
        account_balance_print(number);
    }else{
        printf("This account does not exist!\n");
    }
    return 1;
}

int deposit(){
    unsigned int number;
    printf("Making a deposit...\n");
    printf(SYSTEM_PAD("Input account number: "));
    scanf("%x", &number);
    if(check_account_number(number)){
        printf(SYSTEM_PAD("Input amount of money: "));
        int money;
        scanf("%d", &money);
        if(money<0){
            printf("Incorrect number!\n");
            return 0;
        }
        if(confirm()){
            change_balances(number, money, 0);
            return 1;
        }
        else{
            return 0;
        }
    }else{
        printf("This account does not exist!\n");
        return 0;
    }
}

int withdraw(){
    unsigned int number;
    printf("Making a withdrawal...\n");
    printf(SYSTEM_PAD("Input account number: "));
    scanf("%x", &number);
    if(check_account_number(number)){
        printf(SYSTEM_PAD("Input amount of money: "));
        int money;
        scanf("%d", &money);
        if(money<0){
            printf("Incorrect number!\n");
            return 0;
        }
        if(confirm()){
            change_balances(number, -money, 0);
            return 1;
        }
        else{
            return 0;
        }
    }else{
        printf("This account does not exist!\n");
        return 0;
    }
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
    int action = 1;
    while((action = get_action())){
        if(action==1){
            accounts_print();
        }
        else if(action==2){
            add_account();
        }
        else if(action==3){
            check_balance();
        }
        else if(action==4){
            deposit();
        }
        else if(action==5){
            withdraw();
        }
        else if(action==6){
            confirm();
            data_clean();
        }
        printf("\nPress anything to continue. ");
        clear_buffer();
        getchar();
    }

    return 0;
}