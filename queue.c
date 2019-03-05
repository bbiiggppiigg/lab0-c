/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL) {
        return;
    }
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    list_ele_t *it = q->head;
    while (it != q->tail) {
        list_ele_t *to_free = it;
        it = it->next;
        free(to_free->value);
        free(to_free);
    }
    if (it != NULL) {
        free(it->value);
        free(it);
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    char *news;
    /* What should you do if the q is NULL? */
    if (q == NULL) {
        return false;
    }
    newh = malloc(sizeof(list_ele_t));


    if (newh == NULL) {
        return false;
    }
    news = malloc(sizeof(char) * strlen(s) + 1);
    if (news == NULL) {
        free(newh);
        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */


    // printf("copying from string allocated at %p\n",s);
    // printf("to string allocated at %p\n",news);
    strncpy(news, s, strlen(s) + 1);

    newh->value = news;
    newh->next = q->head;

    q->head = newh;
    q->size += 1;
    if (q->tail == NULL) {
        q->tail = q->head;
    }
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newt;
    char *news;
    /* What should you do if the q is NULL? */
    if (q == NULL) {
        return false;
    }
    newt = malloc(sizeof(list_ele_t));

    if (newt == NULL) {
        return false;
    }

    news = malloc(sizeof(char) * strlen(s) + 1);
    if (news == NULL) {
        free(newt);
        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    strncpy(news, s, strlen(s) + 1);

    if (q->tail) {
        q->tail->next = newt;
        q->tail = newt;
    } else {
        q->tail = newt;
    }
    newt->value = news;
    newt->next = NULL;

    q->size += 1;
    if (q->head == NULL) {
        q->head = q->tail;
    }
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */

    if (q == NULL || q->head == NULL) {
        return false;
    }

    if (sp) {
        strncpy(sp, q->head->value, bufsize - 1);
        sp[bufsize - 1] = 0;
    }
    list_ele_t *to_free = q->head;
    if (q->tail == q->head) {
        q->tail = NULL;
    }

    q->head = q->head->next;
    // puts("freeing value, shouldn't be null");
    if (to_free->value) {
        // printf("to_free->value = %p , *to_free->value =
        // %s\n",(to_free->value),to_free->value);
        free(to_free->value);
    }
    // puts("freed value, shouldn't be null");
    if (to_free)
        free(to_free);

    q->size -= 1;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q)
        return q->size;
    return 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q == NULL || q->head == NULL)
        return;
    list_ele_t *old_head = q->head;
    list_ele_t *old_tail = q->tail;

    list_ele_t *prev = q->head;
    list_ele_t *to_reverse = q->head->next;
    while (to_reverse) {
        list_ele_t *next = to_reverse->next;
        to_reverse->next = prev;
        prev = to_reverse;
        to_reverse = next;
    }

    q->head->next = NULL;
    q->tail = old_head;
    q->head = old_tail;
}
