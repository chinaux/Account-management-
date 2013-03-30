#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "list.h"
list *listCreate(void){
}
void listRelease(list *list){
}
list *listAddNodeHead(list *list,void *value){
}
list *listAddNodeTail(list *list,void *value){
}
bool initList(list *list){
	FILE *pf;
	char buf[1024];
	
	char *delim=":";	
	char *p_type,*p_id,*p_pwd;
	
	if((pf = fopen(DATA_FILE,"r")) == NULL){
		printf("can't open %s",DATA_FILE);
		exit(0);
	}
	
	memset(list,0,sizeof(list));
	memset(buf,0,1024);
	while(fgets(buf,1024,pf) != NULL){
		buf[strlen(buf)-1] = '\0';	/*去除buf末尾的换行符*/
		p_type = strtok(buf,delim);
		p_id   = strtok(NULL,delim);
		p_pwd  = strtok(NULL,delim);
		
		printf("%s,%s,%s\n",p_type,p_id,p_pwd);
		insertList(list,p_type,p_id,p_pwd);
		memset(buf,0,1024);
	//	fputs(buf,stdout);
	}	
	
	fclose(pf);	
}
bool insertList(list *list, char* type,char* id,char* pwd){

	listNode *pnode;
	Account *pacc;
	char *tmp_type,*tmp_id,*tmp_pwd;

	if((pnode = (listNode*) malloc(sizeof(listNode))) == NULL){
		printf("can't malloc ListNode\n");
		exit(0);
	}
	
	if((pacc = (Account*) malloc(sizeof(Account))) == NULL){
		printf("can't malloc Account\n");
		exit(0);
	}
	if((tmp_type = (char*)malloc(sizeof(strlen(type)))) == NULL){
		printf("can't malloc type\n");
		exit(0);
	}
	if((tmp_id = (char*)malloc(sizeof(strlen(id)))) == NULL){
		printf("can't malloc id\n");
		exit(0);
	}
	if((tmp_pwd = (char*) malloc(sizeof(strlen(pwd)))) == NULL){
		printf("can't malloc pwd\n");
		exit(0);
	}
	
	strcpy(tmp_type,type);
	strcpy(tmp_id,id);
	strcpy(tmp_pwd,pwd);
	
	pacc->acc_type = tmp_type;
	pacc->acc_id   = tmp_id;
	pacc->acc_pwd  = tmp_pwd;

	pnode->value = pacc;
	
	if(list->len == 0){
		list->head = pnode;
		list->tail = pnode;
	}else{
		list->tail->next = pnode;
		pnode->prev = list->tail;
		pnode->next = NULL;
		list->tail = pnode;
	}

	list->len++;			

	return TRUE;	
}
bool listDelNode(list *list,listNode *node){
	
	listNode *cur_node;
	
	cur_node = node;
	if(node == list->head){
		
		list->head = list->head->next;
		list->head->prev = NULL;
		
	}else if(node == list->tail){
		
		list->tail = node->prev;
		list->tail = NULL;
	}else{

		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
			
	freeListNode(cur_node);
	list->len--;
	
	return TRUE;
}
void showListNode(listNode *node){

}

listNode *searchListByTypeAndID(list *list,char *type,char *id){
	listNode *cur_node;
	Account  *pac;
	int i;

	cur_node = list->head;
	for(i = 0;i < list->len;i++){
		pac = (Account*)cur_node->value;		
		if(strcmp(type,pac->acc_type) == 0 && strcmp(id,pac->acc_id) == 0){
			return cur_node;
		}
		cur_node = cur_node->next;
	}
	
	return NULL;

}
bool freeListNode(listNode *node){
	
	Account *pac;
	pac = (Account*)node->value;
	freeAccount(pac);
	free(node);	

	return TRUE;
}

bool freeAccount(Account *pac){
	
	free(pac->acc_type);
	free(pac->acc_id);
	free(pac->acc_pwd);

	free(pac);

	return TRUE;
}
