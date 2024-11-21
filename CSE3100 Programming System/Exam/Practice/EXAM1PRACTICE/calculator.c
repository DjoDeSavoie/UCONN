#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "linkedlist.h"

// Function to add two large numbers represented by linked lists
node *addition(node *num1, node *num2)
{
    node *result = NULL;
    int carry = 0;

    while (num1 != NULL || num2 != NULL || carry != 0)
    {
        int sum = carry;

        if (num1 != NULL)
        {
            sum += num1->v;
            num1 = num1->next;
        }

        if (num2 != NULL)
        {
            sum += num2->v;
            num2 = num2->next;
        }

        carry = sum / 10;
        int digit = sum % 10;

        result = prepend(result, new_node(digit));
    }
    return result;
}

// Function to subtract num2 from num1 (num1 > num2 guaranteed)
node *subtraction(node *num1, node *num2)
{
    node *result = NULL;
    int borrow = 0;

    while (num1 != NULL || num2 != NULL)
    {
        int diff = borrow;
        if (num1 != NULL)
        {
            diff += num1->v;
            num1 = num1->next;
        }
        if (num2 != NULL)
        {
            diff -= num2->v;
            num2 = num2->next;
        }

        if(diff < 0){
            diff +=10; 
            borrow = -1;
        }
        else{
            borrow = 0;
        }
        result = prepend(result, new_node(diff));
    }
    return result;
}

// Function to remove leading zeros from the result
node *remove_leading_zeros(node *num)
{
    node *temp = num;
    while (temp != NULL && temp->v == 0)
    {
        node *temp2 = temp;
        temp = temp->next;
        free(temp2);
    }
    return temp;
}

// Main function
int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: ./calculator number1 number2\n");
        exit(0);
    }

    node *num1 = NULL, *num2 = NULL;
    node *sum = NULL;
    node *difference = NULL;

    // Populate num1 from argv[1]
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Invalid input in number1\n");
            exit(0);
        }
        num1 = prepend(num1, new_node(argv[1][i] - '0'));
    }

    // Populate num2 from argv[2]
    for (int i = 0; i < strlen(argv[2]); i++)
    {
        if (!isdigit(argv[2][i]))
        {
            printf("Invalid input in number2\n");
            exit(0);
        }
        num2 = prepend(num2, new_node(argv[2][i] - '0'));
    }

    // Perform addition and subtraction
    sum = addition(num1, num2);
    difference = subtraction(num1, num2);

    // Remove leading zeros from results
    sum = remove_leading_zeros(sum);
    difference = remove_leading_zeros(difference);

    // Print results
    print_list(sum);
    print_list(difference);

    // Clean up memory
    delete_list(num1);
    delete_list(num2);
    delete_list(sum);
    delete_list(difference);

    return 0;
}