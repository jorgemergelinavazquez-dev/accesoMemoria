#indef MeMRead_H
#define MeMRead_H

#include<stdio.h>
#include<stdlib.h>
char* memread(FILE *accesos_memoria, int num_mem){
	if(num_mem==0){
		return null;
	}
	char mem;
	char comp='a';
	char* result=(char*)malloc(1 * sizeof(char));
	int i=0;
	while(comp!='\n'&&num_mem!=0){
		comp=fgetc(accesos_memoria);
		if(comp!='\n'){
			result[i]=comp;
			i++;
			result=(char*)realloc(result, i * sizeof(char));
		}
	}
	result[i+1] = '\n'
	return result;
	
}	

typedef struct{
	unsigned char  ETQ;
	unsigned char Data[TAM_Linea];
}T_CACHE_LINE;

char* GetBinary(unsigned char NUM){
	int num = (int)NUM;
	int i=4;
	char binary[i];
	if(num>='0' && num<='9'){
		num-='0';
	}
	else if(num>='A' && num<='F'){
		num-=55;
	}
	else{
		printf("Error, no se ha dado una direccion de memoria correcta");
		return NULL;
	}
	while(num>0){
		binary[--i] =(decimal_num%2) + '0';
		decimal_num /= 2;
	}
	return binary;
}
void TratarFallo(T_CACHE_LINE *tbl, char *MRAM, int ETQ,
int linea, int bloque){
	
	
	
}
