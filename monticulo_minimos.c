#include "monticulo_minimos.h"
#define TAM 256000

// procedimiento privado de la libreria
// flota el elemento de un `nodo` del monticulo recalculando su posicion de acuerdo a la estructura de un monticulo
// de minimos
void flotar(pmont m, int i) {
    while (i > 1 && m->vector[i / 2] > m->vector[i]) {
        // intercambiar el nodo hijo con el nodo padre
        int temp = m->vector[i];
        m->vector[i] = m->vector[i / 2];
        m->vector[i / 2] = temp;
        i = i / 2;
    }
}

// procedimiento privado de la libreria
// calculo de indices de hijos
// pseudocodigo: hijo izquierdo: 2*i || C: 2*(i - 1) = 2*i - 2
// pseudocodigo: hijo derecho: 2*i + 1 || C: 2*(i - 1) + 1 = 2*i - 1
void hundir(pmont m, int i) {
    int hijo_izq, hijo_der, j;
    do {
        hijo_izq = 2 * i - 2;
        hijo_der = 2 * i - 1;
        j = i;

        if (hijo_der <= m->len && m->vector[hijo_der] < m->vector[i]) {
            i = hijo_der;
        }

        if (hijo_izq <= m->len && m->vector[hijo_izq] < m->vector[i]) {
            i = hijo_izq;
        }

        // Intercambiar el elemento actual con el hijo apropiado
        int temp = m->vector[j];
        m->vector[j] = m->vector[i];
        m->vector[i] = temp;
    } while (j != i);
}

// procedimiento publico de la libreria
// configura la estructura de un monticulo pasado por parametro creando un monticulo funcional y valido estructuralmente cuyos elementos
// son los del vector v de tamaño n pasado por parametro
void crearMonticulo(int v[], int n, pmont m) {
    // Copiar los elementos del vector v al vector_monticulo de la estructura pmont
    for (int i = 0; i < n; i++) {
        m->vector[i + 1] = v[i];
    }

    m->len = n;

    // Recolocar los elementos para que el montículo conserve su propiedad de montículo de mínimos
    // para esto la libreria utiliza la operacion hundir para recolocar elementos del vector del monticulo
    for (int i = n / 2; i > 0; i--) {
        hundir(m, i);
    }
}


// funcion publica de la libreria
int quitarMenor (pmont m) {
    int x = m->vector[0]; // por estructura especifica del monticulo el minimo (la raiz) esta ubicada en la posicion 0 del vector
    int i;
    for (i = m->len; i >= 0; i--) {
        hundir (m, i);
    }

    return x;  //  devuelve el minimo despues de guardarlo en x y eliminarlo del monticulo
}

