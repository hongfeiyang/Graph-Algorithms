/* stack.c by Hongfei Yang (hongfeiy1@student.unimelb.edu.au) as part of his
 * assignment 1 for COMP20007 Design of Algorithms.
 *
 * Date Created: 22 March 2017
 *
 * Hongfei Yang, Student ID 783661
 */
#include <stdio.h>
#include "stack.h"
#include "list.h"

/******************************************************************************/
/*
 * push an item onto the stack
 */
int stack_push(Stack *stack, const void *data) {
    return dlist_ins_prev(stack, stack_top(stack), data);
}

/******************************************************************************/
/*
 * pop an item off the stack
 */
int stack_pop(Stack *stack, void **data) {
    return dlist_remove(stack, stack_top(stack), data);
}
