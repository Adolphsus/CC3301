#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "pss.h"

int main(int argc, char *argv[]) {
    if (argc != 4) { // Si recibimos mas o menos de cuatro parametros:
        fprintf(stderr, "%s\n", "Uso: ./definir <diccionario> <llave> <definicion>"); //indicamos la sintaxis a seguir para usar el diccionario
        return 1; // luego terminamos el programa
    }
    
    char *nom_dic = argv[1]; // declaramos el nombre del diccionario
    char *llave = argv[2];  // declaramos la llave que queremos ingresar
    char *def = argv[3];    //junto a su defincion
    int ancho = 81;         //usamos que el ancho es 81 (80 caracteres mas el salto de linea)
    
   //Abrimos el archivo en modo lectura y escritura: r+
    FILE *f = fopen(nom_dic, "r+");
    char buf[ancho]; //creamos un buffer
    
    if(f==NULL){ //Si el archivo es nulo
        perror(nom_dic); //diagnosticamos el error con perror, indicando que el archivo con el nombre dado no se encontro
        return 1;   //y terminamos el programa
    }

    fseek(f, 0, SEEK_END);  //colocamos el puntero al final del archivo
    int sizeFile = ftell(f); //y calculamos el tamano del archivo
    
    //Para elegir la linea:
    int numLines = sizeFile / (ancho); //sacamos el numero de lineas como el total del tamano del archivo dividido en el ancho de cada linea
    int numLineaEscribir = hash_string(llave) % numLines; //usamos la funcion de hash y le sacamos modulo numero de lineas 
    int contadorLineas = 0; //iniamos una variable para llevar la cuenta de cuantas lineas hemos visitado

    while(1){ //hacemos un loop infinito
        fseek(f, (ancho)*numLineaEscribir, SEEK_SET); //colocamos el puntero al inicio de la linea que nos da al hacer hash%modulo
        fread(buf, sizeof(char), ancho, f); //leemos esta linea y la almacenamos en el buffer
        contadorLineas++; //aumentamos el contador de lineas leidas en 1
        char *c = buf; //hacemos un puntero al buffer
        
        // para ver si escribir o no:
        if(*c == ' ') { // si el primer caracter de la linea esta desocupado (podemos escribir):
            fseek(f, (ancho)*numLineaEscribir, SEEK_SET); //r elocalizamos el puntero (hay que relocalizarlo, pues se mueve a la siguiente al usar fseek())
            fputs(llave, f); // escribimos la palabra
            fputc(':', f);   // escribimos el ':'
            fputs(def, f);   // escribimos su definicion
            fclose(f);       // cerramos el archivo para efectuar los cambios
            return 0;        // terminamos el programa de forma exitosa
        } else {        // si el primer caracter de la linea no estaba desocupado:
            int largopalabra = 0;   // iniciamos un contador
            char *aux1 = buf;       // hacemos un puntero al buffer
            while(*aux1 != ':') {   // mientras no nos encontremos con los ':'
                largopalabra++;     // aumentamos el largo de la palabra
                aux1++;             // y movemos el puntero hacia la derecha
            }
            
            if(strncmp(llave, buf, largopalabra) == 0){ // luego comparamos para ver si la palabra ya esta en el diccionario, si es que esta:
                fprintf(stderr, "%s %s %s\n", "La llave", llave, "ya se encuentra en el diccionario"); // printeamos que a llave ya esta en el diccionario
                return 1;           // terminamos el programa de forma no exitosa
            }
            
            if (contadorLineas == numLines) { //si el contador de lineas es igual al total (ya le revisamos todas las lineas y no habian espacios en blanco)
                fprintf(stderr, "%s%s %s\n", nom_dic, ":", "el diccionario esta lleno"); // printeamos que el diccionario esta lleno
                return 1; // terminamos el programa de forma no exitosa
            }
            
            numLineaEscribir = (hash_string(llave) % numLines)+contadorLineas; // si pasamos por todos los anteriores if, hay que seguir buscando una linea en donde escribir
                                                                               // por lo que sumamos el contador: (hash%modulo+contador), para asi seguir viendo en el archivo
        }
    }
}
