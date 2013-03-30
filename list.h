#include "gl_def.h"
#ifndef __ADLIST_H__
#define __ADLIST_H__
typedef struct listNode {
	struct listNode *prev;
	struct listNode *next;
	void *value;
} listNode;

typedef struct list {
	listNode *head;
	listNode *tail;
	
	unsigned int len;
} list;

typedef struct listIter {
	listNode *next;
	int direction;
} listIter;

typedef struct Account{
	char *acc_type;
	char *acc_id;
	char *acc_pwd;
}Account;

/*global data*/
list gl_list;
/*prototype*/

list *listCreate(void);
void listRelease(list *list);
list *listAddNodeHead(list *list,void *value);
list *listAddNodeTail(list *list,void *value);
bool initList(list *list);
bool insertList(list *list,char *type,char *id,char *pwd);
bool listDelNode(list *list,listNode *node);
void showListNode(listNode *node);
listNode *searchListByTypeAndID(list *list,char *type,char *id);
bool freeListNode(listNode *node);
bool freeAccount(Account *pac);
#endif
