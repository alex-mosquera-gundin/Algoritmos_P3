#ifndef ALGORITMOS_P3_MONTICULO_MINIMOS_H
#define ALGORITMOS_P3_MONTICULO_MINIMOS_H
#define TAM 256000

struct monticulo {
    int ultimo;
    int vector[TAM];
};

typedef struct monticulo * pmonticulo;

// cabecera de funciones publicas de la libreria de monticulo_minimos.h
void crearMonticulo (int v[], int n, pmonticulo m);
int quitarMenor (pmonticulo m);

#endif //ALGORITMOS_P3_MONTICULO_MINIMOS_H
