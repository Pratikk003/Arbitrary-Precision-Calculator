#include "apc.h"

/*
 * Works out the sign of the result and which magnitude operation to run.
 *   op        : '+', '-', '*', '/'
 *   sign1/2   : +1 or -1 for operand 1 / operand 2
 *   cmp       : compare_lists(|op1|, |op2|)
 *   sign      : (out) sign of resultant list (+1 / -1)
 *   mag_op    : (out) '+' or '-' to apply on magnitudes (or '*', '/')
 *   swap      : (out) 1 if magnitudes must be swapped for '-' (|op2| > |op1|)
 */
void handle_sign(char op, int sign1, int sign2, int cmp,
                 int *sign, char *mag_op, int *swap)
{
    *swap = 0;

    if (op == '*' || op == '/')
    {
        *mag_op = op;
        *sign = sign1 * sign2;
        return;
    }

    if (op == '-')              /* a - b  ==  a + (-b) */
        sign2 = -sign2;

    if (sign1 == sign2)         /* (+a)+(+b) or (-a)+(-b): add, keep sign */
    {
        *mag_op = '+';
        *sign = sign1;
    }
    else                        /* different signs: subtract smaller from larger */
    {
        *mag_op = '-';
        if (cmp >= 0)
            *sign = sign1;
        else
        {
            *sign = sign2;
            *swap = 1;
        }
    }
}
