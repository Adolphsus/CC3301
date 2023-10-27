#include <stdio.h>

#include "suma.h"

Bcd sumaBcd(Bcd x, Bcd y) {
  Bcd mask = 0xf; // usamos la mascara con solo 1's
  Bcd correction = 0xa; // correcion que usaremos en caso de que la suma exceda a 10
  Bcd carry = 0x0; // partimos con el carry 0
  Bcd result = 0x0; // partimos con un resultado de cero al que iremos sumando cada digito
  for (int i = 0; i < 64; i+=4) { // recorremos el los digitos del numero (lo hacemos de 4 en 4 pues no podemos usar *)
    Bcd savex = mask&(x>>i); // guardaremos para x los cuatros digitos que representan una cifra (notese que se va moviendo conforme avanza el for)
    Bcd savey = mask&(y>>i); // idem para y
    Bcd sum = savex + savey + carry; // hacemos la suma de x e y (si hay carry producto de alguna iteracion anterior)
    if (sum > 9) { // si la suma es mayor a 9  
      sum -= correction; //restamos a 10 y nos quedamos solo con el digito
      carry = 0x1; // aumentamos en uno en carry (reserva)
    } else {
      carry = 0x0; // en caso contrario el carry es cero
    }
    result |= (sum<<i); // movemos la suma segun corresponda con el i
  }                     // y operamos con or (pues hasta ahora consiste en algo | 0 = algo )
  Bcd n = 0x1;
  if (carry == n) { // si quedo carry, es porque supero las 16 cifras
    return 0xffffffffffffffff; //entonces devolvemos lo pedido
  } else {
    return result; // en caso contrario retornamos el resultado
  }
}