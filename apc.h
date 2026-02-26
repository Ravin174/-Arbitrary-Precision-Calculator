#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct node
{
	struct node *prev;
	int data;
	struct node *next;
}Dlist;

/* Include the prototypes here */
int insert_first(Dlist **head, Dlist **tail, int data);
int insert_last(Dlist **head, Dlist **tail, int data);
int list_compare(Dlist *head1, Dlist *head2);
void print_list(Dlist *head);
void print_list_debug(Dlist *head);
void delete_list(Dlist **head, Dlist **tail);
int delete_last(Dlist **head, Dlist **tail);
int delete_first(Dlist **head, Dlist **tail);
void trim_leading_zeros(Dlist **head, Dlist **tail);

/* NEW PROTOTYPES FOR DIVISION */
void list_copy(Dlist *src_h, Dlist **dest_h, Dlist **dest_t);
void division_subtract(Dlist **minuend_h, Dlist **minuend_t, Dlist *subtrahend_h, Dlist *subtrahend_t);

/* Store the operands into the list */
void digit_to_list(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,char *argv[]);

/* Addition */
int addition(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR);

/* Subtraction */
int subtraction(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR);

/* Multiplication */
int multiplication(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR);


/* Division */
int division(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR);

#endif