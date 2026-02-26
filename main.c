/*
Name: RAVI J S.
Date : 17th Dec 2025.
Student ID: 25021_387.
Description:This project implements an Arbitrary Precision Calculator (APC) in C
        using doubly linked lists to store and manipulate numbers of virtually unlimited size.
        Each node in the list represents a single decimal digit, allowing for mathematical operations
        that exceed the capacity of standard data types like long long int.The system supports 
        addition, subtraction, multiplication, and division by processing digits from least
        significant to most significant while manually handling carries and borrows.
        It includes robust logic for signed arithmetic (handling negative numbers) and memory management
        to prevent leaks during complex operations. This implementation effectively demonstrates data
        structure applications in computational mathematics through custom list traversal and manipulation functions.
*/
#include "apc.h"
#include <string.h>
#include <stdio.h> 

int main(int argc, char *argv[])
{
    // Declare the pointers for three doubly linked lists (operands and result) //
    Dlist *head1=NULL, *tail1=NULL;
    Dlist *head2=NULL, *tail2=NULL; 
    Dlist *headR=NULL, *tailR=NULL;

    //Validate input count //
    if (argc != 4)
    {
        printf("Usage: %s <operand1> <operator> <operand2>\n", argv[0]);
        return -1;
    }

    //Identify and handle negative signs in command-line arguments //
    int sign1 = 1, sign2 = 1;
    char *op1 = argv[1];
    char *op2 = argv[3];

    // If the first character is '-'//
    if (op1[0] == '-')
     {
        sign1 = -1;
        // This modifies argv[1] to point to the character *after* the '-' //
        argv[1]++; 
    }
    if (op2[0] == '-') 
    {
        sign2 = -1;
        // This modifies argv[3] to point to the character *after* the '-'//
        argv[3]++; 
    }

    // Store operands into lists (absolute values) //
    digit_to_list(&head1, &tail1, &head2, &tail2, argv);
    char operator = argv[2][0];
    
    // Ensure 0 is handled if both operands were empty (e.g., just '-') //
    if (!head1 || !head2) 
    {
        // Handle error case for empty input //
        printf("Error: Invalid operand input.\n");
        // Jump to cleanup //
        goto cleanup;
    }

    //Perform the operation and determine the final sign //
    switch (operator)
    {
        case '+':
            // Case 1: (-A) + (-B) = -(A + B) //
            if (sign1 == -1 && sign2 == -1)
            {
                printf("-");
                addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            }
            //(-A) + B = B - A //
            else if (sign1 == -1 && sign2 == 1) 
            {
                int cmp = list_compare(head2, head1); // Compare B and A //
                if (cmp < 0)
                { // If B < A, result is -(A - B) //
					printf("-"); 
					subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR); // A - B //
				}
                else if (cmp > 0) 
                {
                     // If B > A, result is B - A //
					subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR); // B - A //
				}
                else
                { 
                insert_first(&headR, &tailR, 0); 
                } 
                // B = A, result is 0 ..
            }
            // A + (-B) = A - B //
            else if (sign1 == 1 && sign2 == -1)
            {
                int cmp = list_compare(head1, head2); // Compare A and B //
                if (cmp < 0) 
                { // If A < B, result is -(B - A) //
					printf("-"); 
					subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR); // B - A
				}
                else if (cmp > 0) 
                { // If A > B, result is A - B //
					subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR); // A - B
				}
                else
                { 
					insert_first(&headR, &tailR, 0); // A = B, result is 0 //
				}
            }
            //A + B //
            else 
            {
                addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            }
            print_list(headR);
            break;

        case '-':
            // Case 1: (-A) - (-B) = -A + B = B - A //
            if (sign1 == -1 && sign2 == -1) 
            { 
                int cmp = list_compare(head2, head1); // Compare B and A //
                if (cmp < 0) 
                { 
                    // If B < A, result is -(A - B)//
					printf("-"); 
					subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR); 
				}
                else if (cmp > 0) 
                { 
                    // If B > A, result is B - A //
					subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR); 
				}
                else 
                { 
					insert_first(&headR, &tailR, 0); 
				}
            }
			//(-A) - B = -(A + B) //
            else if (sign1 == -1 && sign2 == 1)
            { 
                printf("-");
                addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            }
			// (-B) = A + B//
            else if (sign1 == 1 && sign2 == -1) 
            { 
                addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            }
            //  A - B (Both positive) //
            else
            { 
                int cmp = list_compare(head1, head2); // Compare A and B//
                if (cmp < 0) 
                {
                     // If A < B, result is -(B - A) //
                    printf("-"); 
                    subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR); 
                }
                else if (cmp > 0)
                {
                     // If A > B, result is A - B //
                    subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR); 
                }
                else
                { 
                    insert_first(&headR, &tailR, 0); 
                    // A = B, result is 0
                }
            }
            print_list(headR);
            break;

        case '*':	
            // Sign is negative if signs are different//
            if (sign1 != sign2) 
            {
                if (!(head1->data == 0 && head1->next == NULL) && !(head2->data == 0 && head2->next == NULL))
                    printf("-");
            }
            multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            print_list(headR);
            break;

        case '/':	
            // Sign is negative if signs are different
            if (sign1 != sign2)
            {
                // Only print '-' if the result is non-zero (i.e., operand1 is not 0)//
                if (list_compare(head1, head2) >= 0 && (head1)->data != 0)
                    printf("-");
            }
            division(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            print_list(headR);
            break;

        default:
            printf("Invalid Input:-( Try again...\n");
    }

    // 3. Cleanup: Free all dynamically allocated lists //
    cleanup:
     delete_list(&head1, &tail1);
     delete_list(&head2, &tail2);
     delete_list(&headR, &tailR);
    return 0;
}