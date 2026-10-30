#include "apc.h"

/* list * single digit, then shifted left by 'shift' places (appended zeros) */
static int single_digit_multiply(Dlist *t1, int digit, int shift,
                                 Dlist **hr, Dlist **tr)
{
    int carry = 0;

    for (int i = 0; i < shift; i++)
        if (insert_at_first(hr, tr, 0) == FAILURE) return FAILURE;

    for (Dlist *a = t1; a || carry; )
    {
        int prod = carry;
        if (a) { prod += a->data * digit; a = a->prev; }
        carry = prod / 10;
        if (insert_at_first(hr, tr, prod % 10) == FAILURE) return FAILURE;
    }
    remove_leading_zeros(hr, tr);
    return SUCCESS;
}

/* each (digit x number) partial product is fed to addition() */
int multiplication(Dlist *h1, Dlist *t1, Dlist *h2, Dlist *t2,
                   Dlist **hr, Dlist **tr)
{
    int shift = 0;
    (void)h2;

    if (insert_at_first(hr, tr, 0) == FAILURE) return FAILURE;   /* result = 0 */

    for (Dlist *b = t2; b; b = b->prev, shift++)
    {
        Dlist *ph = NULL, *pt = NULL;          /* partial product */
        Dlist *nh = NULL, *nt = NULL;          /* new running total */

        if (b->data == 0) continue;            /* contributes nothing */

        if (single_digit_multiply(t1, b->data, shift, &ph, &pt) == FAILURE)
            return FAILURE;
        if (addition(*hr, *tr, ph, pt, &nh, &nt) == FAILURE)
            return FAILURE;

        delete_list(hr, tr);
        delete_list(&ph, &pt);
        *hr = nh;
        *tr = nt;
    }
    (void)h1;
    return SUCCESS;
}
