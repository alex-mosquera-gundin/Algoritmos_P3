#ifndef ALGORITMOS_P3_MONTICULO_MINIMOS_H
#define ALGORITMOS_P3_MONTICULO_MINIMOS_H
#define TAM 256000


// estructura de un monticulo de minimos
// mont_len : tamaño del vector del monticulo
// vector[] : conjunto de `nodos` del monticulo recogidos en un vector de enteros
struct monticulo {
    int len;
    int vector[TAM];
};

// definicion de tipo de monticulo
typedef struct monticulo * pmont;

// cabecera de funciones publicas de la libreria de monticulo_minimos.h
void crearMonticulo (int v[], int n, pmont m);
int quitarMenor (pmont m);

#endif //ALGORITMOS_P3_MONTICULO_MINIMOS_H
