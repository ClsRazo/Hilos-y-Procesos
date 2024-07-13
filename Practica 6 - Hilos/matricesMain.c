#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

void generarMatriz(int ***);
void rellenarMatriz(int **);
void imprimirMatriz(int **);
void escribeMatrices(FILE *, int **, int **);
void escribeMatricesFloat(FILE *, float **, float **);
void leeMatricesArchIndi(FILE *, int **);
void escribeMatricesIndi(FILE *, int **);
void leeMatricesArchFloat(FILE *, float **, float **);
void generarMatriz2(float ***);
void leeMatricesArch(FILE *, int **, int **);

DWORD WINAPI sumaMatriz(LPVOID lpParam);
DWORD WINAPI restaMatriz(LPVOID lpParam);
DWORD WINAPI multMatriz(LPVOID lpParam);
DWORD WINAPI transMatriz(LPVOID lpParam);
DWORD WINAPI inverMatriz(LPVOID lpParam);
DWORD WINAPI lectMatriz(LPVOID lpParam);

typedef struct Matrices matri;
struct Matrices{
    int **mi1;
    int **mi2;
    float **mf1;
    float **mf2;
};

int main(int argc, char *argv[]){
    
    //Variables para los hilos
    DWORD idHilo;
    HANDLE manHilo;
    //Variables para la lectura del tiempo
    clock_t tInicio, tFinal;
    float tCalculado;

    matri m;

    srand(time(NULL));
    printf("\n\t\t--------------MATRIZ 1 GENERADA--------------\n");
    generarMatriz(&m.mi1);
    rellenarMatriz(m.mi1);
    imprimirMatriz(m.mi1);
    printf("\n\t\t--------------MATRIZ 2 GENERADA--------------\n");
    generarMatriz(&m.mi2);
    rellenarMatriz(m.mi2);
    imprimirMatriz(m.mi2);

    //Escribir las matrices en un archivo
    FILE *arch;
    arch = fopen("matrices.txt", "w");
    if(arch==NULL){
        perror("No se pudo abrir el archivo");
        exit(1);
    }
    escribeMatrices(arch, m.mi1, m.mi2);
    fclose(arch);

    //inicio del tiempo a medir
    tInicio=clock();
    
    for(int i=0;i<6;i++){
        switch(i){
            case 0:
                manHilo = CreateThread(NULL, 0, sumaMatriz, &m, 0, &idHilo);
                // Esperar a que exista el proceso hijo.
                WaitForSingleObject( manHilo, INFINITE );
                // Cerrar procesos.
                CloseHandle( manHilo );
            break;
            case 1:
                manHilo = CreateThread(NULL, 0, restaMatriz, &m, 0, &idHilo);
                // Esperar a que exista el proceso hijo.
                WaitForSingleObject( manHilo, INFINITE );
                // Cerrar procesos.
                CloseHandle( manHilo );
            break;
            case 2:
                manHilo = CreateThread(NULL, 0, multMatriz, &m, 0, &idHilo);
                // Esperar a que exista el proceso hijo.
                WaitForSingleObject( manHilo, INFINITE );
                // Cerrar procesos.
                CloseHandle( manHilo );
            break;
            case 3:
                manHilo = CreateThread(NULL, 0, transMatriz, &m, 0, &idHilo);
                // Esperar a que exista el proceso hijo.
                WaitForSingleObject( manHilo, INFINITE );
                // Cerrar procesos.
                CloseHandle( manHilo );
            break;
            case 4:
                manHilo = CreateThread(NULL, 0, inverMatriz, &m, 0, &idHilo);
                // Esperar a que exista el proceso hijo.
                WaitForSingleObject( manHilo, INFINITE );
                // Cerrar procesos.
                CloseHandle( manHilo );
            break;
            case 5:
                manHilo = CreateThread(NULL, 0, lectMatriz, &m, 0, &idHilo);
                // Esperar a que exista el proceso hijo.
                WaitForSingleObject( manHilo, INFINITE );
                // Cerrar procesos.
                CloseHandle( manHilo );
            break;
        }
    }

    //Fin del tiempo a medir
    tFinal=clock();

    tCalculado = (float)(tFinal - tInicio) / CLOCKS_PER_SEC;
    printf("\n\n\nTiempo de ejecucion: %.4f segs", tCalculado);

    free(m.mi2);
    free(m.mi1);

    return 0;
}

void generarMatriz(int ***matriz){
    unsigned char i, j;
    
    *matriz = (int **)malloc(10*sizeof(int *));
    for(i = 0; i < 10; i++){
		(*matriz)[i] = (int *)malloc(10*sizeof(int));
	}
}

void rellenarMatriz(int **matriz){
    unsigned char i, j;

    for(i = 0; i < 10; i++){
        for(j = 0; j < 10; j++){
            matriz[i][j] = rand() % 9;
        }
    }
}

void imprimirMatriz(int **matriz){
    unsigned char i, j;
    
    for(i = 0; i < 10; i++){
        printf("\n");
        for(j = 0; j < 10; j++){
            printf("%d   ",matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void escribeMatrices(FILE *arch, int **m1, int **m2){
    int i,j;
    //Escribir la primer matriz
    for(i=0;i<10;i++){
        for(j=0;j<10;j++)
            fprintf(arch, "%d ", m1[i][j]);
        fprintf(arch, "\n");
    }
    fprintf(arch, "\n");
    //Escribir la segunda matriz
    for(i=0;i<10;i++){
        for(j=0;j<10;j++)
            fprintf(arch, "%d ", m2[i][j]);
        fprintf(arch, "\n");
    }
}

void escribeMatricesFloat(FILE *sal, float **m1, float **m2){
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

void generarMatriz2(float ***matriz){
    unsigned char i, j;
    
    *matriz = (float **)calloc(10, sizeof(float *));
    for(i = 0; i < 10; i++){
		(*matriz)[i] = (float *)calloc(10, sizeof(float));
	}
}

void leeMatricesArch(FILE *mat, int **m1, int **m2){
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

void leeMatricesArchIndi(FILE *mat, int **m1){
    int i,j;
    //Leer la matriz 1
    for(i=0;i<10;i++){
        for(j=0;j<10;j++)
            fscanf(mat, "%d", &m1[i][j]);
    }
}

void escribeMatricesIndi(FILE *sal, int **m1){
    int i,j;
    //Escribir la primer matriz
    for(i=0;i<10;i++){
        for(j=0;j<10;j++)
            fprintf(sal, "%d ", m1[i][j]);
        fprintf(sal, "\n");
    }
    fprintf(sal, "\n");
}

void leeMatricesArchFloat(FILE *mat, float **m1, float **m2){
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

DWORD WINAPI sumaMatriz(LPVOID lpParam){
    matri *mats = (matri *)lpParam;

    int i, j;
    FILE *arch;
    arch = fopen("sumaMat.txt", "w");
    if(arch==NULL){
        perror("No se pudo abrir el archivo archino para la suma");
        return 1;
    }

    //Hacer la suma y escribirla en el archivo
    for(i = 0; i < 10; i++){
        for(j = 0; j < 10; j++){
            fprintf(arch, "%d ", (mats->mi1[i][j] + mats->mi2[i][j]));
        }
        fprintf(arch, "\n");
    }
    fclose(arch);
    return 0;
}

DWORD WINAPI restaMatriz(LPVOID lpParam){
    matri *mats = (matri *)lpParam;

    int i,j;
    FILE *dest;
    dest = fopen("restaMat.txt", "w");
    if(dest==NULL){
        perror("No se pudo abrir el archivo destino para la resta");
        return 1;
    }

    //Hacer la resta y escribirla en el archivo
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            fprintf(dest, "%d ", (mats->mi1[i][j] - mats->mi2[i][j]));
        }
        fprintf(dest, "\n");
    }
    fclose(dest);
    return 0;
}

DWORD WINAPI multMatriz(LPVOID lpParam){
    matri *mats = (matri *)lpParam;

    int i,j,k;
    int **mMult;
    generarMatriz(&mMult);
    FILE *dest;
    dest = fopen("multiMat.txt", "w");
    if(dest==NULL){
        perror("No se pudo abrir el archivo destino para la multiplicacion");
        return 1;
    }

    //Hacer la multiplicacion y escribirla en el archivo
    for(i=0;i<10;i++) {
        for(j=0;j<10;j++) {
            mMult[i][j] = 0;
            for(k=0;k<10;k++) {
                mMult[i][j] += mats->mi1[i][k] * mats->mi2[k][j];
            }
            fprintf(dest, "%d ", mMult[i][j]);
        }
        fprintf(dest, "\n");
    }

    fclose(dest);
    return 0;
}

DWORD WINAPI transMatriz(LPVOID lpParam){
    matri *mats = (matri *)lpParam;

    int i,j,k;
    int **mTrans1, **mTrans2;
    generarMatriz(&mTrans1);
    generarMatriz(&mTrans2);
    FILE *dest;
    dest = fopen("transMat.txt", "w");
    if(dest==NULL){
        perror("No se pudo abrir el archivo destino para la transpuesta");
        return 1;
    }

    //Hacer la transpuesta de la matriz 1
    for(i=0;i<10;i++) {
        for(j=0;j<10;j++)
            mTrans1[j][i] = mats->mi1[i][j];
    }

    //Hacer la transpuesta de la matriz 2
    for(i=0;i<10;i++) {
        for(j=0;j<10;j++)
            mTrans2[j][i] = mats->mi2[i][j];
    }

    //Escribir las matrices en el archivo
    escribeMatrices(dest, mTrans1, mTrans2);

    fclose(dest);
    return 0;
}

DWORD WINAPI inverMatriz(LPVOID lpParam){
    matri *mats = (matri *)lpParam;

    int i,j,k;
    float **mIden1, **mIden2; //Matrices identidad
    float factor; //Factor de escala
    generarMatriz2(&mIden1);
    generarMatriz2(&mIden2);

    FILE *dest;
    dest = fopen("inverMat.txt", "w");
    if(dest==NULL){
        perror("No se pudo abrir el archivo destino para la transpuesta");
        return 1;
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
        factor = (float)mats->mi1[k][k];
        for (j=0;j<10;j++) {
            mats->mi1[k][j] /= factor;
            mIden1[k][j] /= factor;
        }
        for (i=0;i<10;i++) {
            if (i!=k) {
                factor = mats->mi1[i][k];
                for(j=0;j<10;j++) {
                    mats->mi1[i][j] -= factor * mats->mi1[k][j];
                    mIden1[i][j] -= factor * mIden1[k][j];
                }
            }
        }
    }

    // Gauss-Jordan para la matriz 2
    for (k=0;k<10;k++) {
        factor = (float)mats->mi2[k][k];
        for (j=0;j<10;j++) {
            mats->mi2[k][j] /= factor;
            mIden2[k][j] /= factor;
        }
        for (i=0;i<10;i++) {
            if (i!=k) {
                factor = mats->mi2[i][k];
                for(j=0;j<10;j++) {
                    mats->mi2[i][j] -= factor * mats->mi2[k][j];
                    mIden2[i][j] -= factor * mIden2[k][j];
                }
            }
        }
    }

    //Escribir las matrices en el archivo
    escribeMatricesFloat(dest, mIden1, mIden2);

    fclose(dest);
    return 0;
}

DWORD WINAPI lectMatriz(LPVOID lpParam){
    matri *mats = (matri *)lpParam;

    int **matPrueba1, **matPrueba2;
    float **matPrueba1F, **matPrueba2F;

    generarMatriz(&matPrueba1);
    generarMatriz(&matPrueba2);
    generarMatriz2(&matPrueba1F);
    generarMatriz2(&matPrueba2F);

    //Leer las matrices base
    FILE *arch;

    //Leer la matriz suma
    arch = fopen("sumaMat.txt", "r");
    if(arch==NULL){
        perror("No se pudo abrir el archivo de la matriz suma desde lectura");
        return 1;
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

    return 0;
}