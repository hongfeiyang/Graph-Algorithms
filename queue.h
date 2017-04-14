/* queue.h by Hongfei Yang (hongfeiy1@student.unimelb.edu.au) as part of his
 * assignment 1 for COMP20007 Design of Algorithms.
 *
 * Date Created: 22 March 2017
 *
 * Hongfei Yang, Student ID 783661
 */
#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include "list.h"

/******************************************************************************/
/*
 * typedef for queue
 */
typedef DList Queue;

/******************************************************************************/
/*
 * macros for queue
 */
#define queue_init dlist_init
#define queue_destroy dlist_destroy
#define queue_size dlist_size
#define queue_front(queue) ((queue)->head)
#define queue_bottom(queue) ((queue)->tail)
#define queue_peek(queue) ((queue)->head == NULL ? NULL : (queue)->head->data)

/******************************************************************************/
/*
 * function prototypes for queue
 */
int enqueue(Queue *queue, const void *data);
int dequeue(Queue *queue, void **data);

#endif
