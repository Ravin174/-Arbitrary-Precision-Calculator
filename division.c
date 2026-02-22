#include "apc.h"

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    /* 1. Handle division by zero */
    if ((*head2)->data == 0 && (*head2)->next == NULL)
    {
        printf("Error: Division by zero.\n");
        return FAILURE;
    }

    // Initial comparison and edge cases //
    int compare_res = list_compare(*head1, *head2);

    if (compare_res == -1) // num1 < num2 //
    {
        insert_first(headR, tailR, 0);
        return SUCCESS;
    }
    
    if (compare_res == 0) 
    {
        insert_first(headR, tailR, 1);
        return SUCCESS;
    }
    
    // Setup for Long Division //
    Dlist *sub_h = NULL;
    Dlist *sub_t = NULL;

    // Temporary pointer to iterate through the dividend (num1) //
    Dlist *curr = *head1;
    int quotient_started = 0;
    // The length of the divisor //
    Dlist *t2 = *head2;
    int divisor_len = 0;
    while (t2) { divisor_len++; t2 = t2->next; }

    ///Pre-load the initial working remainder with enough digits (divisor_len) //
    for (int i = 0; i < divisor_len && curr != NULL; i++)
    {
        insert_last(&sub_h, &sub_t, curr->data);
        curr = curr->next;
    }
    
    // If the pre-loaded number is still smaller, load one more digit //
    if (list_compare(sub_h, *head2) == -1 && curr != NULL)
    {
         insert_last(&sub_h, &sub_t, curr->data);
         curr = curr->next;
    }

    // CORE LONG DIVISION LOOP //
    while (curr != NULL || sub_h != NULL) 
    {
        int q = 0;
        
        //Find 'q' using repeated subtraction (q * divisor <= sub_h) //
        while (sub_h != NULL && list_compare(sub_h, *head2) >= 0)
        {
            // Subtract divisor from working remainder IN PLACE //
            division_subtract(&sub_h, &sub_t, *head2, *tail2);
            q++;
        }
        // Append Quotient Digit //
        if (q > 0 || quotient_started)
        {
            insert_last(headR, tailR, q);
            quotient_started = 1;
        } 
        else if (quotient_started) 
        {
             insert_last(headR, tailR, 0);
        }

        // Load Next Digit //
        if (curr != NULL)
        {
            // If the working remainder is empty (subtraction resulted in 0) //
            if (sub_h == NULL)
            {
                insert_last(&sub_h, &sub_t, curr->data);
                curr = curr->next;
            }
            else 
            {
                 insert_last(&sub_h, &sub_t, curr->data);
                 curr = curr->next;
            }
            
            //If the remainder is still too small, the quotient digit is 0, handle it now //
            if (curr != NULL && list_compare(sub_h, *head2) == -1)
            {
                 if (quotient_started)
                 {
                    insert_last(headR, tailR, 0);
                 }
            }
        }
        
        // Termination check: if no more dividend and no more remainder to process //
        if (curr == NULL && sub_h != NULL && list_compare(sub_h, *head2) == -1)
        {
             break;
        }
        
        if (curr == NULL && sub_h == NULL)
        {
            break;
        }
    }
    
    //  Final Cleanup //
    delete_list(&sub_h, &sub_t);

    // If the quotient list is empty, the result is 0 //
    if (*headR == NULL)
    {
        insert_first(headR, tailR, 0);
    }
    
    return SUCCESS;
}
