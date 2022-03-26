#include "pila.h"
#include "testing.h"
#include <stdio.h>

/* Pruebas para crear una pila vacia */
static void prueba_pila_vacia(void) {
    printf("INICIO DE PRUEBAS CON PILA VACIA\n");

    /* Declaro las variables a utilizar*/
    pila_t* pila = pila_crear();

    /* Inicio de pruebas */
    print_test("crear pila funciona", pila != NULL);
    print_test("la pila efectivamente esta vacia", pila_esta_vacia(pila) == true);
    print_test("si esta vacia, pila_ver_tope es invalido", pila_ver_tope(pila) == NULL);
    print_test("pila_desapilar es invalido si la pila esta vacia", pila_desapilar(pila) == NULL);  


    /* Destruyo la pila*/
    pila_destruir(pila);
}

/* Pruebas para apilar NULL */
static void prueba_pila_apilar_null(void) {
    printf("INICIO DE PRUEBAS PARA APILAR NULL \n");

    /* Declaro las variables a utilizar*/
    pila_t* pila = pila_crear();

    /* Inicio de pruebas */
    print_test("crear pila funciona", pila != NULL);
    print_test("la pila efectivamente esta vacia", pila_esta_vacia(pila) == true);
    print_test("pila_apilar con NULL es valido", pila_apilar(pila, NULL) == true);
    print_test("la pila no esta vacia", pila_esta_vacia(pila) == false);
    print_test("si la operacion anterior de apilar fue efectiva, pila_ver_tope tiene que dar NULL", pila_ver_tope(pila) == NULL);


    /* Destruyo la pila*/
    pila_destruir(pila);
}

/* Pruebas para operatoria de pilas con pocos valores*/
static void prueba_pila_operaciones(void) {
    printf("INICIO DE PRUEBAS CON PILA CON POCOS VALORES\n");

    /* Declaro las variables a utilizar*/
    pila_t* pila = pila_crear();

    /* Inicio de pruebas */
    int a[] = {1,2};
    int i, *p[2];
    for (i = 0; i < 2; i++) {
        p[i] = &a[i];
    }

    print_test("la pila efectivamente apila", pila_apilar(pila, p[0]) == true);
    print_test("el tope de la pila es el valor que apile", pila_ver_tope(pila) == &a[0]);        
    print_test("pila_esta_vacia da false, entonces efectivamente apila", pila_esta_vacia(pila) == false);
    print_test("la pila efectivamente apila", pila_apilar(pila, p[1]) == true);
    print_test("el tope de la pila es el valor que apile", pila_ver_tope(pila) == &a[1]);  
    print_test("la pila efectivamente desapila", pila_desapilar(pila) == &a[1]);    
    print_test("el tope de la pila es el valor que apile inicialmente", pila_ver_tope(pila) == &a[0]);
    print_test("la pila efectivamente desapila", pila_desapilar(pila) == &a[0]);        

    /* Destruyo la pila*/
    pila_destruir(pila);
}

/* Pruebas para ver comportamiendo de la pila para llenado y vaciado*/
static void prueba_pila_comportamiento(void) {
    printf("INICIO DE PRUEBAS DE COMPORTAMIENTO EN LLENADO Y VACIADO DE PILA\n");

    /* Declaro las variables a utilizar*/
    pila_t* pila = pila_crear();

    /* Inicio de pruebas */
    int a[] = {1,2};
    int i, *p[2];
    for (i = 0; i < 2; i++) {
        p[i] = &a[i];
    }

    print_test("la pila efectivamente apila", pila_apilar(pila, p[0]) == true);        
    print_test("la pila efectivamente apila", pila_apilar(pila, p[1]) == true);
    print_test("la pila efectivamente desapila", pila_desapilar(pila) == &a[1]);    
    print_test("la pila efectivamente desapila", pila_desapilar(pila) == &a[0]);          

    print_test("si esta vacia, pila_ver_tope es invalido", pila_ver_tope(pila) == NULL);
    print_test("si esta vacia, pila_desapilar es invalido", pila_desapilar(pila) == NULL);

    /* Destruyo la pila*/
    pila_destruir(pila);
}

/* Pruebas de volumen */
static void prueba_pila_volumen(void) {
    printf("INICIO DE PRUEBAS DE VOLUMEN\n");

    /* Declaro las variables a utilizar*/
    pila_t* pila = pila_crear();

    /* Inicio de pruebas */
    int vol_max = 1000;
    int arr_val[vol_max], *arr_p[vol_max];
    bool condicion_test_volumen_apilar = true;
    bool condicion_test_volumen_desapilar = true;

    for (int i = 0; i < vol_max; i++) {
        arr_val[i] = i;                                                                     //ciclo para crear un vector de volumen
        arr_p[i] = &arr_val[i];
        if ((pila_apilar(pila, arr_p[i]) != true) || (pila_ver_tope(pila) != &arr_val[i])){
            condicion_test_volumen_apilar = false;
            break;
        }
    }

    print_test("la pila efectivamente apilo 1000 valores", condicion_test_volumen_apilar == true);

    for (int k = vol_max - 1 ; k >= 0; k--) {

        if (k == 0) {                                                                               //caso cuando desapilo el ultimo elemento
            if ((pila_desapilar(pila) == NULL) || (pila_esta_vacia(pila) != true)) condicion_test_volumen_desapilar = false;
            break;
        }

        int nuevo_tope = k - 1;                                                                 
        if ((pila_desapilar(pila) == NULL) || (pila_ver_tope(pila) != &arr_val[nuevo_tope])){       //caso general
            condicion_test_volumen_desapilar = false;
            break;
        }
    }


    print_test("la pila efectivamente desapilo 1000 valores", condicion_test_volumen_desapilar == true);

    /* Destruyo la pila*/
    pila_destruir(pila);
}



void pruebas_pila_estudiante() {
    prueba_pila_vacia();
    prueba_pila_apilar_null();
    prueba_pila_operaciones();
    prueba_pila_comportamiento();
    prueba_pila_volumen();

}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
