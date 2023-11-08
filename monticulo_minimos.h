//
// Created by drako on 8/11/23.
//

#ifndef ALGORITMOS_P3_MONTICULO_MINIMOS_H
#define ALGORITMOS_P3_MONTICULO_MINIMOS_H

typedef struct monticulo {
    int ultimo; 
    int *vector; 
}tMount; 

void crearMonticulo (int v[], int n, tMount M); 
int quitarMenor (tMount M);
void liberarMonticulo(tMount M);

#endif //ALGORITMOS_P3_MONTICULO_MINIMOS_H
