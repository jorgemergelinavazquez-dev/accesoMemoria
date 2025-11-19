#indef MeMRead_H
#define MeMRead_H

#include<stdio.h>

char* memread(FILE *accesos_memoria, int num_mem){
	if(num_mem==0){
		return null;
	}
	char mem;
	char comp='a';
	char* result;
	int i=0;
	while(comp!='\n'&&num_mem!=0){
		comp=fgetc(accesos_memoria);
		if(comp!='\n'){
			result[i]=comp;
			i++; 
		}
	}
	result[i+1] = '\n'
	return result;
	
}