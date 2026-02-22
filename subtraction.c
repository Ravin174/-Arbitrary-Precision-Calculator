#include "apc.h"

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    // Check if the operands are equal
    int compare_res = list_compare(*head1, *head2);
    
    // If the numbers are equal, the result is 0 //
    if (compare_res == 0)
    {
        insert_first(headR, tailR, 0);
        return SUCCESS;
    }

    Dlist *max_tail;
    Dlist *min_tail;

    // Determine the larger number (Max) and the smaller number (Min)//
    int is_negative = 0;
    if (compare_res == 1) // head1 > head2 (Result is positive)//
    {
        max_tail = *tail1;
        min_tail = *tail2;
    }
    else // head2 > head1 (Result is negative)//
    {
        max_tail = *tail2;
        min_tail = *tail1;
        is_negative = 1;
    }
    
    int borrow = 0;

    // Perform subtraction from the least significant digit (tails)
    while (max_tail != NULL)
    {
        int temp1 = max_tail->data;
        int temp2 = (min_tail != NULL) ? min_tail->data : 0;
        
        temp1 -= borrow;
        borrow = 0;

        if (temp1 < temp2)
        {
            temp1 += 10;
            borrow = 1;
        }

        int diff = temp1 - temp2;
        
        if (insert_first(headR, tailR, diff) != SUCCESS)
            return FAILURE;
        
        max_tail = max_tail->prev;
        if (min_tail != NULL) min_tail = min_tail->prev;
    }
    
    // 1. Trim leading zeros//
    trim_leading_zeros(headR, tailR);
    
    // Insert the negative sign if needed (using a conventional non-digit value like -1 //
    if (is_negative)
    {
        printf("-"); 
    }

    return SUCCESS;
}