#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include "ordenacion_monticulos.h"
#include "monticulo_minimos.h"

#define TEST_LEN 10
#define MAX_LENGTH 256000
#define STARTING_LENGTH 500
#define UMBRAL_CONFIANZA 500
#define TIEMPO_MAXIMO 1000000
#define K 1000

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void show_array(int v[], int len) {
    int i;
    printf("\n");
    for (i = 0; i < len; ++i) {
       printf("%d  ", v[i]);
    }
    printf("\n");
}

double tiempo_test_ordenar_por_monticulos(int v[], int len, void fill_array(int[], int)) {
    //declarar variables
    double t, start, end;
    int i;

    //obtener tiempo en ejecutarse
    fill_array(v, len);
    start = microsegundos();
    ordenar_array_por_monticulos(v, len);
    end = microsegundos();
    t = end - start;

    //en caso de que sea menor al umbral de confianza repetirlo K veces
    if(t < UMBRAL_CONFIANZA) {
        //conseguir el tiempo de K iteraciones
        start = microsegundos();
        for (i = 0; i < K; i++) {
            fill_array(v, len);
            ordenar_array_por_monticulos(v, len);
        }
        end = microsegundos();
        t = end - start;

        //restarle el tiempo de K iteraciones de rellenar el array
        start = microsegundos();
        for (i = 0; i < K; i++)
            fill_array(v, len);
        end = microsegundos();
        t -= end - start;

        //dividir el tiempo entre K iteraciones e imprimir (*)
        t /= K;
        printf("(*)");
    }


    return t;
}

double tiempo_test_crear_monticulo(int v[], int len, void fill_array(int[], int)) {
    //declarar variables
    double t, start, end;
    int i;
    pmonticulo mont = malloc(sizeof(struct monticulo));

    //obtener tiempo en ejecutarse
    fill_array(v, len);
    start = microsegundos();
    crearMonticulo(v, len, mont);
    end = microsegundos();
    t = end - start;

    //en caso de que sea menor al umbral de confianza repetirlo K veces
    if(t < UMBRAL_CONFIANZA) {
        //conseguir el tiempo de K iteraciones
        start = microsegundos();
        for (i = 0; i < K; i++) {
            fill_array(v, len);
            ordenar_array_por_monticulos(v, len);
        }
        end = microsegundos();
        t = end - start;

        //restarle el tiempo de K iteraciones de rellenar el array
        start = microsegundos();
        for (i = 0; i < K; i++)
            fill_array(v, len);
        end = microsegundos();
        t -= end - start;

        //dividir el tiempo entre K iteraciones e imprimir (*)
        t /= K;
        printf("(*)");
    }

    free(mont);
    return t;
}


//Distintas cotas
double cota_On0_8 (int n){
    return pow(n, 0.8);
}

double cota_On1 (int n){
    return pow(n, 1);
}

double cota_On1_2 (int n){
    return pow(n, 1.2);
}

double cota_Onlogn (int n){
    return n * log(n);
}

double cota_On1_5 (int n){
    return pow(n, 1.5);
}

double cota_On1_8 (int n){
    return pow(n, 1.8);
}

double cota_On2 (int n){
    return pow(n, 2);
}

double cota_On2_2 (int n){
    return pow(n, 2.2);
}

void test (void fill_array(int[], int)) {
    int v[TEST_LEN];
    fill_array(v, TEST_LEN);
    show_array(v, TEST_LEN);
    printf("\nEs ordenado? %d", es_array_ordenado(v, TEST_LEN));
    printf("\n\n");
    ordenar_array_por_monticulos(v, TEST_LEN);
    show_array(v, TEST_LEN);
    printf("Es ordenado? %d", es_array_ordenado(v, TEST_LEN));
    printf("\n\n");
}


void escribir_tabla_generico(double cota_sub(int), double cota_normal(int), double cota_sobre(int),
                             void fill_array(int[], int), double tipo_test(int[], int, void fill_array(int[], int))) {
    //inicializar variables
    int v[MAX_LENGTH];
    int len;
    double t = 0;

    //hacer tabla
    for(len = STARTING_LENGTH; len <= MAX_LENGTH && t < TIEMPO_MAXIMO; len *= 2) {
        t = tipo_test(v, len, fill_array);
        printf("\t\t%7d\t\t%14.3lf\t\t%2.10lf\t\t%2.10lf\t\t%2.10lf\n", len, t, t / cota_sub(len), t / cota_normal(len), t / cota_sobre(len));
    }
}


int main(){
    printf("Test con vector ordenado ascendentemente\n");
    test(rellenar_array_ascendente);
    printf("Test con vector desordenado\n");
    test(rellenar_array_aleatorio);
    printf("Test con vector ordenado descendentemente\n");
    test(rellenar_array_descendente);


    printf("\n\nAlgoritmo -- Crear montículo");

    printf("\n\nCrear montículo con inicializacion ascendente:\n\n");
    printf("\t\tn\t\t\tt(n)\t\tt(n)/n^0.8\t\tt(n)/n^1\t\tt(n)/n^1.2\n");
    escribir_tabla_generico(cota_On0_8, cota_On1, cota_On1_2, rellenar_array_ascendente, tiempo_test_crear_monticulo);

    printf("\n\nCrear montículo con inicializacion desordenada:\n\n");
    printf("\t\tn\t\t\tt(n)\t\tt(n)/n^0.8\t\tt(n)/n^1\t\tt(n)/n^1.2\n");
    escribir_tabla_generico(cota_On0_8, cota_On1, cota_On1_2, rellenar_array_aleatorio, tiempo_test_crear_monticulo);

    printf("\n\nCrear montículo con inicializacion descendente:\n\n");
    printf("\t\tn\t\t\tt(n)\t\tt(n)/n^0.8\t\tt(n)/n^1\t\tt(n)/n^1.2\n");
    escribir_tabla_generico(cota_On0_8, cota_On1, cota_On1_2, rellenar_array_descendente, tiempo_test_crear_monticulo);

    printf("\n\n\nAlgoritmo -- Ordenacion por montículos");

    printf("\n\nOrdenacion por montículos con inicializacion ascendente:\n\n");
    printf("\t\tn\t\t\tt(n)\t\tt(n)/n\t\t\tt(n)/nlog(n)\t\tt(n)/n^1.5\n");
    escribir_tabla_generico(cota_On1, cota_Onlogn, cota_On1_5, rellenar_array_ascendente, tiempo_test_ordenar_por_monticulos);

    printf("\n\nOrdenacion por montículos con inicializacion desordenada:\n\n");
    printf("\t\tn\t\t\tt(n)\t\tt(n)/n\t\t\tt(n)/nlog(n)\t\tt(n)/n^1.5\n");
    escribir_tabla_generico(cota_On1, cota_Onlogn, cota_On1_5, rellenar_array_aleatorio, tiempo_test_ordenar_por_monticulos);

    printf("\n\nOrdenacion por montículos con inicializacion descendente:\n\n");
    printf("\t\tn\t\t\tt(n)\t\tt(n)/n\t\t\tt(n)/nlog(n)\t\tt(n)/n^1.5\n");
    escribir_tabla_generico(cota_On1, cota_Onlogn, cota_On1_5, rellenar_array_descendente, tiempo_test_ordenar_por_monticulos);

    printf("\n\n\n");

}
