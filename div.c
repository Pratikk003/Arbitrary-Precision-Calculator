#include "apc.h"

/* Long division using repeated subtraction.
 * quotient -> (hq,tq), remainder -> (hrem,trem). Returns FAILURE on divide by zero. */
int division(Dlist *h1, Dlist *t1, Dlist *h2, Dlist *t2,
             Dlist **hq, Dlist **tq, Dlist **hrem, Dlist **trem)
{
    (void)t1;
    if (is_zero(h2)) return FAILURE;

    if (insert_at_last(hrem, trem, 0) == FAILURE) return FAILURE;

    for (Dlist *d = h1; d; d = d->next)
    {
        int count = 0;

        /* bring the next digit down */
        if (insert_at_last(hrem, trem, d->data) == FAILURE) return FAILURE;
        remove_leading_zeros(hrem, trem);

        /* how many times does the divisor fit? */
        while (compare_lists(*hrem, h2) >= 0)
        {
            Dlist *nh = NULL, *nt = NULL;
            if (subtraction(*hrem, *trem, h2, t2, &nh, &nt) == FAILURE)
                return FAILURE;
            delete_list(hrem, trem);
            *hrem = nh;
            *trem = nt;
            count++;
        }
        if (insert_at_last(hq, tq, count) == FAILURE) return FAILURE;
    }
    remove_leading_zeros(hq, tq);
    return SUCCESS;
}
