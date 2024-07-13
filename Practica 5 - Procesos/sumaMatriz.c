#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

void generarMatriz(int ***);
void leeMatricesArch(FILE *, int **, int **);
void suma(int **, int**);

int main(int argc, char *argv[]){

    int **matriz1, **matriz2;
    
    generarMatriz(&matriz1);
    generarMatriz(&matriz2);

    //Abrir el archivo de las matrices
    FILE *mat;
    mat=fopen("matrices.txt", "r");
    //Comprobar si se abrio correctamente
    if(mat==NULL){
        perror("No se pudo abrir el archivo de las matrices base desde sumaMatriz");
        exit(0);
    }
    //Llenar las matrices
    leeMatricesArch(mat, matriz1, matriz2);
    //Sumar las matrices y guardarlas en el archivo
    suma(matriz1, matriz2);
    //Terminar ejecucion
    fclose(mat);

    free(matriz1);
    free(matriz2);

    return 0;
}

void generarMatriz(int ***matriz){
    unsigned char i, j;
    
    *matriz = (int **)calloc(10, sizeof(int *));
    for(i = 0; i < 10; i++){
		(*matriz)[i] = (int *)calloc(10, sizeof(int));
	}
}

void suma(int **m1, int**m2){
    int i, j;
    FILE *arch;
    arch = fopen("sumaMat.txt", "w");
    if(arch==NULL){
        perror("No se pudo abrir el archivo archino para la suma");
        return;
    }

    //Hacer la suma y escribirla en el archivo
    for(i = 0; i < 10; i++){
        for(j = 0; j < 10; j++){
            fprintf(arch, "%d ", (m1[i][j] + m2[i][j]));
        }
        fprintf(arch, "\n");
    }
    fclose(arch);
}

void leeMatricesArch(FILE *mat, int **m1, int **m2){
    int i,j;
    //Leer la matriz 1
    for(i = 0; i < 10; i++){
        for(j = 0; j < 10; j++)
            fscanf(mat, "%d", &m1[i][j]);
    }
    fgetc(mat);
    //Leer la matriz 2
    for(i = 0; i < 10; i++){
        for(j = 0; j < 10; j++)
            fscanf(mat, "%d", &m2[i][j]);
    }
}