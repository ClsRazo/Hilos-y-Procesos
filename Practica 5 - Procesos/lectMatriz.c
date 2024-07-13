#include <stdio.h>
#include <windows.h>

void leeMatricesArch(FILE *, int [][10], int [][10]);
void escribeMatrices(FILE *, int [][10], int [][10]);
void leeMatricesArchIndi(FILE *, int [][10]);
void escribeMatricesIndi(FILE *, int [][10]);
void escribeMatricesFloat(FILE *, float [][10], float [][10]);
void leeMatricesArchFloat(FILE *, float [][10], float [][10]);

int main(int argc, char *argv[]){
    int matPrueba1[10][10], matPrueba2[10][10];
    float matPrueba1F[10][10], matPrueba2F[10][10];

    //Leer las matrices base
    FILE *arch;

    //Leer la matriz suma
    arch = fopen("sumaMat.txt", "r");
    if(arch==NULL){
        perror("No se pudo abrir el archivo de la matriz suma desde lectura");
        exit(1);
    }
    printf("\n\t\t------------------- SUMA -------------------\n\n");
    leeMatricesArchIndi(arch, matPrueba1);
    escribeMatricesIndi(stdout, matPrueba1);
    fclose(arch);

    //Leer la matriz resta
    arch = fopen("restaMat.txt", "r");
    if(arch==NULL){
        perror("No se pudo abrir el archivo de la matriz resta desde lectura");
        exit(1);
    }
    printf("\n\t\t------------------- RESTA -------------------\n\n");
    leeMatricesArchIndi(arch, matPrueba1);
    escribeMatricesIndi(stdout, matPrueba1);
    fclose(arch);

    //Leer la matriz multiplicacion
    arch = fopen("multiMat.txt", "r");
    if(arch==NULL){
        perror("No se pudo abrir el archivo de la matriz multiplciacion desde lectura");
        exit(1);
    }
    printf("\n\t\t------------------- MULTIPLICACION -------------------\n\n");
    leeMatricesArchIndi(arch, matPrueba1);
    escribeMatricesIndi(stdout, matPrueba1);
    fclose(arch);

    //Leer las matrices transpuestas
    arch = fopen("transMat.txt", "r");
    if(arch==NULL){
        perror("No se pudo abrir el archivo de las matrices transpuestas desde lectura");
        exit(1);
    }
    printf("\n\t\t------------------- TRANSPUESTAS -------------------\n\n");
    leeMatricesArch(arch, matPrueba1, matPrueba2);
    escribeMatrices(stdout, matPrueba1, matPrueba2);
    fclose(arch);

    //Leer las matrices inversas
    arch = fopen("inverMat.txt", "r");
    if(arch==NULL){
        perror("No se pudo abrir el archivo de las matrices inversas desde lectura");
        exit(1);
    }
    printf("\n\t\t------------------- INVERSAS -------------------\n\n");
    leeMatricesArchFloat(arch, matPrueba1F, matPrueba2F);
    escribeMatricesFloat(stdout, matPrueba1F, matPrueba2F);
    fclose(arch);

    exit(0);
}

void leeMatricesArch(FILE *mat, int m1[][10], int m2[][10]){
    int i,j;
    //Leer la matriz 1
    for(i=0;i<10;i++){
        for(j=0;j<10;j++)
            fscanf(mat, "%d", &m1[i][j]);
    }
    fgetc(mat);
    //Leer la matriz 2
    for(i=0;i<10;i++){
        for(j=0;j<10;j++)
            fscanf(mat, "%d", &m2[i][j]);
    }
}

void escribeMatrices(FILE *sal, int m1[][10], int m2[][10]){
    int i,j;
    //Escribir la primer matriz
    for(i=0;i<10;i++){
        for(j=0;j<10;j++)
            fprintf(sal, "%d ", m1[i][j]);
        fprintf(sal, "\n");
    }
    fprintf(sal, "\n");
    //Escribir la segunda matriz
    for(i=0;i<10;i++){
        for(j=0;j<10;j++)
            fprintf(sal, "%d ", m2[i][j]);
        fprintf(sal, "\n");
    }
}

void leeMatricesArchIndi(FILE *mat, int m1[][10]){
    int i,j;
    //Leer la matriz 1
    for(i=0;i<10;i++){
        for(j=0;j<10;j++)
            fscanf(mat, "%d", &m1[i][j]);
    }
}

void escribeMatricesIndi(FILE *sal, int m1[][10]){
    int i,j;
    //Escribir la primer matriz
    for(i=0;i<10;i++){
        for(j=0;j<10;j++)
            fprintf(sal, "%d ", m1[i][j]);
        fprintf(sal, "\n");
    }
    fprintf(sal, "\n");
}

void escribeMatricesFloat(FILE *sal, float m1[][10], float m2[][10]){
    int i,j;
    //Escribir la primer matriz
    for(i=0;i<10;i++){
        for(j=0;j<10;j++)
            fprintf(sal, "%.3f ", m1[i][j]);
        fprintf(sal, "\n");
    }
    fprintf(sal, "\n");
    //Escribir la segunda matriz
    for(i=0;i<10;i++){
        for(j=0;j<10;j++)
            fprintf(sal, "%.3f ", m2[i][j]);
        fprintf(sal, "\n");
    }
}

void leeMatricesArchFloat(FILE *mat, float m1[][10], float m2[][10]){
    int i,j;
    //Leer la matriz 1
    for(i=0;i<10;i++){
        for(j=0;j<10;j++)
            fscanf(mat, "%f", &m1[i][j]);
    }
    fgetc(mat);
    //Leer la matriz 2
    for(i=0;i<10;i++){
        for(j=0;j<10;j++)
            fscanf(mat, "%f", &m2[i][j]);
    }
}
