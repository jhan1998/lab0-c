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
    /* TODO: What if malloc returned NULL? */
    if (q) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (!q)
        return;
    while (q->head) {
        list_ele_t *tmp = q->head;
        q->head = q->head->next;
        if (tmp->value)
            free(tmp->value);
        free(tmp);
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
    if (q) {
        list_ele_t *newh;
        /* TODO: What should you do if the q is NULL? */
        newh = malloc(sizeof(list_ele_t));
        /* Don't forget to allocate space for the string and copy it */
        /* What if either call to malloc returns NULL? */
        if (newh) {
            int len = strlen(s) + 1;
            newh->value = malloc(len);
            if (!newh->value) {
                free(newh);
                return false;
            }
            strncpy(newh->value, s, len);
            newh->next = q->head;
            q->head = newh;
            if (!q->size)
                q->tail = newh;
            q->size++;
            return true;
        }
        return false;
    }
    return false;
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
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q) {
        list_ele_t *newt = malloc(sizeof(list_ele_t));
        if (newt) {
            int len = strlen(s) + 1;
            newt->value = malloc(len);
            if (!newt->value) {
                free(newt);
                return false;
            }
            strncpy(newt->value, s, len);
            newt->next = NULL;
            if (q->size)
                q->tail->next = newt;
            else
                q->head = newt;
            q->tail = newt;
            q->size++;
            return true;
        }
        return false;
    }
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
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q && q->size != 0) {
        if (sp) {
            strncpy(sp, q->head->value, bufsize - 1);
            sp[bufsize - 1] = '\0';
        }
        list_ele_t *tmp = q->head;
        q->head = q->head->next;
        tmp->next = NULL;
        free(tmp->value);
        free(tmp);
        q->size--;
        if (!q->size)
            q->tail = NULL;
        return true;
    }
    return false;
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
    if (q) {
        return q->size;
    }
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
    if (q) {
        list_ele_t **head = &q->head;
        list_ele_t *cursor = NULL;
        q->tail = q->head;
        while (*head) {
            list_ele_t *tmp = (*head)->next;
            (*head)->next = cursor;
            cursor = *head;
            *head = tmp;
        }
        (*head) = cursor;
    }
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */

void MergeSort(queue_t *left, queue_t *right, queue_t *q)
{
    q->size = left->size + right->size;
    list_ele_t **indirect = &q->head;

    for (int i = 0; i < q->size; i++) {
        if (!right->head ||
            (left->head && strcmp(right->head->value, left->head->value) > 0)) {
            (*indirect) = left->head;
            left->head = left->head->next;
        } else {
            (*indirect) = right->head;
            right->head = right->head->next;
        }
        indirect = &(*indirect)->next;
    }
    q->tail =
        (list_ele_t *) ((char *) indirect - (long) &((list_ele_t *) 0)->next);
}

void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !q->head || q->size == 1)
        return;
    queue_t left, right;
    left.size = (q->size >> 1);
    right.size = (q->size >> 1) + (q->size & 1);
    list_ele_t *cur = left.head = q->head;
    right.tail = q->tail;

    for (size_t i = 0; i < left.size - 1; i++)
        cur = cur->next;

    left.tail = cur;
    right.head = cur->next;
    left.tail->next = NULL;

    q_sort(&left);
    q_sort(&right);
    MergeSort(&left, &right, q);
}
