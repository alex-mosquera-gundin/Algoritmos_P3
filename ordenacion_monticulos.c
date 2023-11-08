#include "ordenacion_monticulos.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//rellena el array de forma aleatoria
void rellenar_array_aleatorio(int array[], int len){
    int i;

    //inicializar semilla
    srand(time(NULL));

    //rellenar con numeros aleatorios enre len y - len
    for(i = 0; i < len; i++)
        array[i] =(rand() % (2 * len)) - len;
}

//rellena el array de forma ascendente
void rellenar_array_ascendente(int array[], int len){
    int i;
    for(i = 0; i < len; i++)
        array[i] = i + 1;
}

//rellena el array de forma descendente
void rellenar_array_descendente(int array[], int len){
    int i;
    for(i = 0; i < len; i++)
        array[i] = len - i;
}

//ordena el array por medio de monticulos
void ordenar_array_por_monticulos(int array[], int len){

}

//devuelve un 1 si el array está ordenado y un 0 si no
int es_array_ordenado(int array[], int len){
    int cond = 1, i;
    for(i = 1; i < len && cond; i++)
        if(array[i-1] > array[i])
            cond = 0;

    return cond;
}