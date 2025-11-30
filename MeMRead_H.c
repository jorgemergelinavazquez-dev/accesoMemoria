#ifndef MeMRead_H
#define MeMRead_H
#include<stdio.h>
#include<stdlib.h>

// Necesario para que la librería vea las variables del Main
extern int globaltime;
extern int numfallos;
extern unsigned int addr;
extern int accesos;

// STRUCT
typedef struct{
	unsigned char ETQ;
	unsigned char Data[TAM_LINEA]; // Corregido TAM_Linea -> TAM_LINEA
} T_CACHE_LINE;

// FUNCIONES
void ParsearDireccion(unsigned int addr, int *ETQ, int *palabra, int *linea, int *bloque){
	unsigned int comp=addr;
	comp &= 0xF80;
	*ETQ = comp >> 7; // Añadido desplazamiento
	comp=addr;
	comp &= 0x070;
	*linea = comp >> 4; // Añadido desplazamiento
	comp=addr;
	comp &= 0x00F;
	*palabra=comp;
	*bloque=addr/16;
}	

void LimpiarCACHE(T_CACHE_LINE tbl[NUM_FILAS]){
	for(int i=0; i<NUM_FILAS; i++){
		tbl[i].ETQ = 0xFF;
        for(int j=0; j<TAM_LINEA; j++) {
		    tbl[i].Data[j] = 0x23; // No se puede asignar NULL a un char
        }
	}
}

void VolcarCACHE(T_CACHE_LINE *tbl) {
    // Imprimimos la linea actual para depurar
    // Nota: Como no tenemos 'linea' ni 'palabra' aqui como argumentos, 
    // lo ideal seria pasar esos datos o imprimir toda la tabla.
    // He corregido el acceso para que no falle al compilar.
    printf("--- Volcado de Cache ---\n");
    for(int i=0; i<NUM_FILAS; i++) {
        printf("Linea %d ETQ %X: ", i, tbl[i].ETQ);
        for(int j=0; j<TAM_LINEA; j++) printf("%02X ", tbl[i].Data[j]);
        printf("\n");
    }
}

void TratarFallo(T_CACHE_LINE *tbl, unsigned char *MRAM, int ETQ, int linea, int bloque){
    // Corregida la lógica de punteros y tipos
	if(tbl[linea].ETQ != ETQ){
        // numfallos y globaltime se gestionan en el main segun tu codigo, 
        // pero aqui hacemos la copia fisica de datos.
		int dir_base = bloque * TAM_LINEA;
        for(int i=0; i<TAM_LINEA; i++) {
            tbl[linea].Data[i] = MRAM[dir_base + i];
        }
		tbl[linea].ETQ = ETQ;
	}
}
#endif
