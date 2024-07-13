#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

void generarMatriz(int ***);
void rellenarMatriz(int **);
void imprimirMatriz(int **);

void escribeMatrices(FILE *, int **, int **);

int main(int argc, char *argv[]){

    //Variables para la ejecucion de sub-procesos
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    //Variables para la lectura del tiempo
    clock_t tInicio, tFinal;
    float tCalculado;

    int **matriz1, **matriz2, **restSum, **restMult;

    srand(time(NULL));
    //printf("\n\t\t------------------- SUMA -------------------\n\n");
    printf("\n\t\t--------------MATRIZ 1 GENERADA--------------\n");
    generarMatriz(&matriz1);
    rellenarMatriz(matriz1);
    imprimirMatriz(matriz1);
    printf("\n\t\t--------------MATRIZ 2 GENERADA--------------\n");
    generarMatriz(&matriz2);
    rellenarMatriz(matriz2);
    imprimirMatriz(matriz2);

    //Guardamos las matrices en un archivo para su uso por los demás programas
    //Escribir las matrices en un archivo
    FILE *arch;
    arch = fopen("matrices.txt", "w");
    if(arch==NULL){
        perror("No se pudo abrir el archivo");
        exit(1);
    }
    escribeMatrices(arch, matriz1, matriz2);
    fclose(arch);

    //inicio del tiempo a medir
    tInicio=clock();

    //Crear el proceso de la suma
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    for(int i=0;i<6;i++){
        switch(i){
            case 0:
                if(!CreateProcess( "sumaMatriz.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)){
                    printf( "CreateProcess failed (%d).\n", GetLastError() );
                    return 1;
                }
                // Esperar a que exista el proceso hijo.
                WaitForSingleObject( pi.hProcess, INFINITE );
                // Cerrar procesos.
                CloseHandle( pi.hProcess );
                CloseHandle( pi.hThread );
            break;
            case 1:
                if(!CreateProcess( "restaMatriz.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)){
                    printf( "CreateProcess failed (%d).\n", GetLastError() );
                    //return 1;
                }
                // Esperar a que exista el proceso hijo.
                WaitForSingleObject( pi.hProcess, INFINITE );
                // Cerrar procesos.
                CloseHandle( pi.hProcess );
                CloseHandle( pi.hThread );
            break;
            case 2:
                if(!CreateProcess( "multMatriz.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi )){
                    printf( "CreateProcess failed (%d).\n", GetLastError() );
                    // return 1;
                }
                // Esperar a que exista el proceso hijo.
                WaitForSingleObject( pi.hProcess, INFINITE );
                // Cerrar procesos.
                CloseHandle( pi.hProcess );
                CloseHandle( pi.hThread );
            break;
            case 3:
                if(!CreateProcess( "transMatriz.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)){
                    printf( "CreateProcess failed (%d).\n", GetLastError() );
                    // return 1;
                }
                // Esperar a que exista el proceso hijo.
                WaitForSingleObject( pi.hProcess, INFINITE );
                // Cerrar procesos.
                CloseHandle( pi.hProcess );
                CloseHandle( pi.hThread );
            break;
            case 4:
                if(!CreateProcess( "invMatriz.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)){
                    printf( "CreateProcess failed (%d).\n", GetLastError() );
                    // return 1;
                }
                // Esperar a que exista el proceso hijo.
                WaitForSingleObject( pi.hProcess, INFINITE );
                // Cerrar procesos.
                CloseHandle( pi.hProcess );
                CloseHandle( pi.hThread );
            break;
            case 5:
                if(!CreateProcess( "lectMatriz.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)){
                    printf( "CreateProcess failed (%d).\n", GetLastError() );
                    // return 1;
                }
                // Esperar a que exista el proceso hijo.
                WaitForSingleObject( pi.hProcess, INFINITE );
                // Cerrar procesos.
                CloseHandle( pi.hProcess );
                CloseHandle( pi.hThread );
            break;
        }
    }

    //Fin del tiempo a medir
    tFinal=clock();

    tCalculado = (float)(tFinal - tInicio) / CLOCKS_PER_SEC;
    printf("\n\n\nTiempo de ejecucion: %.4f segs", tCalculado);

    free(matriz1);
    free(matriz2);

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