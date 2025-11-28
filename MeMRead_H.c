#indef MeMRead_H
#define MeMRead_H
#include<stdio.h>
#include<stdlib.h>
typedef struct{
	unsigned char  ETQ;
	unsigned char Data[TAM_Linea];
}T_CACHE_LINE;
void ParsearDireccion(unsigned int addr, int *ETQ, int *palabra, int *linea, int *bloque){
	unsigned int comp=addr;
	comp &= 0xF80;
	*ETQ=comp;
	comp=addr;
	comp &= 0x070;
	*linea=comp;
	comp=addr;
	comp &= 0x00F;
	*palabra=comp;
	*bloque=addr/16;
}	
void LimpiarCache(T_CACHE_LINE tbl[NUM_FILAS]){
	for(int i=0;i<=NUM_FILAS){
		tbl[i].Data=NULL;
		tbl[i].ETQ=NULL;
	}
	
}
void VolcarCACHE(T_CACHE_LINE *tbl) {
		printf("T: %d, Acierto de CACHE, ADDR %04X Label %X linea %02X palabra %02X DATO %02X\n", globaltime, addr, etq, linea, palabra, Cache[linea].Data[palabra]);
		
}
void TratarFallo(T_CACHE_LINE *tbl, char *MRAM, int ETQ,
int linea, int bloque){
	if(tbl.ETQ!=ETQ){
		numfallos++;
		printf("T: %d, Fallo de CACHE %d, ADDR %04X Label %X linea %02X palabra %02X bloque %02X", globaltime, numfallos, addr,atoi(*tbl.ETQ), linea, atoi(*tbl.Data), bloque);
		globaltime+=20;
		parseardireccion(addr, ETQ,atoi(tbl.Data), linea, bloque);
		printf("cargando el bloque %02X en la linea %02X", bloque, linea);
		char newbloque[3];
		char newETQ[3];
		newbloque=itoa(bloque, hex, 16);
		newETQ=itoa(ETQ, hex, 16);
		*tbl.Data=newbloque;
		*tbl.ETQ=newETQ;
	}
}
#endif
