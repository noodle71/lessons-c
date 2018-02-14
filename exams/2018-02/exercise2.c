/*
 * DESCRIPTION:
 * Escribir un programa completo para calcular el porcentaje de disparos con éxito 
 * de un jugador de baloncesto. 
 *
 * El programa main() leerá desde el teclado el número de disparos y el jugador 
 * disparará dicho número de veces. El jugador siempre estará en la misma 
 * posición (a una distancia de META metros). 
 *
 * En cada lanzamiento (en un bucle), se lee de teclado la velocidad inicial y el 
 * ángulo (no validar estos datos). Para determinar si ha encestado o no, el 
 * programa main() llamará a una función Lanzar(), que devolverá 1 si acierta y 0 si no.
 * En main(), el programa contará el número de veces que el jugador anota una canasta. 
 * Al final, el programa calculará y mostrará en la pantalla el porcentaje 
 * de los disparos con éxito.
 *
 * Función: int Lanzar(float v0, float ang);
 * Esta función calculará el resultado de un lanzamiento. 
 * La función recibirá la velocidad inicial y el ángulo y calculará la altura 'y' a la que 
 * el balón impacta en la posición X=META. Definir META como una constante (4.6), y G 
 * como una constante (9.8). La ecuación para calcular el valor de y es:
 *
 * y = META * tan(ang) - ((G * META²)/(2 * v0² * (cos(ang))²))
 *
 * Si el valor de y está entre dos constantes Y-ARRIBA (3.5) y Y_ABAJO (2.9), 
 * la función devolverá 1, si no, la función devolverá 0. 
 *
 * NOTA: Se puede usar las funciones tan(ang) y cos(ang) para calcular 
 * tangente y coseno de un ángulo. Añadir la librería math.h.
 */

#include <stdio.h>
#include <math.h>
#define META 4.6
#define G 9.8
#define Y_ARRIBA 3.5
#define Y_ABAJO 2.9

int Lanzar(float v0, float ang);

int main(void){
  int intentos;
  int i;
  int total_encestado = 0;
  float v0;
  float ang;
  float estadisticas;

  printf("\nIntroduce el número de intentos para encestar en la canasta: ");
  scanf("%d", &intentos);

  for(i = 1; i <= intentos; i++){
    printf("\n\nIntento número %d\tCanastas encestadas: %d", i, total_encestado);
    printf("\nIntroduce velocidad: ");
    scanf("%f", &v0);
    printf("\nIntroduce angulo: ");
    scanf("%f", &ang);
    total_encestado += Lanzar(v0, ang);
  }

  if(intentos > 0){
    estadisticas = (total_encestado * 100) / intentos;
    printf("\nDe un total de %d intentos, se han acertado %d veces.", intentos, total_encestado);
    printf("\nPorcentaje de acierto: %.3f \n", estadisticas); 
  }
}

int Lanzar(float v0, float ang){
  int encesta = 0;
  float numerator;
  float denominator;
  float term_indep;
  float y;
  numerator = G * pow(META, 2);
  denominator = 2 * pow(v0, 2) * pow(cos(ang), 2);
  term_indep = META * tan(ang);
  y = term_indep - (numerator / denominator);
  if(y >= Y_ABAJO && y <= Y_ARRIBA){
    encesta = 1;
  }
  return encesta;
}
