#include "apc.h"

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	Dlist *t1 = *tail1;
    Dlist *t2 = *tail2;
    int sum = 0;
    int carry = 0;

    while (t1 != NULL || t2 != NULL)
    {
        int temp1 = (t1 != NULL) ? t1->data : 0;
        int temp2 = (t2 != NULL) ? t2->data : 0;

		sum = temp1 + temp2 + carry;
         int result_digit = sum % 10;
         carry = sum / 10 ;
        if (insert_first(headR, tailR,result_digit) != SUCCESS)
        {
            return FAILURE;
        }
        if (t1 != NULL) t1 = t1->prev;
        if (t2 != NULL) t2 = t2->prev;
    }
    if (carry > 0)
    {
        if (insert_first(headR, tailR, carry) != SUCCESS)
        {
            return FAILURE;
        }
    }
    return SUCCESS;
}
