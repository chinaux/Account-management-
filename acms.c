#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
int main(int argv,char **argc){
	
	char command;
	int flag;
	if(argv != 3){
		printf("Usage  :acms [user] [pwd]\n");
		printf("Example:acms root root\n");
		exit(0);
	}

	if(TRUE == login()){
		
		flag=TRUE;
		while(flag){
			printf(">");	
			command=getc(stdin);
			
			switch(command){
				case 'a':{
					addAccount();
					break;
				}
				case 'd':{
					deleteAccount();
					break;
				}
				case 'q':{
					quit();
					flag=FAIL;
					break;
				}
				case 's':{
					showAccount();
					break;
				}
				case 'x':{
					saveAndQuit();
					flag=FAIL;
					break;
				}
				case 'h':{
					help();
					break;
				}	
				default:
					break;

			}				
		}		
	}else{
		printf("you failed to login the account system\n");
	}
	
}
