#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include "ordenacion_monticulos.h"
#include "monticulo_minimos.h"

#define TEST_LEN 250
#define MAX_LENGTH 256000
#define STARTING_LENGTH 500
#define UMBRAL_CONFIANZA 500
#define K 1000
#define TIEMPO_MAXIMO 1000000

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

//la data son los argumentos de las funciones a cronometrar y el orden es 0 si el setup va antes de la función y 1 si va después
double tiempo_test_generico(void funcion_de_setup(void *),void funcion_a_cronometrar(void *), void funcion_de_final(void *), void *data){
    //declarar variables
    double t, start, end;
    int i;

    //obtener tiempo en ejecutarse
    funcion_de_setup(data);

    start = microsegundos();
    funcion_a_cronometrar(data);
    end = microsegundos();

    funcion_de_final(data);

    t = end - start;

    //en caso de que sea menor al umbral de confianza repetirlo K veces
    if(t < UMBRAL_CONFIANZA) {
        //conseguir el tiempo de K iteraciones
        start = microsegundos();
        for (i = 0; i < K; i++) {
            funcion_de_setup(data);

            funcion_a_cronometrar(data);

            funcion_de_final(data);
        }
        end = microsegundos();
        t = end - start;

        //restarle el tiempo de K iteraciones de rellenar el array
        start = microsegundos();
        for (i = 0; i < K; i++) {
            funcion_de_setup(data);
            funcion_de_final(data);
        }
        end = microsegundos();
        t -= end - start;

        //dividir el tiempo entre K iteraciones e imprimir (*)
        t /= K;
        printf("(*)");
    }


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

//next_data sirve para que devuelva la longitud actual y actualize los tados para las funciones
void escribir_tabla_generico(double cota_sub(int), double cota_normal(int), double cota_sobre(int),
                             void funcion_de_setup(void *), void funcion_a_cronometrar(void *), void funcion_de_final(void *),
                             int inicializar_data(void *), int next_data(void *), void liberar_data(void *),void *data){


    //inicializar variables
    int len;
    double t;

    //hacer tabla
    len = inicializar_data(data);
    do{
        t = tiempo_test_generico(funcion_de_setup, funcion_a_cronometrar, funcion_de_final, data);
        printf("\t\t%7d\t\t%14.3lf\t\t%2.10lf\t\t%2.10lf\t\t%2.10lf\n", len, t, t / cota_sub(len), t / cota_normal(len), t / cota_sobre(len));
        len = next_data(data);
    } while (t < TIEMPO_MAXIMO && len != -1);
    liberar_data(data);
}

void funct_vacia(void *pointer){};


//datos para medir la creación por montículos
typedef struct datos_crear_monticulos {
    int vector[MAX_LENGTH];
    int len;
    void (*function)(int vector[], int len);
    pmonticulo mont;
} datos_crear_monticulos;

int inicializar_crear_monticulos(void *pointer) {
    datos_crear_monticulos *data = pointer;
    data->len = STARTING_LENGTH;
    data->mont = malloc(sizeof(pmonticulo));
    return data->len;
}

int next_crear_monticulos(void *pointer) {
    datos_crear_monticulos *data = pointer;
    data->len *= 2;

    if (data->len > MAX_LENGTH)
        return -1;

    return data->len;
}

void funct_asignar_mont(void *pointer){
    datos_crear_monticulos *data = pointer;
    data->function(data->vector, data->len);
}

void funct_crear_mont(void *pointer) {
    datos_crear_monticulos *data = pointer;
    crearMonticulo(data->vector, data->len, data->mont);
}



//datos para medir la ordenación por montículos
typedef struct datos_ordenar_monticulos{
    int vector[MAX_LENGTH];
    int len;
} * datos_ordenar_monticulos;

int inicializar_ordenar_monticulos(datos_ordenar_monticulos data){
    data->len = STARTING_LENGTH;
    return data->len;
}

int next_ordenar_monticulos(datos_ordenar_monticulos data){
    data->len *= 2;

    if(data->len > MAX_LENGTH)
        return -1;

    return data->len;
}

void funct_ordenar_monticulos(datos_ordenar_monticulos data){
    ordenar_array_por_monticulos(data->vector, data->len);
}

void funct_rellenar_vector(void rellenar_array(int vector[], int len), datos_ordenar_monticulos data){
    rellenar_array(data->vector, data->len);
}


int main(){
    //primera sección dedicada al test
    printf("test:\n");
    int v[TEST_LEN];
    datos_crear_monticulos data;

    rellenar_array_aleatorio(v, TEST_LEN);
    show_array(v, TEST_LEN);
    printf("\nEs ordenado? %d", es_array_ordenado(v, TEST_LEN));
    printf("\n\n");

    ordenar_array_por_monticulos(v, TEST_LEN);

    show_array(v, TEST_LEN);
    printf("\nEs ordenado? %d", es_array_ordenado(v, TEST_LEN));



    //segunda sección dedicada a las tablas
    printf("\ntesting imprimir tablas\n");
    data.function = rellenar_array_ascendente;
    escribir_tabla_generico(cota_On0_8, cota_On1, cota_On1_2,
                            funct_asignar_mont, funct_crear_mont, funct_vacia,
                            inicializar_crear_monticulos, next_crear_monticulos, free, &data);
}
