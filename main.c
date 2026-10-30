#include "apc.h"

static void print_signed(Dlist *head, int sign)
{
    if (sign < 0 && !is_zero(head)) putchar('-');
    print_list(head);
}

int calculate(const char *s1, const char *op_str, const char *s2)
{
    char op, mag_op;
    int sign1, sign2, sign, swap, cmp, ret = SUCCESS;
    const char *d1, *d2;

    Dlist *h1 = NULL, *t1 = NULL, *h2 = NULL, *t2 = NULL;
    Dlist *hr = NULL, *tr = NULL, *hrem = NULL, *trem = NULL;

    if (validate_operator(op_str, &op) == FAILURE)
    {
        fprintf(stderr, "Error: invalid operator '%s' (use + - * / )\n", op_str);
        return FAILURE;
    }
    if (validate_operand(s1, &sign1, &d1) == FAILURE ||
        validate_operand(s2, &sign2, &d2) == FAILURE)
    {
        fprintf(stderr, "Error: operands must be integers (optional sign + digits)\n");
        return FAILURE;
    }
    if (string_to_list(d1, &h1, &t1) == FAILURE ||
        string_to_list(d2, &h2, &t2) == FAILURE)
    {
        fprintf(stderr, "Error: out of memory\n");
        ret = FAILURE;
        goto cleanup;
    }

    cmp = compare_lists(h1, h2);
    handle_sign(op, sign1, sign2, cmp, &sign, &mag_op, &swap);

    switch (mag_op)
    {
        case '+':
            ret = addition(h1, t1, h2, t2, &hr, &tr);
            break;
        case '-':
            ret = swap ? subtraction(h2, t2, h1, t1, &hr, &tr)
                       : subtraction(h1, t1, h2, t2, &hr, &tr);
            break;
        case '*':
            ret = multiplication(h1, t1, h2, t2, &hr, &tr);
            break;
        case '/':
            if (is_zero(h2))
            {
                fprintf(stderr, "Error: division by zero\n");
                ret = FAILURE;
                goto cleanup;
            }
            ret = division(h1, t1, h2, t2, &hr, &tr, &hrem, &trem);
            break;
    }

    if (ret == FAILURE)
    {
        fprintf(stderr, "Error: operation failed\n");
        goto cleanup;
    }

    printf("Result    : ");
    print_signed(hr, sign);
    putchar('\n');
    if (mag_op == '/')       /* remainder takes the sign of the dividend */
    {
        printf("Remainder : ");
        print_signed(hrem, sign1);
        putchar('\n');
    }

cleanup:
    delete_list(&h1, &t1);
    delete_list(&h2, &t2);
    delete_list(&hr, &tr);
    delete_list(&hrem, &trem);
    return ret;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Invalid input\n"
                        "Usage: %s <operand1> <operator> <operand2>\n"
                        "       (quote '*' as \"*\" or use x)\n", argv[0]);
        return 1;
    }

    return calculate(argv[1], argv[2], argv[3]) == SUCCESS ? 0 : 1;
}
