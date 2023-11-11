#ifndef ALGORITMOS_P3_MONTICULO_MINIMOS_H
#define ALGORITMOS_P3_MONTICULO_MINIMOS_H
#define TAM 256000

typedef struct monticulo {
    int ultimo;
    int vector[TAM];
}*pmonticulo;


// cabecera de funciones publicas de la libreria de monticulo_minimos.h

//crea un montículo a partir del vector y la longitud dada y se lo asigna al puntero dado
void crearMonticulo (int v[], int len, pmonticulo m);

//quita y devuelve el último elemento del montículo
int quitarMenor (pmonticulo m);

#endif //ALGORITMOS_P3_MONTICULO_MINIMOS_H
