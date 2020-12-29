#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q) /* check if q is NULL to prevent the crash of q->head */
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q)
        return;

    while (q->head) {
        list_ele_t *rm_node = q->head;
        q->head = q->head->next;
        /*
         * rm_node->value is allocated by q_insert_head()
         * or q_insert_tail(), so q_free is responsible for
         * freeing it
         */
        free(rm_node->value);
        free(rm_node);
    }
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /*
     * Do NOT do this check after the malloc() next line
     * otherwise memory leak is prone to happen
     */
    if (!q)
        return false;

    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    newh->next = NULL;
    newh->value = NULL;

    /*
     * Extra 1 byte for '\0'
     */
    size_t copy_size = (sizeof(char) * strlen(s)) + (sizeof(char) * 1);
    newh->value = (char *) malloc(copy_size);
    if (!newh->value) {
        /* Failed to construct newh, free it! */
        free(newh);
        return false;
    }
    memcpy(newh->value, s, copy_size);

    /* if queue is empty */
    if (!q->head) {
        q->head = q->tail = newh;
    } else {
        newh->next = q->head;
        q->head = newh;
    }
    q->size += 1;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (!q)
        return false;

    list_ele_t *newt = malloc(sizeof(list_ele_t));
    if (!newt)
        return false;
    newt->next = NULL;
    newt->value = NULL;

    /*
     * Extra 1 byte for '\0'
     */
    size_t copy_size = (sizeof(char) * strlen(s)) + (sizeof(char) * 1);
    newt->value = (char *) malloc(copy_size);
    if (!newt->value) {
        /* Failed to construct newt, free it! */
        free(newt);
        return false;
    }
    memcpy(newt->value, s, copy_size);

    /* if queue is empty */
    if (!q->tail) {
        q->head = q->tail = newt;
    } else {
        q->tail->next = newt;
        q->tail = newt;
    }
    q->size += 1;
    return false;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || !q->head)
        return false;

    list_ele_t *rm_node = q->head;
    q->head = q->head->next;
    q->size -= 1;
    if (!q->head) /* if queue is empty after removing head */
        q->tail = NULL;

    size_t copy_size =
        (sizeof(char) * strlen(rm_node->value)) + (sizeof(char) * 1);
    if (sp) {
        memcpy(sp, rm_node->value, copy_size <= bufsize ? copy_size : bufsize);
        sp[bufsize - 1] = '\0';
    }

    free(rm_node->value);
    free(rm_node);
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q)
        return q->size;
    return 0;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
