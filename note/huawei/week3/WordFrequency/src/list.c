#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "pointerCheck.h"

typedef struct List_T {
    void *node;
    struct List_T *next;
} List;

List *ListNew(void *node)
{
    List *newList = (List *)malloc(sizeof(List));
    CHECK_NULL_RETURN_NULL(newList);

    memset(newList, 0, sizeof(List));
    newList->node = node;
    newList->next = NULL;

    return newList;
}

void *ListGet(List *list)
{
    CHECK_NULL_RETURN_NULL(list);
    return list->node;
}

void ListSet(List *list, void *node)
{
    CHECK_NULL_RETURN_VOID(list);
    list->node= node;
}

List *ListNext(List *list)
{
    CHECK_NULL_RETURN_NULL(list);
    return list->next;
}

static void ListSwap(List *listA, List *listB)
{
    CHECK_NULL_RETURN_VOID(listA);
    CHECK_NULL_RETURN_VOID(listB);
    void *tempNode;
    tempNode= listA->node;
    listA->node = listB->node;
    listB->node= tempNode;
}

List *ListSort(List *list, int compare(void *nodeA, void *nodeB))
{
    CHECK_NULL_RETURN_NULL(list);
    CHECK_NULL_RETURN_NULL(compare);
    List *tailList = NULL;
    List *flagList = NULL;
    while (flagList != list) {
        tailList = flagList;
        flagList = list;
        List *previousList = list;
        while (previousList->next != tailList) {
            List *currentList = previousList->next;
            if (0 > compare(previousList->node, currentList->node)) {
                ListSwap(previousList, currentList);
                flagList = previousList->next;
            }
            previousList = currentList;
        }
    }
    return list;
}

List *ListFind(List *list, void *node, bool equal(void *nodeA, void *nodeB))
{
    CHECK_NULL_RETURN_NULL(list);
    CHECK_NULL_RETURN_NULL(equal);
    do {
        if (true == equal(list->node, node)) {
            return list;
        }
        list = list->next;
    } while (NULL != list);
    return NULL;
}

List *ListAppend(List *list, List *tail)
{
    if (NULL == list) {
        return tail;
    } else {
        List *currentTail = list;
        while (NULL != currentTail->next) {
            currentTail = currentTail->next;
        }
        currentTail->next = tail;
        return list;
    }
}

void ListFree(List **list)
{
    CHECK_NULL_RETURN_VOID(list);
    CHECK_NULL_RETURN_VOID(*list);
    List *next = NULL;
    do {
        next = (*list)->next;
        free(*list);
        *list = next;
    } while (NULL != *list);
}