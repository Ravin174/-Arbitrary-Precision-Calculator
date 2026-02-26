#include "apc.h"

int insert_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if(new == NULL)
        return FAILURE;
    new -> data = data;
    new -> prev = NULL;
    new -> next = NULL;
    if(*head == NULL && *tail == NULL)
    {
        *head = new;
        *tail = new;
        return SUCCESS;
    }
    else
    {
        new -> next = *head;
        (*head) -> prev = new;
        *head = new;
        return SUCCESS;
    }
}

int insert_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if(new == NULL)
        return FAILURE;
    new -> data = data;
    new -> prev = NULL;
    new -> next = NULL;
    
    /* Check if list is empty */
    if(*head == NULL && *tail == NULL)
    {
        *head = new;
        *tail = new;
    }
    else
    {
        new -> prev = *tail;
        (*tail) -> next = new;
        *tail = new;
    }
    return SUCCESS;
}

void digit_to_list(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,char *argv[]) 
{
    /* For Operand 1 */
    for (int i = 0; argv[1][i]; i++)
    {
        int digit = argv[1][i] - '0';
        insert_last(head1, tail1, digit);
    }

    /* For Operand 2 */
    for (int i = 0; argv[3][i]; i++)
    {
        int digit = argv[3][i] - '0';
        insert_last(head2, tail2, digit);
    }
}

int list_compare(Dlist *head1, Dlist *head2)
{
    int len1 = 0, len2 = 0;
    Dlist *t1 = head1, *t2 = head2;

    /* Count length of both lists */
    while (t1) { 
        len1++; 
        t1 = t1->next; 
    }
    while (t2) { 
        len2++; 
        t2 = t2->next; 
    }

    /* Compare lengths */
    if (len1 > len2) return 1;
    if (len2 > len1) return -1;

    /* Lengths equal -> compare node by node from MOST significant digit */
    t1 = head1;
    t2 = head2;

    while (t1 && t2)
    {
        if (t1->data > t2->data) return 1;
        if (t2->data > t1->data) return -1;

        t1 = t1->next;
        t2 = t2->next;
    }
    return 0;
}

void print_list(Dlist *head)
{
    if (!head)
    {
        printf("0\n");
        return;
    }

    /* This loop prints the digits of the list */
    while (head)
    {
        printf("%d", head->data);
        head = head->next;
    }
    printf("\n");
}

void print_list_debug(Dlist *head)
{
    if (!head)
    {
        printf("INFO : List is empty\n");
        return;
    }

    printf("Head -> ");
    while (head)
    {
        printf("%d", head->data);
        head = head->next;
        if (head) 
            printf(" <-> ");
    }
    printf(" <- Tail\n");
}

/* Delete list (used to be free_list) */
void delete_list(Dlist **head, Dlist **tail)
{
    Dlist *temp = *head;
    while (temp)
    {
        Dlist *next = temp->next;
        free(temp);
        temp = next;
    }
    *head = *tail = NULL;
}

/* Delete list last node */
int delete_last(Dlist **head, Dlist **tail)
{
    if (*head == NULL)
    {
        return -1;
    }
    Dlist *temp = *tail;

    if (*head == *tail)
    {
        *head = NULL;
        *tail = NULL;
    }
    else
    {
        *tail = temp->prev;
        (*tail)->next = NULL; 
    }
    free(temp);

    return 0;
}

/* Delete list first node */
int delete_first(Dlist **head, Dlist **tail)
{
    if (*head == NULL)
    {
        return -1;
    }
    Dlist *temp = *head;

    if (*head == *tail)
    {
        *head = NULL;
        *tail = NULL;
    }
    else
    {
        *head = temp->next;
        (*head)->prev = NULL;
    }
    free(temp);
    return 0;
}

/* Function to remove leading zeros */
void trim_leading_zeros(Dlist **head, Dlist **tail)
{
    Dlist *current = *head;

    /* Keep removing nodes while the current node is 0 AND it's not the ONLY node */
    while (current != NULL && current->data == 0 && current->next != NULL)
    {
        Dlist *temp = current;
        *head = current->next;
        if (*head != NULL)
            (*head)->prev = NULL;
        free(temp);
        current = *head;
    }

    /* If, after trimming, the list is empty (or only contained zeros), insert a single 0 */
    if (*head == NULL)
    {
        insert_first(head, tail, 0);
    }
}

/* NEW: Copies a list */
void list_copy(Dlist *src_h, Dlist **dest_h, Dlist **dest_t)
{
    if (*dest_h != NULL)
        delete_list(dest_h, dest_t); /* Clear destination first */
        
    Dlist *curr = src_h;
    while (curr)
    {
        insert_last(dest_h, dest_t, curr->data);
        curr = curr->next;
    }
}

/* NEW: Specialized subtraction function for division (Minuend >= Subtrahend is guaranteed) */
void division_subtract(Dlist **minuend_h, Dlist **minuend_t, Dlist *subtrahend_h, Dlist *subtrahend_t)
{
    Dlist *result_h = NULL;
    Dlist *result_t = NULL;
    
    Dlist *t1 = *minuend_t; /* Tail of Minuend (LSD) */
    Dlist *t2 = subtrahend_t; /* Tail of Subtrahend (LSD) */
    int borrow = 0;
    
    while (t1 != NULL || t2 != NULL || borrow)
    {
        int d1 = (t1 != NULL) ? t1->data : 0;
        int d2 = (t2 != NULL) ? t2->data : 0;
        
        int diff = d1 - d2 - borrow;
        borrow = 0;
        
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        
        insert_first(&result_h, &result_t, diff);

        if (t1 != NULL) t1 = t1->prev;
        if (t2 != NULL) t2 = t2->prev;
    }

    /* Clean up and replace the original minuend list with the result */
    delete_list(minuend_h, minuend_t);
    *minuend_h = result_h;
    *minuend_t = result_t;
    
    /* Trim leading zeros from the result */
    trim_leading_zeros(minuend_h, minuend_t);
}