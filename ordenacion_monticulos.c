#include "ordenacion_monticulos.h"
#include "monticulo_minimos.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// Rellena el array de forma aleatoria
void rellenar_array_aleatorio(int array[], int len) {
    srand(time(NULL));

    for (int i = 0; i < len; i++) {
        array[i] = (rand() % (2 * len)) - len;
    }
}

// Rellena el array de forma ascendente
void rellenar_array_ascendente(int array[], int len) {
    for (int i = 0; i < len; i++) {
        array[i] = i + 1;
    }
}

// Rellena el array de forma descendente
void rellenar_array_descendente(int array[], int len) {
    for (int i = 0; i < len; i++) {
        array[i] = len - i;
    }
}

// Ordena el array por medio de montículos
void ordenar_array_por_monticulos(int array[], int len) {
    // Crear montículo
    pmonticulo mont = (pmonticulo)malloc(sizeof(struct monticulo));

    if (mont == NULL) {
        perror("Error al asignar memoria para el montículo");
        exit(EXIT_FAILURE);
    }

    // Inicializar el montículo
    mont->ultimo = 0;

    // Crear montículo
    crearMonticulo(array, len, mont);

    // Rellenar el vector
    for (int i = 0; i < len; i++) {
        array[i] = quitarMenor(mont);
    }

    // Liberar memoria del montículo
    free(mont);
}

// Devuelve un 1 si el array está ordenado y un 0 si no
int es_array_ordenado(int array[], int len) {
    int cond = 1, i = 1;

    while (i < len && cond) {
        if (array[i - 1] > array[i])
            cond = 0;
        i++;
    }

    return cond;
}

