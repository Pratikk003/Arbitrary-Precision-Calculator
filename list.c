#include "apc.h"

static Dlist *new_node(int data)
{
    Dlist *n = malloc(sizeof(Dlist));
    if (!n) return NULL;
    n->data = data;
    n->prev = n->next = NULL;
    return n;
}

int insert_at_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *n = new_node(data);
    if (!n) return FAILURE;
    if (*head == NULL)
        *head = *tail = n;
    else
    {
        n->next = *head;
        (*head)->prev = n;
        *head = n;
    }
    return SUCCESS;
}

int insert_at_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *n = new_node(data);
    if (!n) return FAILURE;
    if (*head == NULL)
        *head = *tail = n;
    else
    {
        n->prev = *tail;
        (*tail)->next = n;
        *tail = n;
    }
    return SUCCESS;
}

void delete_list(Dlist **head, Dlist **tail)
{
    Dlist *cur = *head, *next;
    while (cur)
    {
        next = cur->next;
        free(cur);
        cur = next;
    }
    *head = *tail = NULL;
}

/* keep at least one node so zero is represented as "0" */
void remove_leading_zeros(Dlist **head, Dlist **tail)
{
    while (*head && (*head)->data == 0 && (*head)->next)
    {
        Dlist *tmp = *head;
        *head = tmp->next;
        (*head)->prev = NULL;
        free(tmp);
    }
    (void)tail;
}

int string_to_list(const char *digits, Dlist **head, Dlist **tail)
{
    for (int i = 0; digits[i]; i++)
        if (insert_at_last(head, tail, digits[i] - '0') == FAILURE)
            return FAILURE;
    remove_leading_zeros(head, tail);
    return SUCCESS;
}

int is_zero(Dlist *head)
{
    return head && head->data == 0 && head->next == NULL;
}

void print_list(Dlist *head)
{
    for (Dlist *t = head; t; t = t->next)
        putchar('0' + t->data);
}
