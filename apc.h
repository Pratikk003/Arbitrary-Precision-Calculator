#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS  0
#define FAILURE -1

/* One digit per node, most significant digit at head */
typedef struct node
{
    struct node *prev;
    int data;
    struct node *next;
} Dlist;

/* ---------- list.c : doubly linked list helpers ---------- */
int  insert_at_first(Dlist **head, Dlist **tail, int data);
int  insert_at_last(Dlist **head, Dlist **tail, int data);
void delete_list(Dlist **head, Dlist **tail);
void remove_leading_zeros(Dlist **head, Dlist **tail);
int  string_to_list(const char *digits, Dlist **head, Dlist **tail);
int  is_zero(Dlist *head);
void print_list(Dlist *head);

/* ---------- validate.c : input validation + comparison ---------- */
int validate_operator(const char *op, char *out_op);
int validate_operand(const char *str, int *sign, const char **digits);
/* returns 1 if head1 > head2, -1 if head2 > head1, 0 if equal (magnitude) */
int compare_lists(Dlist *head1, Dlist *head2);

/* ---------- sign.c : sign handling ---------- */
void handle_sign(char op, int sign1, int sign2, int cmp,
                 int *sign, char *mag_op, int *swap);

/* ---------- arithmetic on magnitudes (non-negative numbers) ---------- */
int addition(Dlist *h1, Dlist *t1, Dlist *h2, Dlist *t2,
             Dlist **hr, Dlist **tr);
int subtraction(Dlist *h1, Dlist *t1, Dlist *h2, Dlist *t2,   /* needs |1| >= |2| */
                Dlist **hr, Dlist **tr);
int multiplication(Dlist *h1, Dlist *t1, Dlist *h2, Dlist *t2,
                   Dlist **hr, Dlist **tr);
int division(Dlist *h1, Dlist *t1, Dlist *h2, Dlist *t2,
             Dlist **hq, Dlist **tq, Dlist **hrem, Dlist **trem);

/* ---------- driver (main.c) ---------- */
int calculate(const char *s1, const char *op, const char *s2);

#endif
