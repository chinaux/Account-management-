#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "menu.h"
#include "list.h"
#define TYPE_SIZE 8
#define   ID_SIZE 16
#define  PWD_SIZE 16
bool help(){

    printf("usage:\n");
    printf("\ta: addAccount\n");
    printf("\ts: showAllAccount\n");
    printf("\td: deleteAccount\n");
    printf("\tq: quit without save\n");
    printf("\tx: quit and save\n");
    printf("\th: help\n");
    
    return TRUE;
}
bool login(){
    char usr[10];
    char pwd[10];
    
    printf("user:");
    scanf("%s",usr);
    printf("pwd :");
    scanf("%s",pwd);
    
    if(strcmp(usr,"root") == 0 && strcmp(pwd,"root") == 0){
        initList(&gl_list);
        help();
        return TRUE;
    }else{
        return FAIL;
    }
}
bool addAccount(){

    char acc_type[TYPE_SIZE];
    char acc_id[ID_SIZE];
    char acc_pwd[PWD_SIZE];
    /*here is  a big bug ,if user input beyand the array size ,program will be crashed.
        is there any way to avoid this problem?
    */
    printf("your acc_type:");
    scanf("%s",acc_type);
    printf("your acc_id:");
    scanf("%s",acc_id);
    printf("your acc_pwd:");
    scanf("%s",acc_pwd);
    
    if(TRUE == insertList(&gl_list,acc_type,acc_id,acc_pwd)){
        printf("Congratulation!\nYour new account has been insert into database successfully\n");
        return TRUE;
    }else{
        printf("Sorry!\nI failed to insert your new account into database\n");
        return FAIL;
    }
}
bool showAccount(){
    int i;
    Account *cur_paccount;
    listNode *cur_node;

    cur_node = gl_list.head;
    
    for(i = 0;i < gl_list.len;i++){
        cur_paccount = cur_node->value;
        if(cur_paccount != NULL){
            printf("type:%-10s  id:%-10s pwd:%-10s\n",cur_paccount->acc_type,\
                    cur_paccount->acc_id,cur_paccount->acc_pwd);
        }
        cur_node=cur_node->next;
    }
}
bool deleteAccount(){
    
    char acc_type[TYPE_SIZE];
    char acc_id[ID_SIZE];
    listNode *node;

    printf("your acc_type:");
    scanf("%s",acc_type);
    printf("your acc_id:");
    scanf("%s",acc_id);
    
    if((node = searchListByTypeAndID(&gl_list,acc_type,acc_id)) == NULL){

        printf("can't find the account\n");
        exit(0);
    }   
    
    if(TRUE == listDelNode(&gl_list,node)){
        
        printf("SUCCESSFULLY!\nthe account has been delete\n");
        return TRUE;
    }else{

        printf("SORRY!\nwe fail to delete the account!\n");
        return FAIL;
    }

}
bool quit(){
    
    int i;
    Account *cur_paccount;
    listNode *cur_node,*next_node;

    cur_node = gl_list.head;
    
    for(i = 0;i < gl_list.len;i++){
        next_node = cur_node->next;
        freeListNode(cur_node);
        cur_node = next_node;
    }
}
bool saveAndQuit(){
    
    FILE *pf;
    int i;
    Account *cur_paccount;
    listNode *cur_node;

    if((pf = fopen(DATA_FILE,"w")) == NULL){
        printf("can't open %s",DATA_FILE);
        exit(0);
    }
    
    cur_node = gl_list.head;
    
    for(i = 0;i < gl_list.len;i++){
        cur_paccount = cur_node->value;
        if(cur_paccount != NULL){
            fprintf(pf,"%s:%s:%s\n",cur_paccount->acc_type,\
                    cur_paccount->acc_id,cur_paccount->acc_pwd);
        }
        cur_node=cur_node->next;
    }
    
    fclose(pf);
        
    quit();
}
