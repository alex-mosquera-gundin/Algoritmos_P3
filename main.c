#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define MAX_LENGTH 256000
#define STARTING_LENGTH 500
#define UMBRAL_CONFIANZA 500
#define K 1000

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

double tiempo_test_generico(void funcion_ordenacion(int[], int), int vector[], int len, void fill_array(int[], int)){
    //declarar variables
    double t, start, end;
    int i;

    //obtener tiempo en ejecutarse
    fill_array(vector, len);
    start = microsegundos();
    funcion_ordenacion(vector, len);
    end = microsegundos();
    t = end - start;

    //en caso de que sea menor al umbral de confianza repetirlo K veces
    if(t < UMBRAL_CONFIANZA) {
        //conseguir el tiempo de K iteraciones
        start = microsegundos();
        for (i = 0; i < K; i++) {
            fill_array(vector, len);
            funcion_ordenacion(vector, len);
        }
        end = microsegundos();
        t = end - start;

        //restarle el tiempo de K iteraciones de rellenar el array
        start = microsegundos();
        for (i = 0; i < K; i++)
            fill_array(vector, len);
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


void escribir_tabla_generico(double cota_sub(int), double cota_normal(int), double cota_sobre(int), 
                             void funcion_ordenacion(int[], int), void fill_array(int[], int)) {
    //inicializar variables
    int v[MAX_LENGTH];
    int len;
    double t;

    //hacer tabla
    for(len = STARTING_LENGTH; len <= MAX_LENGTH; len *= 2) {
        t = tiempo_test_generico(funcion_ordenacion, v, len, fill_array);
        printf("\t\t%7d\t\t%14.3lf\t\t%2.10lf\t\t%2.10lf\t\t%2.10lf\n", len, t, t / cota_sub(len), t / cota_normal(len), t / cota_sobre(len));
    }
}


int main(){
    printf("test");
}
