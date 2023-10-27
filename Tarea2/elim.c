#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "elim.h"

void eliminar(char *str, char *pat) {
  char *aux = str; // creo un puntero al inicio de la palabra
  int lenpat = strlen(pat); // tomo ahora el largo de la palabra (hacerlo despues me llevo a un sobrecosto)
  while (*aux) {  // mientras la palabra no se acabe
    if (*aux == *pat && strncmp(aux, pat, lenpat) == 0) { // aplico un "filtro" para ver si la primera letra coincide con el patron, si es asi veo si hay coincidiencia con el patron con strncmp, si no vamos directamente al else y asi evitamos comparar innecesariamente
        aux = aux + lenpat; // si es asi me salto esta parte
    } else {  // si no es asi
      *str++ = *aux++; // hago que el contenido de la palabra sea igual al contenido del apuntado por el puntero (aqui modificamos el str) y avanzo los punteros
    }
  }
  *str = '\0'; // al final corto desde donde termino el puntero del str
}

char *eliminados(char *str, char *pat) {
    int count = 0; //iniciamos un contador
    int lenpat = strlen(pat);
    int lenstr = strlen(str);
    char *aux = str; // creo un puntero al inicio de la palabra
    while (*aux) {  // mientras la palabra no se acabe
        if (*aux == *pat && strncmp(aux, pat, lenpat) == 0) { // aplico un "filtro" para ver si la primera letra coincide con el patron, si es asi veo si hay coincidiencia con el patron con strncmp, si no vamos directamente al else y asi evitamos comparar innecesariamente
            aux += lenpat; // si es asi me salto esta parte
        } else {  // si no es asi
            count++; // aumento el contador (esto nos dara el largo de nuestra solucion)
            aux++; // hago que el contenido de la palabra sea igual al contenido del apuntado por el puntero
        }   
    }
    char *copy = malloc(lenstr+1); // creamos un espacio en memoria del tamano de nuestro str+1
    strcpy(copy, str); // copiamos nuestro string
    eliminar(copy, pat); // usamos eliminar en la copia
    char *solution = malloc(count+1); // creamos un espacio en memoria del tamano de nuestro contador+1 (todas las letras que no coinciden con el patron mas un espacio para el 0)
    strcpy(solution, copy); // copiamos lo resultado en copia en solucion (para asi usar el tamano justo)
    free(copy); // liberamos la copia
    return solution; // retornamos la solucion
}
