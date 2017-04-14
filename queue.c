/* queue.c by Hongfei Yang (hongfeiy1@student.unimelb.edu.au) as part of his
 * assignment 1 for COMP20007 Design of Algorithms.
 *
 * Date Created: 22 March 2017
 *
 * Hongfei Yang, Student ID 783661
 */
#include <stdio.h>
#include "queue.h"
#include "list.h"

/******************************************************************************/
/*
 * enqueue
 */
int enqueue(Queue *queue, const void *data) {
    return dlist_ins_next(queue, queue_bottom(queue), data);
}

/******************************************************************************/
/*
 * dequeue
 */
int dequeue(Queue *queue, void **data) {
    return dlist_remove(queue, queue_front(queue), data);
}
