#include "apc.h"

/* Computes list1 - list2. Caller guarantees |list1| >= |list2| */
int subtraction(Dlist *h1, Dlist *t1, Dlist *h2, Dlist *t2,
                Dlist **hr, Dlist **tr)
{
    Dlist *a = t1, *b = t2;
    int borrow = 0;
    (void)h1; (void)h2;

    while (a)
    {
        int d = a->data - borrow;
        borrow = 0;
        if (b) { d -= b->data; b = b->prev; }
        if (d < 0) { d += 10; borrow = 1; }
        if (insert_at_first(hr, tr, d) == FAILURE)
            return FAILURE;
        a = a->prev;
    }
    remove_leading_zeros(hr, tr);
    return SUCCESS;
}
