#include "apc.h"

int addition(Dlist *h1, Dlist *t1, Dlist *h2, Dlist *t2,
             Dlist **hr, Dlist **tr)
{
    Dlist *a = t1, *b = t2;
    int carry = 0;
    (void)h1; (void)h2;

    while (a || b || carry)
    {
        int sum = carry;
        if (a) { sum += a->data; a = a->prev; }
        if (b) { sum += b->data; b = b->prev; }
        carry = sum / 10;
        if (insert_at_first(hr, tr, sum % 10) == FAILURE)
            return FAILURE;
    }
    remove_leading_zeros(hr, tr);
    return SUCCESS;
}
