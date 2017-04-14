/* stack.h by Hongfei Yang (hongfeiy1@student.unimelb.edu.au) as part of his
 * assignment 1 for COMP20007 Design of Algorithms.
 *
 * Date Created: 22 March 2017
 *
 * Hongfei Yang, Student ID 783661
 */
#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include "list.h"

/******************************************************************************/
/*
 * typedefs for stack
 */
typedef DList Stack;
typedef DListElmt StackElmt;

/******************************************************************************/
/*
 * macros for stack operations
 */
#define stack_init dlist_init
#define stack_destroy dlist_destroy
#define stack_size dlist_size
#define stack_top(stack) ((stack)->head)
#define stack_bottom(stack) ((stack)->tail)
#define stack_peek(stack) ((stack)->head != NULL ? (stack)->head->data : NULL)
#define stack_up(stack_elmt) ((stack_elmt)->prev)
#define stack_down(stack_elmt) ((stack_elmt)->next)
#define stack_elmt_data(stack_elmt) ((stack_elmt)->data)

/******************************************************************************/
/*
 * function prototypes
 */
int stack_push(Stack *stack, const void *data);
int stack_pop(Stack *stack, void **data);

#endif
