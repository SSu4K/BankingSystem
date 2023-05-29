#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"

#define S(size) "%" #size "s"
#define WS(size) "%" #size "[^\n]s"

#define FORMAT(size, F) F(size)

#define ACCOUNT_FORMAT "| %.4X |" FORMAT(SURNAME_SIZE, S) " |" FORMAT(NAME_SIZE, S) " |" FORMAT(ADDRESS_SIZE, S) " |" FORMAT(PESEL_SIZE, S) " |\n"

static char labels[5][20] = {" id:", " surname:", " name:", " adress:", " pesel:"};
static int column_widths[5] = {6, SURNAME_SIZE + 1, NAME_SIZE + 1, ADDRESS_SIZE + 1, PESEL_SIZE + 1};

#define COMP_GEN_C(field)                                      \
    int comp_##field(account_t *account1, account_t *account2) \
    {                                                          \
        return strcmp(account1->field, account2->field);       \
    }

COMP_GEN_C(name)
COMP_GEN_C(surname)
COMP_GEN_C(adress)
COMP_GEN_C(pesel)

int comp_number(account_t *account1, account_t *account2)
{
    if (account1->number == account2->number)
        return 0;
    return 1;
}

account_t *new_account()
{
    account_t *account = (account_t *)malloc(sizeof(account_t));
    account->number = -1;
    account->regular_balance = 0;
    account->savings_balance = 0;
    return account;
}

static void print_multiple(char c, int n)
{
    for (int i = 0; i < n; i++, printf("%c", c))
        ;
}

void print_account_footer(void)
{
    for (int label = 0; label < 5; label++)
    {
        printf("|");
        print_multiple('_', column_widths[label]);
    }
    printf("|\n");
}

void print_account_header()
{
    int total_width = NAME_SIZE + SURNAME_SIZE + ADDRESS_SIZE + PESEL_SIZE + 8 * 2;
    print_multiple('_', total_width);
    printf("\n");
    for (int label = 0; label < 5; label++)
    {
        printf("|%s", labels[label]);
        print_multiple(' ', column_widths[label] - strlen(labels[label]));
    }
    printf("|\n");
    print_account_footer();
}

void print_account(account_t *account)
{
    printf(ACCOUNT_FORMAT, account->number, account->surname, account->name, account->adress, account->pesel);
}
