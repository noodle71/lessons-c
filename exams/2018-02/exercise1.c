/*
 * AUTHOR: Angel Fernández Camba
 * DESCRIPTION:
 * Se ha de escribir el código de un programa completo que simula el funcionamiento 
 * de la apertura de una caja de seguridad mediante la introducción de una clave.
 * La clave de apertura de la caja de seguridad está definida con una constante 
 * simbólica (añadir #define CLAVE …… con el valor que queráis).
 * El usuario de la caja de seguridad para proceder a su apertura va a ir 
 * introduciendo dígitos de uno en uno, de manera que el programa debe ir leyendo 
 * cada uno de esos dígitos e ir construyendo el supuesto valor de la clave. No se sabe el 
 * número de dígitos de la clave por lo que el usuario introducirá el valor -1 para 
 * indicar que ya ha terminado de introducir dígitos. Es necesario validar cada uno de 
 * los dígitos introducidos.
 *
 * Por ejemplo, si el usuario introduce los siguientes dígitos:
 * 2 3 1 6 8 -1
 * el supuesto valor de la clave es: 23168
 * Una vez que se tiene el supuesto valor de la clave, se le muestra al usuario el 
 * valor indicando también el número de intento del que se trata.
 * A continuación, es necesario comprobar si realmente se trata de la clave de la 
 * caja fuerte:
 *
 * Si lo es, se procede a dar un mensaje de “Clave correcta, apertura de la caja” y 
 * se finaliza el programa.
 *
 * Si no lo es pero no se han superado los 3 intentos, se le muestra un mensaje al 
 * usuario para que lo vuelve a intentar: “Inténtelo de nuevo”.
 * Si no lo es pero ya se han superado los tres intentos, se bloquea la caja de 
 * seguridad dando el siguiente mensaje al usuario “Caja bloqueada, número máximo de 
 * intentos superado” y se finaliza el programa.
 *
 * Ejemplo de Ejecución 1: supuesta la clave con el valor 23456 (#define CLAVE 23456), 
 * no se acierta:
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): -6
 * Digito incorrecto
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): 3
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): 6
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): 2
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): 7
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): 8
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): -1
 * Intento 1: Posible valor de la clave: 36278
 * Intentelo de nuevo
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): 8
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): 3
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): -1
 * Intento 2: Posible valor de la clave: 83
 * Intentelo de nuevo
 *
 * 2
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): 5
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): 5
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): 8
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): 7
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): -1
 * Intento 3: Posible valor de la clave: 5587
 * Caja bloqueada, numero maximo de intentos superado
 * Press any key to continue.
 *
 * Ejemplo de Ejecución 2: supuesta la clave con el valor 23456 (#define CLAVE 23456), 
 * se acierta.
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): -2
 * Digito incorrecto
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): 3
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): 5
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): 6
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): -1
 * Intento 1: Posible valor de la clave: 356
 * Intentelo de nuevo
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): 2
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): 3
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): 4
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): 5
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): 6
 * Introduzca un digito (entre 0 y 9 y -1 para terminar): -1
 * Intento 2: Posible valor de la clave: 23456
 * Clave correcta, apertura de la caja
 * Press any key to continue.
 */

#include <stdio.h>

#define CLAVE 23168

int main(void){
  int intentos = 0;
  int clave = 0;
  int num;
  //Pedimos contraseñas hasta que agotemos los intentos
  do{

    //Mientras no sea -1m seguimos añadiendo cifras a nuestro número  
    do{

      //Comprobamos que el número que metemos es válido
      do{
        printf("\nIntroduzca un digito (entre 0 y 9 y -1 para terminar): ");
        scanf("%d", &num);
        if(num < -1 || num > 9){
	  printf("\nDígito incorrecto");
        }
      }while(num < -1 || num > 9);

      if(num != -1){
        clave = (clave * 10) + num;
      }
    }while(num != -1);

    intentos++;
    printf("\nIntento %d: Posible valor de la clave: %d", intentos, clave);

    if(clave != CLAVE){
      clave = 0;
      printf("\nIntentelo de nuevo");
    }

  }while(intentos < 3 && clave != CLAVE);

  if(clave != CLAVE){
    printf("\nCaja bloqueada, numero maximo de intentos superado\n");
  }else{
    printf("\nClave correcta, apertura de la caja\n");
  }

  return 0;
}
