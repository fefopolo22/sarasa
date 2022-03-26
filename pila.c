#include "pila.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#define INIT_CANT 0
#define MIN_CAP 12
#define FACTOR_REDIMENSION 2
#define COND_ACHICAMIENTO 4


/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};


/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...

pila_t* pila_crear(void) {

    pila_t* pila = malloc(sizeof(pila_t));

    if (pila == NULL) return NULL;

    pila->datos = malloc(MIN_CAP * sizeof(void*));

    if (pila->datos == NULL) {
        free(pila);
        return NULL;
    }
    
    pila->cantidad = INIT_CANT;
    pila->capacidad = MIN_CAP;
    return pila;
}

void pila_destruir(pila_t *pila) {

    free(pila->datos);                                                //Liberacion de toda la memoria que ocupan los datos
    free(pila);                                                       //Liberacion de memoria que ocupa estructura
}

bool pila_redimension(pila_t *pila, size_t nueva_capacidad) {

    void** datos_nuevo = realloc(pila->datos, nueva_capacidad * sizeof(void*));
    
    if (datos_nuevo == NULL) return false;
    
    pila->datos = datos_nuevo;
    pila->capacidad = nueva_capacidad;
    return true;
}

bool pila_esta_vacia(const pila_t* pila) {

    return !pila->cantidad;
}


bool pila_apilar(pila_t* pila, void* valor) {
    
    if (pila->cantidad == pila->capacidad) {

        if (pila_redimension(pila, pila->capacidad * FACTOR_REDIMENSION) == false) return false;
    }

    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    return true;

}

void* pila_ver_tope(const pila_t* pila) {

    if (pila_esta_vacia(pila)) return NULL;
    return pila->datos[pila->cantidad - 1];    
}

void* pila_desapilar(pila_t* pila) {

    if (pila_esta_vacia(pila)) return NULL;

    pila->cantidad--;

    if ((pila->cantidad * COND_ACHICAMIENTO <= pila->capacidad) && pila->capacidad > MIN_CAP) {
        pila_redimension(pila, pila->capacidad / FACTOR_REDIMENSION);
    }

    return pila->datos[pila->cantidad];
}
