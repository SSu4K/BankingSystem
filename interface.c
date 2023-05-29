#include <string.h>
#include <ctype.h>
#include "interface.h"

#define INTERFACE_WIDTH 40
#define MIN_NAME 3
#define MIN_SURNAME 3

#define SYSTEM_PAD(str) "|  " str

#define MAX_LABEL_WIDTH 30

#define ACTION_LABELS_COUNT 11
char action_labels[ACTION_LABELS_COUNT][MAX_LABEL_WIDTH] = {
    "BANKING SYSYTEM",
    "1. List all accounts",
    "2. Add an account",
    "3. Show accounts balance",
    "4. Make a deposit",
    "5. Make a withdrawal",
    "6. Make a transfer",
    "7. Make sub-account transfer",
    "8. Search for accounts",
    "9. Clean database",
    "0. Exit",
};

#define SEARCH_LABELS_COUNT 7
char search_labels[SEARCH_LABELS_COUNT][MAX_LABEL_WIDTH] = {
    "SEARCH BY FIELD",
    "1. Account number",
    "2. Name",
    "3. Surname",
    "4. Adress",
    "5. Pesel",
    "0. Exit",
};

int system_open()
{
    if (data_open())
    {
        printf("Sucessfully opened the Banking System!\n");
        return 1;
    }
    return 0;
}

int system_close()
{
    if (data_close())
    {
        printf("Sucessfully closed the Banking System!\n");
        return 1;
    }
    return 0;
}

void clear_buffer()
{
    char c;
    fseek(stdin, 0, SEEK_END);
    if(ftell(stdin)==0) return;
    while (c = getchar(), c != '\n' && c != EOF)
        ;
}

int confirm()
{
    printf("This operation will cause permament changes tot the database.");
    printf("Continue? Y/n ");
    clear_buffer();
    char c;
    c = getchar();
    if (c == 'Y' || c == 'y')
        return 1;

    return 0;
}

void print_multiple(char c, int n)
{
    for (int i = 0; i < n; i++, printf("%c", c))
        ;
}

int is_alpha(char *str)
{
    while (*str != '\0')
    {
        if (!isalpha(*str))
            return 0;
        str++;
    }
    return 1;
}

int is_num(char *str)
{
    while (*str != '\0')
    {
        if (!isdigit(*str))
            return 0;
        str++;
    }
    return 1;
}

int is_alnum(char *str)
{
    while (*str != '\0')
    {
        if (!isdigit(*str) && !isalpha(*str) && *str != ' ' && *str != '/')
            return 0;
        str++;
    }
    return 1;
}

int input_money(){
    double money=0;
    if(!scanf("%lf", &money))
        return -1;
    if(money<0)
        return -1;
    return money*100;
}

int add_account()
{
    char name[NAME_SIZE];
    char surname[SURNAME_SIZE];
    char adress[ADDRESS_SIZE];
    char pesel[PESEL_SIZE];
    clear_buffer();
    printf("\nCreating new account...\n");
    printf(SYSTEM_PAD("Input name: "));
    scanf("%[^\n]s", name);
    if (strlen(name) < MIN_NAME || strlen(name) > NAME_SIZE - 1 || !is_alpha(name))
        goto incorrect_input;
    clear_buffer();
    printf(SYSTEM_PAD("Input surname: "));
    scanf("%[^\n]s", surname);
    if (strlen(surname) < MIN_NAME || strlen(surname) > SURNAME_SIZE - 1 || !is_alpha(surname))
        goto incorrect_input;
    clear_buffer();
    printf(SYSTEM_PAD("Input adress: "));
    scanf("%[^\n]s", adress);
    if (strlen(adress) < 1 || strlen(adress) > ADDRESS_SIZE - 1 || !is_alnum(adress))
        goto incorrect_input;
    clear_buffer();
    printf(SYSTEM_PAD("Input pesel: "));
    scanf("%[^\n]s", pesel);
    if (strlen(pesel) != PESEL_SIZE - 1 || !is_num(pesel))
        goto incorrect_input;

    if (!confirm())
        return 0;

    create_new_account(name, surname, adress, pesel);
    return 1;

incorrect_input:
    printf("Incorrect data!\n");
    return 0;
}

int check_balance()
{
    unsigned int number=0;
    printf("\nChecking balance...\n");
    printf(SYSTEM_PAD("Input account number: "));
    if (!scanf("%x", &number))
    {
        printf("This account does not exist!\n");
        return 0;
    }
    if (check_account_number(number))
    {
        account_balance_print(number);
    }
    else
    {
        printf("This account does not exist!\n");
    }
    return 1;
}

int deposit()
{
    unsigned int number=0;
    printf("\nMaking a deposit...\n");
    printf(SYSTEM_PAD("Input account number: "));
    if (!scanf("%x", &number))
    {
        printf("This account does not exist!\n");
        return 0;
    }
    if (check_account_number(number))
    {
        printf(SYSTEM_PAD("Input amount of money: "));
        int money=0;
        if((money=input_money())==-1)
            goto incorrect_input;
        
        if (money < 0)
        {
            goto incorrect_input;
        }
        if (confirm())
        {
            return change_balances(number, money, 0);
        }
        else
        {
            return 0;
        }
    }
    else
    {
        printf("This account does not exist!\n");
        return 0;
    }
    incorrect_input:
    printf("Incorrect input!");
    return 0;
}

int withdraw()
{
    unsigned int number=0;
    printf("\nMaking a withdrawal...\n");
    printf(SYSTEM_PAD("Input account number: "));
    if (!scanf("%x", &number))
        goto incorrect_input;
    if (check_account_number(number))
    {
        printf(SYSTEM_PAD("Input amount of money: "));
        int money=0;
        if ((money=input_money())==-1)
            goto incorrect_input;
        if (money < 0)
        {
            goto incorrect_input;
        }
        if (confirm())
        {
            return change_balances(number, -money, 0);
        }
        else
        {
            return 0;
        }
    }
    else
    {
        printf("This account does not exist!\n");
        return 0;
    }
incorrect_input:
    printf("Incorrect input!");
    return 0;
}

int transfer()
{
    unsigned int source_number=0;
    unsigned int destination_number=0;
    int money=0;
    printf("\nMaking a transfer...\n");
    printf(SYSTEM_PAD("Input source account number: "));
    if (!scanf("%x", &source_number))
        goto incorrect_input;
    if (!check_account_number(source_number))
        goto incorrect_input;
    printf(SYSTEM_PAD("Input destination account number: "));
    if (!scanf("%x", &destination_number))
        goto incorrect_input;
    if (!check_account_number(destination_number))
        goto incorrect_input;
    printf(SYSTEM_PAD("Input amount of money: "));
    if((money=input_money())==-1)
        goto incorrect_input;
        
    if (money < 0)
        goto incorrect_input;

    if (!confirm())
        return 0;

    if (change_balances(source_number, -money, 0))
    {
        if (change_balances(destination_number, money, 0))
        {
            return 1;
        }
        change_balances(source_number, money, 0);
    }
    return 0;

incorrect_input:
    printf("Incorrect input!");
    return 0;
}

int sub_transfer()
{
    unsigned int number = 0;
    int money = 0;
    int mode = 0;
    printf("\nMaking a sub-account transfer...\n");
    printf(SYSTEM_PAD("Input account number: "));
    clear_buffer();
    if (!scanf("%x", &number))
        goto incorrect_input;
    if (!check_account_number(number))
        goto incorrect_input;
    printf(SYSTEM_PAD("0: regular account -> savings account\n"));
    printf(SYSTEM_PAD("1: savings account -> regular account\n"));
    printf(SYSTEM_PAD("Choose mode: "));
    clear_buffer();
    if(!scanf("%d", &mode))
        goto incorrect_input;
        
    printf(SYSTEM_PAD("Input amount of money: "));
    clear_buffer();
    if((money=input_money())==-1)
        goto incorrect_input;
        
    if (money < 0)
        goto incorrect_input;
    if(mode!=0)
        money*=(-1);
    if(!confirm())
        return 0;
    return change_balances(number, -money, money);
incorrect_input:
    printf("Incorrect input!");
    return 0;
}

void print_box(char labels[][MAX_LABEL_WIDTH], int labels_count)
{
    print_multiple('_', INTERFACE_WIDTH);
    printf("\n| ");
    print_multiple(' ', (INTERFACE_WIDTH - 4 - strlen(labels[0])) / 2);
    printf("%s", labels[0]);
    print_multiple(' ', INTERFACE_WIDTH - 4 - (INTERFACE_WIDTH - 4 - strlen(labels[0])) / 2 - strlen(labels[0]));
    printf(" |\n|");
    print_multiple(' ', INTERFACE_WIDTH - 2);
    printf("|\n");
    for (int i = 1; i < labels_count; i++)
    {
        printf("| ");
        printf("%s", labels[i]);
        print_multiple(' ', INTERFACE_WIDTH - 4 - strlen(labels[i]));
        printf(" |\n");
    }
    printf("|");
    print_multiple('_', INTERFACE_WIDTH - 2);
    printf("|\n");
}

int search()
{
    print_box(search_labels, SEARCH_LABELS_COUNT);
    printf("\n  Choose field: ");
    int field=0;
    account_t *temp = new_account();
    clear_buffer();
    if (!scanf("%d", &field))
        goto incorrect_input;
    if (field < 1 || field > 5)
        return 1;
    if (field == 1)
    {
        unsigned int number;
        printf("\nSearching by account number...\n");
        printf(SYSTEM_PAD("Input account number: "));
        clear_buffer();
        if (!scanf("%x", &number))
            goto incorrect_input;
        if (!check_account_number(number))
            goto incorrect_input;
        temp->number = number;
        accounts_search(temp, comp_number);
    }
    else if (field == 2)
    {
        printf("\nSearching by name...\n");
        printf(SYSTEM_PAD("Input name: "));
        clear_buffer();
        if (!scanf("%[^\n]s", temp->name))
            goto incorrect_input;
        if (strlen(temp->name) < MIN_NAME || strlen(temp->name) > NAME_SIZE - 1 || !is_alpha(temp->name))
            goto incorrect_input;
        accounts_search(temp, comp_name);
    }
    else if (field == 3)
    {
        printf("\nSearching by surname...\n");
        printf(SYSTEM_PAD("Input surname: "));
        clear_buffer();
        if (!scanf("%[^\n]s", temp->surname))
            goto incorrect_input;
        if (strlen(temp->surname) < MIN_NAME || strlen(temp->surname) > SURNAME_SIZE - 1 || !is_alpha(temp->surname))
            goto incorrect_input;
        accounts_search(temp, comp_surname);
    }
    else if (field == 4)
    {
        printf("\nSearching by adress...\n");
        printf(SYSTEM_PAD("Input adress: "));
        clear_buffer();
        if (!scanf("%[^\n]s", temp->adress))
            goto incorrect_input;
        if (strlen(temp->adress) < 1 || strlen(temp->adress) > ADDRESS_SIZE - 1 || !is_alnum(temp->adress))
            goto incorrect_input;
        accounts_search(temp, comp_adress);
    }
    else if (field == 5)
    {
        printf("\nSearching by pesel...\n");
        printf(SYSTEM_PAD("Input pesel: "));
        clear_buffer();
        if (!scanf("%[^\n]s", temp->pesel))
            goto incorrect_input;
        if (strlen(temp->pesel) != PESEL_SIZE - 1 || !is_num(temp->pesel))
            goto incorrect_input;
        accounts_search(temp, comp_pesel);
    }

    free(temp);
    return 1;
incorrect_input:
    free(temp);
    printf("Incorrect input!");
    return 0;
}

int get_action()
{
    print_box(action_labels, ACTION_LABELS_COUNT);

    printf("\n  Choose action: ");
    int action;
    if (!scanf("%d", &action)){
        clear_buffer();
        return -1;
    }
    return action;
}

int system_run()
{
    int action = 1;
    int success = 0;
    while ((action = get_action()))
    {
        success = 1;
        if (action == -1 || action >= ACTION_LABELS_COUNT)
        {
            continue;
        }
        if (action == 1)
        {
            accounts_print();
        }
        else if (action == 2)
        {
            success = add_account();
        }
        else if (action == 3)
        {
            success = check_balance();
        }
        else if (action == 4)
        {
            success = deposit();
        }
        else if (action == 5)
        {
            success = withdraw();
        }
        else if (action == 6)
        {
            success = transfer();
        }
        else if (action == 7)
        {
            success = sub_transfer();
        }
        else if (action == 8)
        {
            success = search();
        }
        else if (action == 9)
        {
            confirm();
            data_clean();
        }
        if (!success)
        {
            printf("\nOperation was unsuccessfull!\n");
        }
        else
        {
            printf("\nOperation was succesfull!\n");
        }
        printf("Press anything to continue. ");
        clear_buffer();
        getchar();
    }

    return 0;
}