////////LIBRERIAS////////
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<MeMRead_H>


////////DEFINES////////
#define TAM_LINEA 16
#define NUM_FILAS 8
#define TAM_RAM 4096

////////STRUCT////////
typedef struct {
    unsigned char ETQ;
    unsigned char Data[TAM_LINEA];
} T_CACHE_LINE;

////////NOMBRES DE FICHEROS////////
char 

////////VARIABLES_GLOBALES////////
int globaltime = 0;//inicializamos a 0 las variables para evitar fallos inesperados
int numfallos = 0;
unsigned char Simul_RAM[TAM_RAM];
T_CACHE_LINE Cache[NUM_FILAS];
char texto[100];

////////INICIALIZACION_FUNCIONES////////
void LimpiarCACHE(T_CACHE_LINE tbl[NUM_FILAS]);
void VolcarCACHE(T_CACHE_LINE *tbl);
void ParsearDireccion(unsigned int addr, int *ETQ, int *palabra, int *linea, int *bloque);
void TratarFallo(T_CACHE_LINE *tbl, unsigned char *MRAM, int ETQ, int linea, int bloque);

////////MAIN////////
int main() {
    FILE* fd;
    unsigned int addr;
    int etq, palabra, linea, bloque;//estas no son necesarias ya que despues se le asignaran valores
    int accesos = 0;

    LimpiarCACHE(Cache);//borramos la basura que hay en la cache

    if ((fd = fopen("CONTENTS_RAM.bin", "rb")) == NULL) {//if para verificar que existe el fichero, rb = read bin,no crea el fichero si no existe
        printf("Error al abrir CONTENTS_RAM.bin\n");
        return 1;
    }
    fread(Simul_RAM, 1, TAM_RAM, fd);//leemos el fichero, fread->CHATGPT
	//fread(Array donde guarda las cosas, tamaño de cada elemento, cuantos elementos hay q leer, que archivo hay q leer)
    fclose(fd);//lo cerramos
    if ((fd = fopen("accesos_memoria.txt", "r")) == NULL) {//compruebo q existen, r = read,no crea el fichero si no existe
        printf("Error al abrir accesos_memoria.txt\n")
		return 1;
    }
	if ((fd = fopen("dirs_memoria.txt", "r")) == NULL) {
            printf("Error al abrir dirs_memoria.txt\n");
            return 1;
    }

    printf("\nAccesos totales: %d", accesos);
    printf("\nNumero de fallos: %d", numfallos);
    printf("\nTiempo medio de acceso: %.2f", (float)globaltime / accesos);//float para que no de fallo por dividir por decimal, CHATGPT SOLUCION
    printf("\nTexto leido: %s\n", texto);

    if ((fd = fopen("CONTENTS_CACHE.bin", "wb")) == NULL) {
        printf("Error al crear CONTENTS_CACHE.bin");
        return 1;
    }
    for (int i = 0; i < NUM_FILAS; i++) {
        fwrite(Cache[i].Data, 1, TAM_LINEA, fd);//escrivimos el fichero, fwrite->CHATGPT
    }
    fclose(fd);
    return 0;
}

////////FUNCIONES////////

void LimpiarCACHE(T_CACHE_LINE tbl[NUM_FILAS]) {
}
void ParsearDireccion(unsigned int addr, int *ETQ, int *palabra, int *linea, int *bloque) {
}
void TratarFallo(T_CACHE_LINE *tbl, unsigned char *MRAM, int ETQ, int linea, int bloque) {
}
void VolcarCACHE(T_CACHE_LINE *tbl) {
}
