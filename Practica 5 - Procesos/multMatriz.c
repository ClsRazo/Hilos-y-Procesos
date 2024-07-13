#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

void generarMatriz(int ***);
void leeMatricesArch(FILE *, int **, int **);
void multiplicacion(int **, int**);

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
    //Multiplicar las matrices y guardarlas en el archivo
    multiplicacion(matriz1, matriz2);
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

void multiplicacion(int **m1, int**m2){
    int i,j,k;
    int **mMult;
    generarMatriz(&mMult);
    FILE *dest;
    dest = fopen("multiMat.txt", "w");
    if(dest==NULL){
        perror("No se pudo abrir el archivo destino para la multiplicacion");
        return;
    }

    //Hacer la multiplicacion y escribirla en el archivo
    for(i=0;i<10;i++) {
        for(j=0;j<10;j++) {
            mMult[i][j] = 0;
            for(k=0;k<10;k++) {
                mMult[i][j] += m1[i][k] * m2[k][j];
            }
            fprintf(dest, "%d ", mMult[i][j]);
        }
        fprintf(dest, "\n");
    }

    fclose(dest);
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