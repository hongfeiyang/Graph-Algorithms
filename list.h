/* list.h by Hongfei Yang (hongfeiy1@student.unimelb.edu.au) as part of his
 * assignment 1 for COMP20007 Design of Algorithms.
 *
 * Date Created: 22 March 2017
 *
 * Hongfei Yang, Student ID 783661
 */

#ifndef LIST_H
#define LIST_H
#include <stdlib.h>

/******************************************************************************/
/* 
 * structure of doubly-linked list
 */
typedef struct dlistelmt DListElmt;

struct dlistelmt {
    void *data;
    DListElmt *prev;
    DListElmt *next;
};

typedef struct {
    int size;
    void (*destroy)(void *data);
    DListElmt *head;
    DListElmt *tail;
} DList;

/******************************************************************************/
/* 
 * function prototypes
 */
DList* dlist_init(void (*destroy)(void *data));
int dlist_ins_next(DList *list, DListElmt *element, const void *data);
int dlist_ins_prev(DList *list, DListElmt *element, const void *data);
int dlist_remove(DList *list, DListElmt *element, void **data);
void dlist_destroy(DList *list);
void data_destroy(void *data);

/******************************************************************************/
/*
 * macros for list operation
 */
#define dlist_size(list) ((list)->size)
#define dlist_head(list) ((list)->head)
#define dlist_tail(list) ((list)->tail)
#define dlist_is_head(element) ((element)->prev == NULL ? 1 : 0)
#define dlist_is_tail(element) ((element)->next == NULL ? 1 : 0)
#define dlist_data(element) ((element)->data)
#define dlist_next(element) ((element)->next)
#define dlist_prev(element) ((element)->prev)

/******************************************************************************/
/* 
 * constants
 */
#define ERROR 1

#endif
