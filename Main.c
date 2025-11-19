////////LIBRERIAS////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

////////STRUCT////////
typedef struct {
	unsigned char ETQ;
	unsigned char Data[TAM_LINEA];
} T_CACHE_LINE
////////VARIABLES_GLOBALES////////
int globaltime=0;
int numfallos=0;
unsigned char Simul_RAM[4096];

////////INICIALIZACION_FUNCIONES////////
void LimpiarCACHE(T_CACHE_LINE tbl[NUM_FILAS]);
void VolcarCACHE(T_CACHE_LINE *tbl);
void ParsearDireccion(unsigned int addr, int *ETQ, int *palabra, int *linea, int *bloque);
void TratarFallo(T_CACHE_LINE *tbl, char *MRAM, int ETQ, int linea, int bloque);
////////MAIN////////
int main(){
	
	if((*FILE fd = fopen("/*FicheroQueSea.txt*/","r"))==NULL){
		printf("El fichero no existe");
		return -1;
	}
	
	fclose(fd);
}

////////FUNCIONES////////
void TratarFallo(T_CACHE_LINE *tbl, char *MRAM, int ETQ, int linea, int bloque){
	
	printf("T: %d, Fallo de cahce, addr %04X etq %X linea %02X palabra %02X bloque %02X",*tbl,*MRAM,ETQ,linea,/*falta la palabra*/,bloque);
	
}
