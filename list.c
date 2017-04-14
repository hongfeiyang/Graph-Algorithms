/* list.c by Hongfei Yang (hongfeiy1@student.unimelb.edu.au) as part of his
 * assignment 1 for COMP20007 Design of Algorithms.
 * 
 * Date Created: 22 March 2017
 *
 * Hongfei Yang, Student ID 783661
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

/******************************************************************************/
/*
 * create an empty list
 */
DList* dlist_init(void (*destroy)(void *data)) {
    DList *list;
    
    list = (DList*)malloc(sizeof(*list));
    
    assert(list!=NULL);
    
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
    
    return list;
}

/******************************************************************************/
/* 
 * function to destroy data stored in the list, according to the type of data
 * stored in the list
 */
void data_destroy(void *data) {
    data = NULL;
}

/******************************************************************************/
/* 
 * remove one element from the list
 */
int dlist_remove(DList *list, DListElmt *element, void **data) {
    
    /* do not allow deletion from empty list */
    if (dlist_size(list) == 0 || element == NULL) {
        return ERROR;
    }
    
    /* pointer to store the data from the element which is going to be freed */
    *data = element->data;
    
    if (dlist_is_head(element)) {
        
        /* remove from the head of the list */
        list->head = element->next;
        
        if (list->head == NULL) {
            
            /* only one element in the list, now the list is empty */
            list->tail = NULL;
            
        } else {
            
            /* more than one elements in the list, adjust the pointers */
            element->next->prev = NULL;
        }
    } else {
        
        /* remove from elsewhere in the list */
        element->prev->next = element->next;
        
        if (element->next == NULL) {
            
            /* remove from the tail of the list */
            list->tail = element->prev;
            
        } else {
            
            /* remove from elsewhere of the list */
            element->next->prev = element->prev;
        }
    }
    
    /* set the pointer to NULL as a precaution */
    element->next = element->prev = NULL;
    
    /* free the element */
    free(element);
    
    /* adjust the list size */
    list->size--;
    
    return 0;
}

/******************************************************************************/
/* 
 * free a list, element by element
 */
void dlist_destroy(DList *list) {
    
    void *data;
    
    /* recursively remove head from the list */
    while (dlist_remove(list, list->head, (void**)&data) == 0 && list->destroy) {
        
        /* call custom destroy function to handle data removed from the list */
        list->destroy(data);
    }
    
    /* verify if the list size is 0 as a precaution */
    assert(dlist_size(list)==0);
    
    free(list);
}

/******************************************************************************/
/* 
 * insert after an given element
 */
int dlist_ins_next(DList *list, DListElmt *element, const void *data) {
    
    DListElmt *new;
    
    assert(list!=NULL);
    
    /* do not allow insertion after NULL for empty list */
    if (list->size != 0 && element == NULL) {
        printf("Insert after null is not allowed for non-empty list\n");
        exit(EXIT_FAILURE);
    }
    
    /* allocation check */
    if (!(new = (DListElmt*)malloc(sizeof(*new)))) {
        printf("new elelment allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    new->data = (void*)data;
    
    if (!dlist_size(list) && element == NULL) {
        
        /* insert an element into an empty list */
        list->head = list->tail = new;
        new->prev = new->next = NULL;
        
    } else {
        
        /* insertion for non-empty list */
        new->next = element->next;
        new->prev = element;
        
        if (element->next == NULL) {
            
            /* insert at tail */
            list->tail = new;
            
        } else {
            
            /* insert into elsewhere in the list */
            element->next->prev = new;
        }
        
        element->next = new;
    }
    
    /* adjust list size */
    list->size++;
    
    return 0;
}

/******************************************************************************/
/*
 * insert before an given element
 */
int dlist_ins_prev(DList *list, DListElmt *element, const void *data) {
    
    DListElmt *new;
    
    assert(list!=NULL);
    
    /* do not allow insertion before NULL for non-empty list */
    if (dlist_size(list) != 0 && element == NULL) {
        printf("Insert before null is not allowed for non-empty list");
        exit(EXIT_FAILURE);
    }
    
    if (!(new = (DListElmt*)malloc(sizeof(*new)))) {
        printf("new elelment allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    new->data = (void*)data;
    
    
    if (!dlist_size(list) && element == NULL) {
        
        /* handle insertion into empty list */
        list->head = list->tail = new;
        new->prev = new->next = NULL;
        
    } else {
        
        /* handle insertion for non-empty list */
        new->next = element;
        new->prev = element->prev;
        
        if (element->prev == NULL) {
            
            /* insertion at head */
            list->head = new;
            
        } else {
            
            /* insertion at elsewhere */
            element->prev->next = new;
        }
        
        element->prev = new;
    }
    
    /* adjust list size */
    list->size++;
    
    return 0;
}
/******************************************************************************/
