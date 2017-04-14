/* traverse.c by Hongfei Yang (hongfeiy1@student.unimelb.edu.au) as part of his
 * assignment 1 for COMP20007 Design of Algorithms.
 *
 * Date Created: 22 March 2017
 *
 * Hongfei Yang, Student ID 783661
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "traverse.h"
#include "stack.h"
#include "list.h"
#include "queue.h"

/******************************************************************************/

/* constants */

#define INCLUDEWEIGHT 1
#define EXCLUDEWEIGHT 0

#define VISITED 1
#define UNVISITED 0

#define VERTEX_ID 0
#define WEIGHT 1

#define PATH_MEM_SIZE 2

/******************************************************************************/

/* macros for printing a vertex */
#define print_label(vertex) (printf("%s\n", (vertex)->label))

/******************************************************************************/
/*
 * functions that will find the next unvisited edge for a given vertex
 */
Edge *next_unv_edge(Vertex *vertex, int* visited, Edge **nxt_edge) {
    
    /* resume from last position */
    Edge *edge = nxt_edge[vertex->first_edge->u];
    
    /* reach the end of all edge for a given vertex, return NULL */
    if (edge==NULL) {
        return NULL;
    }
    
    /* find the next unvisited edge */
    while (visited[edge->v]==VISITED) {
        edge = edge->next_edge;
        if (edge == NULL) {
            return NULL;
        }
    }
    /* adjust the records to ensure each edge is accessed once only */
    nxt_edge[vertex->first_edge->u] = edge->next_edge;
    
    return edge;
    
}

/******************************************************************************/
/* 
 * given an array of vertex id, this function will print out their labels
 * accordingly
 */
void print_path(Graph *graph, int (*path)[PATH_MEM_SIZE], int depth, int mode) {
    int j;
    
    if (mode==EXCLUDEWEIGHT) {
        
        /* print label only */
        for (j=0; j<depth; j++) {
            printf("%s, ", graph->vertices[path[j][VERTEX_ID]]->label);
        }
        
    } else {
        
        /* print label and weight */
        for (j=0; j<depth; j++) {
            printf("%s (%dkm)\n",
                   graph->vertices[path[j][VERTEX_ID]]->label, path[j][WEIGHT]);
        }
    }
}

/******************************************************************************/
/*
 * depth-first traversal of the graph from a given source
 */
void print_dfs(Graph* graph, int source_id) {
    
    /* store visited records */
    int *visited= calloc(graph->maxn, sizeof(int));
    
    /* store pointer to data in the stack after stack pops */
    void *data;
    Stack *stack;
    Vertex *curr_vertex;
    Edge *nxt_edge[graph->n], *next_avail_edge;
    
    stack = stack_init(data_destroy);
    
    /* put the first vertex into the stack, mark it as visited */
    curr_vertex = graph->vertices[source_id];
    print_label(curr_vertex);
    visited[source_id] = VISITED;
    nxt_edge[source_id] = curr_vertex->first_edge;
    stack_push(stack, curr_vertex);
    
    
    /* try to explore every vertex */
    while (stack_size(stack)>0) {
        
        /* get the next unvisited edge */
        next_avail_edge = next_unv_edge(stack_peek(stack), visited, nxt_edge);
        
        if (next_avail_edge!=NULL) {
            /* yes, there is new unexplored edge, so go ahead and visit it */
            
            /* mark it as visited and record its next unvisited edge */
            curr_vertex = graph->vertices[next_avail_edge->v];
            visited[curr_vertex->first_edge->u] = VISITED;
            
            /* store the next edge of all vertices to ensure that each edge
             * is only accessed once */
            nxt_edge[curr_vertex->first_edge->u] = curr_vertex->first_edge;
            
            print_label(curr_vertex);
            stack_push(stack, curr_vertex);
            
        } else {
            
            /* all edge of the current vertex have been explored,
             * so return to the earlier vertex */
            stack_pop(stack, (void**)&data);
        }
    }
    
    /* finished exploring, free all structures */
    free(visited);
    stack_destroy(stack);
}

/******************************************************************************/
/*
 * breadth-first traversal of the graph from a given source
 */
void print_bfs(Graph* graph, int source_id) {
    
    /* store records */
    int *visited= calloc(graph->maxn, sizeof(int));
    
    /* store the pointer to data in the queue after dequeue */
    void *data;
    Queue *queue;
    Vertex *curr_vertex;
    Edge *nxt_edge[graph->n], *next_avail_edge;
    
    queue = queue_init(data_destroy);
    
    /* put the first vertex on the queue */
    curr_vertex = graph->vertices[source_id];
    print_label(curr_vertex);
    visited[source_id] = VISITED;
    nxt_edge[source_id] = curr_vertex->first_edge;
    enqueue(queue, curr_vertex);
    
    /* try to explore every vertex */
    while (queue_size(queue)>0) {
        
        /* get the next unvisited edge */
        next_avail_edge = next_unv_edge(queue_peek(queue), visited, nxt_edge);
        
        if (next_avail_edge!=NULL) {
            /* there is a new unexplored vertex, go ahead and visit it */
            
            /* mark it as visited and record its next unvisited edge */
            curr_vertex = graph->vertices[next_avail_edge->v];
            visited[curr_vertex->first_edge->u] = VISITED;
            
            /* store the next edge of all vertices to ensure that each edge
             * is only accessed once */
            nxt_edge[curr_vertex->first_edge->u] = curr_vertex->first_edge;
            
            /* print out label */
            print_label(curr_vertex);
            
            enqueue(queue, curr_vertex);
            
        } else {
            
            /* all vertices around the current vertex have been explored,
             * move to the earlier vertex */
            dequeue(queue, (void**)&data);
        }
    }
    
    /* finished exploring, free all structures */
    free(visited);
    queue_destroy(queue);
}

/******************************************************************************/
/*
 * find a detailed path using depth-first search
 */
void detailed_path(Graph* graph, int source_id, int destination_id) {
    
    if (source_id == destination_id) {
        printf("%s (0km)\n", graph->vertices[source_id]->label);
        return;
    }
	
    /* store relevant records */
    int curr_depth = 0, total_weight = 0;
    int *visited= calloc(graph->maxn, sizeof(int));
    int (*curr_path)[PATH_MEM_SIZE] = calloc(graph->maxn, sizeof(*curr_path));
    
    /* store the pointer to data in the queue after dequeue */
    void *data;
    Stack *stack;
    Vertex *curr_vertex;
    
    /* store the next edge of all vertices to ensure that each edge is only
     * accessed once */
    Edge **nxt_edge, *next_avail_edge;
    
    nxt_edge = calloc(graph->n, sizeof(Edge*));
    
    stack = stack_init(data_destroy);
    
    /* put the first vertex into the stack */
    curr_vertex = graph->vertices[source_id];
    visited[source_id] = VISITED;
    nxt_edge[source_id] = curr_vertex->first_edge;
    stack_push(stack, curr_vertex);

    /* adjust the current path records */
    curr_path[curr_depth][VERTEX_ID] = source_id;
    curr_path[curr_depth++][WEIGHT] = total_weight;
    
    /* try to explore every vertex */
    while (stack_size(stack)>0) {
        next_avail_edge = next_unv_edge(stack_peek(stack), visited, nxt_edge);

        if (next_avail_edge!=NULL) {
            /* find a new unvisited vertex, but
             * is it the one we are looking for? */
            
            /* adjust the total weight to include the next vertex */
            curr_vertex = graph->vertices[next_avail_edge->v];
            
            
            if (next_avail_edge->v == destination_id) {
                
                /* yes, we have reached the destination, so 
                 * stop here and print out all vertex on the path */
                print_path(graph, curr_path, curr_depth, INCLUDEWEIGHT);
                printf("%s (%dkm)\n", curr_vertex->label,
                       total_weight+next_avail_edge->weight);
                break;
                
            } else {
                /* no, this is not the one we are looking for,
                 * so move on to the next vertex */
                
                stack_push(stack, curr_vertex);
                visited[next_avail_edge->v] = VISITED;
                
                /* store the next edge of all vertices to ensure that each edge
                 * is only accessed once while the vertex remains on the stack*/
                nxt_edge[next_avail_edge->v] = curr_vertex->first_edge;
                
                curr_path[curr_depth][VERTEX_ID] = curr_vertex->first_edge->u;
                total_weight += next_avail_edge->weight;
                curr_path[curr_depth++][WEIGHT] = total_weight;
            }
            
        } else {
            
            /* there are no unvisited vertex around the current vertex,
             * but we still have not found the destination, so backtrack
             * and try other edges */
            visited[((Vertex*)stack_peek(stack))->first_edge->u] = UNVISITED;
            stack_pop(stack, (void**)&data);
            
            /* adjust the depth and weight */
            curr_depth--;
            if (curr_depth) {
                total_weight = curr_path[curr_depth-1][WEIGHT];
            }
        }
    }
    
    /* finished, free all data structures */
    free(nxt_edge);
    free(curr_path);
    free(visited);
    stack_destroy(stack);
}

/******************************************************************************/
/*
 * this will find all paths from a source to a destination
 */
void all_paths(Graph* graph, int source_id, int destination_id) {
    
    if (source_id == destination_id) {
        printf("%s\n", graph->vertices[source_id]->label);
        return;
    }
    
    /* store relevant records */
    int curr_depth = 0, total_weight = 0;
    int *visited= calloc(graph->maxn, sizeof(int));
    int (*curr_path)[PATH_MEM_SIZE] = calloc(graph->maxn, sizeof(*curr_path));
    
    /* store the pointer to data in the queue after dequeue */
    void *data;
    Stack *stack;
    Vertex *curr_vertex;
    
    /* store the next edge of all vertices to ensure that each edge is only
     * accessed once */
    Edge **nxt_edge, *next_avail_edge;

    nxt_edge = calloc(graph->n, sizeof(Edge*));

    stack = stack_init(data_destroy);
    
    /* put the first vertex into the stack */
    curr_vertex = graph->vertices[source_id];
    visited[source_id] = VISITED;
    nxt_edge[source_id] = curr_vertex->first_edge;
    stack_push(stack, curr_vertex);
    
    /* adjust the current path records */
    curr_path[curr_depth][VERTEX_ID] = source_id;
    curr_path[curr_depth++][WEIGHT] = total_weight;
    
    /* try to explore every vertex */
    while (stack_size(stack)>0) {
        next_avail_edge = next_unv_edge(stack_peek(stack), visited, nxt_edge);
        
        if (next_avail_edge!=NULL) {
            /* find a new unvisited vertex, 
             * but is it the one we are looking for? */
            
            /* adjust the total weight to include the next vertex */
            curr_vertex = graph->vertices[next_avail_edge->v];
            
            
            if (next_avail_edge->v == destination_id) {
                
                /* yes, we have reached the destination,
                 * so print out all vertices on the path */
                print_path(graph, curr_path, curr_depth, EXCLUDEWEIGHT);
                printf("%s\n", curr_vertex->label);
                
            } else {
                /* no, this is not the one we are looking for,
                 * so move on to the next vertex */
                
                stack_push(stack, curr_vertex);
                visited[next_avail_edge->v] = VISITED;
                
                /* store the next edge of all vertices to ensure that each edge
                 * is only accessed once while the vertex remains on the stack*/
                nxt_edge[next_avail_edge->v] = curr_vertex->first_edge;
                
                curr_path[curr_depth][VERTEX_ID] = curr_vertex->first_edge->u;
                total_weight += next_avail_edge->weight;
                curr_path[curr_depth++][WEIGHT] = total_weight;
            }
            
        } else {
            /* there are no unvisited vertex around the current vertex,
             * but we still have not found the destination, so backtrack
             * and try other edges */
            visited[((Vertex*)stack_peek(stack))->first_edge->u] = UNVISITED;
            stack_pop(stack, (void**)&data);
            
            /* adjust the depth and weight */
            curr_depth--;
            if (curr_depth) {
                total_weight = curr_path[curr_depth-1][WEIGHT];
            }
        }
    }
    
    /* finished, free all data structures */
    free(curr_path);
    free(visited);
    free(nxt_edge);
    stack_destroy(stack);
}

/******************************************************************************/
/* 
 * find the shortest path between two given vertex
 */
void shortest_path(Graph* graph, int source_id, int destination_id) {
    
    if (source_id == destination_id) {
        printf("%s (0km)\n", graph->vertices[source_id]->label);
        return;
    }
    
    /* store relevant records */
    int curr_depth = 0, total_weight = 0, min_weight = 0, min_depth = 0,
        no_of_path = 0;
    int *visited= calloc(graph->maxn, sizeof(int));
    int (*curr_path)[PATH_MEM_SIZE] = calloc(graph->maxn, sizeof(*curr_path));
    int (*min_path)[PATH_MEM_SIZE] = calloc(graph->maxn, sizeof(*curr_path));
    
    /* store the pointer to data in the queue after dequeue */
    void *data;
    
    Stack *stack;
    Vertex *curr_vertex;
    
    /* store the next edge of all vertices to ensure that each edge is only
     * accessed once */
    Edge **nxt_edge, *next_avail_edge;
    
    nxt_edge = calloc(graph->n, sizeof(Edge*));
    
    stack = stack_init(data_destroy);
    
    /* put the first vertex into the stack */
    curr_vertex = graph->vertices[source_id];
    visited[source_id] = VISITED;
    nxt_edge[source_id] = curr_vertex->first_edge;
    stack_push(stack, curr_vertex);
    
    /* adjust the current path records */
    curr_path[curr_depth][VERTEX_ID] = source_id;
    curr_path[curr_depth++][WEIGHT] = total_weight;
    
    /* try to explore every vertex */
    while (stack_size(stack)>0) {
        next_avail_edge = next_unv_edge(stack_peek(stack), visited, nxt_edge);
        
        if (next_avail_edge!=NULL) {
            /* find a new unvisited vertex,
             * but is it the one we are looking for? */
            
            /* adjust the total weight to include the next vertex */
            curr_vertex = graph->vertices[next_avail_edge->v];
            
            if (next_avail_edge->v == destination_id) {
                /* yes, we have found the destination in neighbour vertices */
                
                if (no_of_path < 1) {
                    /* first path found, so set this as minimum */
                    
                    min_depth = curr_depth;
                    min_weight = total_weight + next_avail_edge->weight;
                    memcpy(min_path, curr_path, sizeof(*min_path)*graph->maxn);
                }
                
                if ((total_weight+next_avail_edge->weight) < min_weight &&
                    no_of_path >= 1) {
                    /* new minimum found, make this the current mimimum */
                    
                    min_depth = curr_depth;
                    min_weight = total_weight + next_avail_edge->weight;
                    memcpy(min_path, curr_path, sizeof(*min_path)*graph->maxn);

                }
                
                /* and adjust the number of path found */
                no_of_path++;
                
            } else {
                /* no, this is not the one we are looking for,
                 * so move on to the next vertex */
                
                stack_push(stack, curr_vertex);
                visited[next_avail_edge->v] = VISITED;
                
                /* store the next edge of all vertices to ensure that each edge
                 * is only accessed once while the vertex remains on the stack*/
                nxt_edge[next_avail_edge->v] = curr_vertex->first_edge;
                
                curr_path[curr_depth][VERTEX_ID] = curr_vertex->first_edge->u;
                total_weight += next_avail_edge->weight;
                curr_path[curr_depth++][WEIGHT] = total_weight;
            }
            
        } else {
            /* there are no unvisited vertex around the current vertex,
             * but we still have not found the destination, so backtack
             * and try other edges */
            visited[((Vertex*)stack_peek(stack))->first_edge->u] = UNVISITED;
            stack_pop(stack, (void**)&data);
            
            /* adjust the depth and weight */
            curr_depth--;
            if (curr_depth) {
                total_weight = curr_path[curr_depth-1][WEIGHT];
            }
        }
    }
    
    /* print the shortest path stored, if any */
    if (no_of_path > 0) {
        print_path(graph, min_path, min_depth, EXCLUDEWEIGHT);
        printf("%s (%dkm)\n",
               graph->vertices[destination_id]->label, min_weight);
    } else {
        printf("NO path found\n");
    }
    
    /* finished, free all data structures */
    free(curr_path);
    free(min_path);
    free(visited);
    free(nxt_edge);
    stack_destroy(stack);
}
