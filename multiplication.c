#include "apc.h"

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR,Dlist **tailR)
{ 
    Dlist *t2 = *tail2;
    int position = 0; // Tracks the position for zero padding//

    // Iterate through the digits of the second number (t2) from right to left //
    while (t2 != NULL)
    {
        Dlist *t1 = *tail1;
        int carry = 0;
        Dlist *current_product_head = NULL;
        Dlist *current_product_tail = NULL;
        
        int digit2 = t2->data;
        
        // Add padding zeros for the current position //
        for (int i = 0; i < position; i++)
        {
            if (insert_first(&current_product_head, &current_product_tail, 0) != SUCCESS)
                return FAILURE; // Failed to pad//
        }
        
        // Multiply digit2 with all digits of the first number (t1)  //
        while (t1 != NULL)
        {
            int digit1 = t1->data;
            int product = (digit1 * digit2) + carry;
            
            int result_digit = product % 10;
            carry = product / 10;

            if (insert_first(&current_product_head, &current_product_tail, result_digit) != SUCCESS)
                return FAILURE; // Failed to insert digit//
            
            t1 = t1->prev;
        }
        
        // Add the final carry if any//
        if (carry > 0)
        {
            if (insert_first(&current_product_head, &current_product_tail, carry) != SUCCESS)
                return FAILURE; // Failed to insert carry//
        }
        
        if (*headR == NULL) // First time adding (running total is empty) //
        {
            // Copy current_product to headR
            *headR = current_product_head;
            *tailR = current_product_tail;
        }
        else
        {
            Dlist *temp_headR = NULL;
            Dlist *temp_tailR = NULL;
            
            // Re-use the existing addition function //
            if (addition(&current_product_head, &current_product_tail, headR, tailR, &temp_headR, &temp_tailR) != SUCCESS)
                return FAILURE;

            // Free the old headR and update the result pointers//
            delete_list(headR, tailR); 
            *headR = temp_headR;
            *tailR = temp_tailR;
        }
        
        position++;
        t2 = t2->prev;
    }

    return SUCCESS;
}