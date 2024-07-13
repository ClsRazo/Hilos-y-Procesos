#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

void generarMatriz1(int ***);
void generarMatriz2(float ***);
void leeMatricesArch(FILE *, int **, int **);
void inversa(int **, int**);
void escribeMatricesFloat(FILE *, float **, float **);

int main(int argc, char *argv[]){

    int **matriz1, **matriz2;

    generarMatriz1(&matriz1);
    generarMatriz1(&matriz2);

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
    //Inversa de las matrices y guardarlas en el archivo
    inversa(matriz1, matriz2);
    //Terminar ejecucion
    fclose(mat);

    free(matriz1);
    free(matriz2);

    return 0;
}

void generarMatriz2(float ***matriz){
    unsigned char i, j;
    
    *matriz = (float **)calloc(10, sizeof(float *));
    for(i = 0; i < 10; i++){
		(*matriz)[i] = (float *)calloc(10, sizeof(float));
	}
}

void generarMatriz1(int ***matriz){
    unsigned char i, j;
    
    *matriz = (int **)calloc(10, sizeof(int *));
    for(i = 0; i < 10; i++){
		(*matriz)[i] = (int *)calloc(10, sizeof(int));
	}
}

void inversa(int **m1, int**m2){
    int i,j,k;
    float **mIden1, **mIden2; //Matrices identidad
    float factor; //Factor de escala
    generarMatriz2(&mIden1);
    generarMatriz2(&mIden2);

    FILE *dest;
    dest = fopen("inverMat.txt", "w");
    if(dest==NULL){
        perror("No se pudo abrir el archivo destino para la transpuesta");
        return;
    }

    // Inicializar matriz identidad para la matriz 1 y 2
    for(i=0;i<10;i++) {
        for(j=0;j<10;j++){
            mIden1[i][j] = (i == j) ? 1.0 : 0.0;
            mIden2[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Gauss-Jordan para la matriz 1
    for (k=0;k<10;k++) {
        factor = m1[k][k];
        for (j=0;j<10;j++) {
            m1[k][j] /= factor;
            mIden1[k][j] /= factor;
        }
        for (i=0;i<10;i++) {
            if (i!=k) {
                factor = m1[i][k];
                for(j=0;j<10;j++) {
                    m1[i][j] -= factor * m1[k][j];
                    mIden1[i][j] -= factor * mIden1[k][j];
                }
            }
        }
    }

    // Gauss-Jordan para la matriz 2
    for (k=0;k<10;k++) {
        factor = m2[k][k];
        for (j=0;j<10;j++) {
            m2[k][j] /= factor;
            mIden2[k][j] /= factor;
        }
        for (i=0;i<10;i++) {
            if (i!=k) {
                factor = m2[i][k];
                for(j=0;j<10;j++) {
                    m2[i][j] -= factor * m2[k][j];
                    mIden2[i][j] -= factor * mIden2[k][j];
                }
            }
        }
    }

    //Escribir las matrices en el archivo
    escribeMatricesFloat(dest, mIden1, mIden2);

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

void escribeMatricesFloat(FILE *arch, float **m1, float **m2){
    int i,j;
    //Escribir la primer matriz
    for(i=0;i<10;i++){
        for(j=0;j<10;j++)
            fprintf(arch, "%.3f ", m1[i][j]);
        fprintf(arch, "\n");
    }
    fprintf(arch, "\n");
    //Escribir la segunda matriz
    for(i=0;i<10;i++){
        for(j=0;j<10;j++)
            fprintf(arch, "%.3f ", m2[i][j]);
        fprintf(arch, "\n");
    }
}