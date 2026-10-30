#include "apc.h"

int validate_operator(const char *op, char *out_op)
{
    if (strlen(op) != 1) return FAILURE;
    switch (op[0])
    {
        case '+': case '-': case '/':
            *out_op = op[0]; return SUCCESS;
        case '*': case 'x': case 'X':
            *out_op = '*';   return SUCCESS;
    }
    return FAILURE;
}

/* optional leading +/-, then one or more digits */
int validate_operand(const char *str, int *sign, const char **digits)
{
    *sign = 1;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-') *sign = -1;
        str++;
    }
    if (*str == '\0') return FAILURE;
    for (const char *p = str; *p; p++)
        if (!isdigit((unsigned char)*p)) return FAILURE;
    *digits = str;
    return SUCCESS;
}

static int list_length(Dlist *h)
{
    int n = 0;
    for (; h; h = h->next) n++;
    return n;
}

/* compares magnitudes (lists must have no leading zeros)
 * head1 > head2 -> 1 ; head2 > head1 -> -1 ; equal -> 0 */
int compare_lists(Dlist *head1, Dlist *head2)
{
    int l1 = list_length(head1), l2 = list_length(head2);
    if (l1 > l2) return 1;
    if (l2 > l1) return -1;
    while (head1 && head2)
    {
        if (head1->data > head2->data) return 1;
        if (head2->data > head1->data) return -1;
        head1 = head1->next;
        head2 = head2->next;
    }
    return 0;
}
