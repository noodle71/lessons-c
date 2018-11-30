/*
GEVICAI: “GE_V_ICAI: gestión y venta de billetes de avión de la Agencia de Viajes ICAI”.
Entrega 1
Se va a realizar un proyecto a lo largo de las últimas semanas del curso de manera incremental, a
medida que vayamos aprendiendo a manejar estructuras y archivos.
El proyecto va a consistir en hacer un programa que realice diversas tareas de gestión y venta de
billetes de avión de la Agencia de Viajes ICAI.
La información referente a un tipo de avión se va a guardar en una estructura T_AVION que contiene la
siguiente información:

Identificador del avión (id_avion), es un número entero.
Modelo del avión (modelo), es una cadena de caracteres de no más de 20 caracteres.
Número de plazas del avión (num_plazas), es un número entero.
Velocidad máxima de ese modelo de avión (vel_max), es un dato de tipo float.
La información referente a un recorrido determinado se va a guardar en una estructura T_RECORRIDO
que contiene la siguiente información:

Número de vuelo (num_vuelo, tipo entero), es el número de vuelo de ese recorrido.
Código del Aeropuerto de origen (origen), es una cadena de caracteres de no más de 4
caracteres.
Código del Aeropuerto de destino (destino), es una cadena de caracteres de no más de 4
caracteres.
Identificador del tipo de avión asignado a ese vuelo (id_avion), es un entero.
Día de la semana (día), es una cadena de caracteres de no más de 10 caracteres.
La hora de salida (hora_salida), es una variable de tipo T_HORARIO, que a su vez
contiene la hora (en formato de 24 horas) y el minuto.
Número de pasajeros (num_pas), es un valor entero que inicialmente, antes de comenzar la
venta de billetes tendrá el valor 0 (indica que no se ha vendido ningún billete de ese
recorrido).

Inicialmente, antes de poder comenzar con las tareas de gestión y venta de billetes, va a ser necesario
cargar el vector dinámico de aviones (v_av) y el vector dinámico de recorridos (v_rec).
En la carga manual (se le solicita la información al usuario), habrá que preguntar al usuario cuántos
tipos de aviones se van a cargar, num_avi, y posteriormente llamar a la función:
void CargaManualAviones(T_AVION v[], int num_avi);
La función CargaManualAviones() es la encargada de rellenar el vector con todos los tipos de
avión. Para cargar cada avión hará una llamada a la función CargaUnAvion() cuyo prototipo es:
void CargaUnAvion(T_AVION *av);
que se encarga de solicitar los datos de un avión y guardarlos en la estructura que le han pasado por
referencia.
De la misma manera que en el caso de los aviones, se han de cargar manualmente los recorridos,
solicitando al usuario previamente que indique cuántos recorridos va a incluir, num_rec, y llamando
posteriormente a la función CargaManualRecorridos(), que llamará a su vez a
CargaUnRecorrido().
void CargaManualRecorridos(T_RECORRIDO v[], int num_rec);
void CargaUnRecorrido(T_RECORRIDO *rec);
Al rellenar el campo de número de pasajeros, siempre estará puesto a 0 inicialmente.

Una vez cargados los dos vectores, se presentará un menú al usuario donde se podrá elegir la tarea a
realizar:
1. Mostrar todos los tipos de avión, utilizando la función MostrarAviones(), que a su vez
llamará a la función MostrarUnAvion() que imprimirá por pantalla cada uno de los
campos de la estructura que recibe por referencia.
void MostrarAviones(T_AVION v[], int num_avi);
void MostrarUnAvion(T_AVION *av);
2. Mostrar todos los recorridos, utilizando la función MostrarRecorridos(), que a su vez
llamará a la función MostrarUnRecorrido()que imprimirá por pantalla cada uno de los
campos de la estructura que recibe por referencia.
void MostrarRecorridos(T_RECORRIDO v[], int num_rec);
void MostrarUnRecorrido(T_RECORRIDO *rec);
3. Mostrar todos los recorridos que cubren un origen y un destino (con los códigos de aeropuerto
que indique el usuario). Para ello, se ha de utilizar la función
RecorridoSeleccionado() que recibe la cadena con el código origen y con el código
destino. Esta función devuelve el número de recorridos encontrados que cubran el trayecto, y
devuelve por referencia el recorrido cuya hora de salida es la más temprana.
int RecorridoSeleccionado(T_RECORRIDO v[], int num_rec,
char *origen, char *destino,
T_RECORRIDO *rec_temprano);
Los datos que devuelve la función se mostrarán en el programa principal.
4.
Salir
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20
#define M 4
#define D 10
#define PRINT_RECORRIDO "%d %s %s %d %s %d:%d %d\n"
#define PRINT_AVION "%d %s %d %f\n"

typedef struct
{
  int hora;
  int minuto;
} T_HORARIO;

typedef struct
{
  int num_vuelo;
  char origen[M];
  char destino[M];
  int id_avion;
  char dia[D];
  T_HORARIO hora_salida;
  int num_pas;
} T_RECORRIDO;

typedef struct
{
  int id_avion;
  char modelo[N];
  int num_plazas;
  float vel_max;
} T_AVION;

void CargaManualAviones(T_AVION v[], int num_avi);
void CargaUnAvion(T_AVION *av);

void CargaManualRecorridos(T_RECORRIDO v[], int num_rec);
void CargaUnRecorrido(T_RECORRIDO *rec);

void MostrarAviones(T_AVION v[], int num_avi);
void MostrarUnAvion(T_AVION *av);

void MostrarRecorridos(T_RECORRIDO v[], int num_rec);
void MostrarUnRecorrido(T_RECORRIDO *rec);

int RecorridoSeleccionado(T_RECORRIDO v[], int num_rec, char *origen, char *destino, T_RECORRIDO *rec_temprano);

//FUNCIONES NO OBLIGATORIAS
int menu(void);
void PedirCadena(char mensaje[], int tam, char cadena[]);
void PedirInt(char mensaje[], int *num);
void PedirFloat(char mensaje[], float *num);
void LimpiarCadena(int tam, char cadena[]);
void AsignarRecorridoTemprano(T_RECORRIDO *rec_temprano, T_RECORRIDO recorrido, int *hora_temprano, int *minuto_temprano);

int main(void)
{
  int opcion;
  int num_rec, num_avi;
  T_AVION *v_av;
  T_RECORRIDO *v_rec, rec_temprano;
  char origen[M], destino[M];
  int recorridos_encontrados;

  //CARGA MANUAL
  do
  {
    PedirInt("Introduzca numero de aviones", &num_avi);
    if (num_avi <= 0)
    {
      puts("ERROR");
    }
  } while (num_avi <= 0);

  do
  {
    PedirInt("Introduzca numero de recorridos", &num_rec);
    if (num_avi <= 0)
    {
      puts("ERROR");
    }
  } while (num_avi <= 0);

  v_av = (T_AVION *)calloc(num_avi, sizeof(T_AVION));
  v_rec = (T_RECORRIDO *)calloc(num_rec, sizeof(T_RECORRIDO));

  if (v_av != NULL && v_rec != NULL)
  {
    CargaManualAviones(v_av, num_avi);
    CargaManualRecorridos(v_rec, num_rec);
  }

  do
  {
    opcion = menu();
    switch (opcion)
    {
    case 1:
      MostrarAviones(v_av, num_avi);
      break;
    case 2:
      MostrarRecorridos(v_rec, num_rec);
      break;
    case 3:
      PedirCadena("\nIntroduzca origen: ", M, origen);
      PedirCadena("\nIntroduzca destino: ", M, destino);
      recorridos_encontrados = RecorridoSeleccionado(v_rec, num_rec, origen, destino, &rec_temprano);
      if (recorridos_encontrados > 0)
      {
        printf("\nSe han encontrado %d recorridos. Mostrando el mas temprano:\n", recorridos_encontrados);
        MostrarUnRecorrido(&rec_temprano);
      }
      else
      {
        puts("No se han encontrado recorridos\n");
      }
      break;
    case 4:
      puts("Salir\n\n");
    }

  } while (opcion != 4);
  return 0;
}

void CargaManualAviones(T_AVION v[], int num_avi)
{
  int i;
  for (i = 0; i < num_avi; i++)
  {
    printf("\n\nIntroduzca datos del avion %d:\n", i + 1);
    CargaUnAvion(&v[i]);
  }
  return;
}

void CargaUnAvion(T_AVION *av)
{
  PedirInt("Id avion: ", &(av->id_avion));
  PedirCadena("Modelo: ", N, av->modelo);
  PedirInt("Num plazas: ", &(av->num_plazas));
  PedirFloat("Vel max: ", &(av->vel_max));
  return;
}

void CargaManualRecorridos(T_RECORRIDO v[], int num_rec)
{
  int i;
  for (i = 0; i < num_rec; i++)
  {
    printf("\n\nIntroduzca datos del recorrido %d:\n", i + 1);
    CargaUnRecorrido(&v[i]);
  }
  return;
}

void CargaUnRecorrido(T_RECORRIDO *rec)
{
  PedirInt("Num vuelo: ", &(rec->num_vuelo));
  PedirCadena("Origen: ", M, rec->origen);
  PedirCadena("Destino: ", M, rec->destino);
  PedirInt("Id avion: ", &(rec->id_avion));
  PedirCadena("Dia (DD/MM/AAAA): ", D, rec->dia);
  PedirInt("Hora salida: ", &(rec->hora_salida.hora));
  PedirInt("Minuto salida: ", &(rec->hora_salida.minuto));
  rec->num_pas = 0;
  return;
}

void MostrarAviones(T_AVION v[], int num_avi)
{
  int i;
  puts("\nMostrando aviones:");
  for (i = 0; i < num_avi; i++)
  {
    MostrarUnAvion(&v[i]);
  }
  return;
}

void MostrarUnAvion(T_AVION *av)
{
  printf(PRINT_AVION, av->id_avion, av->modelo, av->num_plazas, av->vel_max);
  return;
}

void MostrarRecorridos(T_RECORRIDO v[], int num_rec)
{
  int i;
  puts("\nMostrando recorridos:");
  for (i = 0; i < num_rec; i++)
  {
    MostrarUnRecorrido(&v[i]);
  }
  return;
}

void MostrarUnRecorrido(T_RECORRIDO *rec)
{
  printf(PRINT_RECORRIDO, rec->num_vuelo, rec->origen, rec->destino, rec->id_avion, rec->dia, rec->hora_salida.hora, rec->hora_salida.minuto, rec->num_pas);
  return;
}

int RecorridoSeleccionado(T_RECORRIDO v[], int num_rec, char *origen, char *destino, T_RECORRIDO *rec_temprano)
{
  int i;
  int cont = 0;
  int h, m;
  int h_temp, m_temp;
  T_RECORRIDO r;
  for (i = 0; i < num_rec; i++)
  {
    r = v[i];
    if (strcmp(r.origen, origen) == 0 && strcmp(r.destino, destino) == 0)
    {
      cont++;
      h = r.hora_salida.hora;
      m = r.hora_salida.minuto;
      if (cont == 1)
      {
        AsignarRecorridoTemprano(rec_temprano, r, &h_temp, &m_temp);
      }
      else if (h < h_temp || (h == h_temp && m < m_temp))
      {
        AsignarRecorridoTemprano(rec_temprano, r, &h_temp, &m_temp);
      }
    }
  }
  return cont;
}

//FUNCIONES NO OBLIGATORIAS
void AsignarRecorridoTemprano(T_RECORRIDO *rec_temprano, T_RECORRIDO recorrido, int *hora_temprano, int *minuto_temprano)
{
  *rec_temprano = recorrido;
  *hora_temprano = recorrido.hora_salida.hora;
  *minuto_temprano = recorrido.hora_salida.minuto;
  return;
}

int menu(void)
{
  int opcion;
  do
  {
    puts("\nMENU:");
    puts("1 - Mostrar TODOS aviones");
    puts("2 - Mostrar TODOS recorridos");
    puts("3 - Mostrar recorridos para origen/destino");
    puts("4 - Salir");
    PedirInt("", &opcion);
    if (opcion < 0 || opcion > 4)
    {
      puts("ERROR: Opcion incorrecta");
    }
  } while (opcion < 0 || opcion > 4);
  return opcion;
}

void PedirInt(char mensaje[], int *num)
{
  do
  {
    fflush(stdin);
    puts(mensaje);
    scanf("%d", num);
    getchar(); //Para recoger el /n que se queda en el stdin al pulsar enter.
    if (*num < 0)
    {
      puts("ERROR");
    }
  } while (*num < 0);
  return;
}

void PedirFloat(char mensaje[], float *num)
{
  fflush(stdin);
  puts(mensaje);
  scanf("%f", num);
  getchar(); //Para recoger el /n que se queda en el stdin al pulsar enter.
  return;
}

void PedirCadena(char mensaje[], int tam, char cadena[])
{
  fflush(stdin);
  puts(mensaje);
  gets(cadena, tam, stdin);
  LimpiarCadena(tam, cadena);
  return;
}

void LimpiarCadena(int tam, char cadena[])
{
  int i;
  for (i = 0; i < tam; i++)
  {
    if (cadena[i] == '\n')
    {
      cadena[i] = '\0';
    }
  }
  cadena[tam - 1] = '\0';
}