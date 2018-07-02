#ifndef LIST_H
#define LIST_H
#include "darknet.h"

//双向链表的基本操作函数，list的定义位于include/darknet.h，下述函数的具体实现在src/list.c中
list *make_list();
int list_find(list *l, void *val);

void list_insert(list *, void *);


void free_list_contents(list *l);

#endif
