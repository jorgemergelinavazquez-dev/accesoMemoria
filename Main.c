////////LIBRERIAS////////
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

////////DEFINES////////
#define TAM_LINEA 16
#define NUM_FILAS 8
#define TAM_RAM 4096

// MOVIDO AQUI: El include debe ir DESPUES de los defines
#include "MeMRead_Corregido.h"

////////NOMBRES DE FICHEROS////////
char* ContRam = "CONTENTS_RAM.bin";
char* AcsMem= "accesos_memoria.txt"; 
char* DirMem= "dirs_memoria.txt";
char* ContCach = "CONTENTS_CACHE.bin";

////////VARIABLES_GLOBALES////////
int globaltime = 0;//inicializamos a 0 las variables para evitar fallos inesperados
int numfallos = 0; 
T_CACHE_LINE Cache[NUM_FILAS];
char texto[100];
int accesos = 0;
unsigned int addr;

////////MAIN////////
int main() {
    FILE* fd; // faltaba ;
	FILE* fd2;
    int ETQ, x, linea, bloque, palabra; // faltaba palabra
	unsigned char MRAM[TAM_RAM];	

    LimpiarCACHE(Cache);//borramos la basura que hay en la cache

    if ((fd = fopen(ContRam, "rb")) == NULL) {//if para verificar que existe el fichero, rb = read bin,no crea el fichero si no existe
        printf("Error al abrir CONTENTS_RAM.bin\n");
        return 1;
    }
    fread(MRAM, 1, TAM_RAM, fd);//leemos el fichero, fread->CHATGPT
	//fread(Array donde guarda las cosas, tamaño de cada elemento, cuantos elementos hay q leer, que fichero hay q leer)
    fclose(fd);//lo cerramos
    
	if ((fd = fopen(AcsMem, "r")) == NULL) {//compruebo q existen, r = read,no crea el fichero si no existe
        // printf("Error al abrir accesos_memoria.txt\n") // Faltaba ;
        // Logica corregida: si falla uno, prueba el otro
        if ((fd = fopen(DirMem, "r")) == NULL) {
            printf("Error al abrir dirs_memoria.txt\n");
            return 1;
        }
    }
    // fd2 no se usaba correctamente, usamos fd para el bucle

	while (fscanf(fd, "%x", &addr) != EOF) {
        addr &= 0xFFF;// mascara->CHATGPT
        accesos++;
        
        ParsearDireccion(addr, &ETQ, &palabra, &linea, &bloque);

        // Llamada corregida y logica movida aqui para evitar duplicados en funcion
        if (Cache[linea].ETQ != ETQ) {
             numfallos++;
             printf("T: %d, Fallo de CACHE %d, ADDR %04X Label %X linea %02X palabra %02X bloque %02X\n", globaltime, numfallos, addr, ETQ, linea, palabra, bloque);
             globaltime += 20;
             printf("Cargando bloque %02X en la linea %02X\n", bloque, linea);
             TratarFallo(Cache, MRAM, ETQ, linea, bloque); // faltaba ;
        }

        printf("T: %d, Acierto de CACHE, ADDR %04X Label %X linea %02X palabra %02X DATO %02X\n", globaltime, addr, ETQ, linea, palabra, Cache[linea].Data[palabra]);
        
        if (strlen(texto) < 99) {
            int len = strlen(texto);
            // Aseguramos que es un caracter imprimible o lo guardamos igual
            texto[len] = Cache[linea].Data[palabra];
            texto[len + 1] = '\0';//para cerrar frases
        }
        VolcarCACHE(Cache);
        sleep(1);
    }
    fclose(fd);
	// fclose(fd2); // fd2 podia no estar abierto

    printf("\nAccesos totales: %d", accesos);
    printf("\nNumero de fallos: %d", numfallos);
    printf("\nTiempo medio de acceso: %.2f", (float)globaltime / accesos);//float para que no de fallo por dividir por decimal, CHATGPT SOLUCION
    printf("\nTexto leido: %s\n", texto);

    if ((fd = fopen(ContCach, "wb")) == NULL) {
        printf("Error al crear CONTENTS_CACHE.bin");
        return 1;
    }
    for (int i = 0; i < NUM_FILAS; i++)
        fwrite(Cache[i].Data, 1, TAM_LINEA, fd);//escrivimos el fichero, fwrite->CHATGPT
		//fwrite(Array de donde saca las cosas, tamaño de cada elemento, cuantos elementos hay q escribir, en q archivo hay q escribir)
    
    fclose(fd);
    return 0;
}
