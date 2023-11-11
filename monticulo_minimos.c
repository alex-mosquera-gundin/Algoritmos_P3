#include <stdio.h>
#include <stdlib.h>
#include "monticulo_minimos.h"
#define TAM 256000


void hundir(pmonticulo m, int i) {
    int hijo_izq, hijo_der, j;
    do {
        hijo_izq = 2 * i - 1;
        hijo_der = 2 * i;

        j = i;

        if (hijo_der <= m->ultimo && m->vector[hijo_der] < m->vector[i]) {
            i = hijo_der;
        }

        if (hijo_izq <= m->ultimo && m->vector[hijo_izq] < m->vector[i]) {
            i = hijo_izq;
        }

        // Intercambiar el elemento actual con el hijo apropiado
        if (j != i) {
            int temp = m->vector[j];
            m->vector[j] = m->vector[i];
            m->vector[i] = temp;
        }
    } while (j != i);
}

// Procedimiento privado para flotar el elemento en la posición i
void flotar(pmonticulo m, int i) {
    while (i > 1 && m->vector[i / 2] > m->vector[i]) {
        // Intercambiar el nodo hijo con el nodo padre
        int temp = m->vector[i];
        m->vector[i] = m->vector[i / 2];
        m->vector[i / 2] = temp;
        i = i / 2;
    }
}

void crearMonticulo(int v[], int n, pmonticulo m) {
    m->ultimo = n;

    // Copiar los elementos del array al vector del montículo
    for (int i = 1; i <= n; i++) {
        m->vector[i] = v[i - 1];
    }

    // Aplicar la operación hundir para mantener la propiedad de montículo
    for (int i = n / 2; i > 0; i--) {
        hundir(m, i);
    }
}

// Función pública para quitar el menor elemento del montículo y devolverlo
int quitarMenor(pmonticulo m) {
    if (m->ultimo < 1) {
        fprintf(stderr, "Montículo vacío. No existen elementos\n");
        exit(EXIT_FAILURE);
    }

    int menor = m->vector[1];

    // Intercambiar el primer elemento con el último
    m->vector[1] = m->vector[m->ultimo];
    m->ultimo--;

    // Aplicar la operación hundir para mantener la propiedad de montículo
    hundir(m, 1);

    return menor;
}









