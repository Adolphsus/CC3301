#include <stddef.h>

#include "prev.h"

//Adolfo Arenas P.

void asignarPrev(Nodo *t, Nodo **pprev) { // t es el nodo en el que estamos y pprev es un puntero al puntero prev
  if(t != NULL){ // si el nodo t no es nulo
    asignarPrev(t->izq, pprev); // recorremos a la izquierda 
    t->prev = *pprev; // asignamos *pprev al nodo previo de t
    t->prox = NULL; // asignamos nulo al proximo
    if (t->prev != NULL) { // si el nodo previo a t no es nulo 
        t->prev->prox = t; // asignamos su nodo siguiente como t
    }   
    *pprev = t; // finalmente asignamos pprev a t
    asignarPrev(t->der, pprev); // y seguimos recorriendo hacia la derecha
   } 
 }

