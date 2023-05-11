#ifndef LIST_H__
#define LIST_H__

#include <stdbool.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct List_T List;

List *ListNew(void *node);
void *ListGet(List *list);
void ListSet(List *list, void *node);
List *ListNext(List *list);
List * ListSort(List * list, int compare(void *nodeA, void *nodeB));
List * ListFind(List * list, void *node, bool equal(void *nodeA, void *nodeB));
List * ListAppend(List * list, List * tail);
void ListFree(List * *list);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* LIST_H__ */