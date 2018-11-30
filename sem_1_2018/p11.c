/*

Vamos a retomar el proyecto GEVICAI “Gestión y Venta de billetes de avión de la Agencia de Viajes
ICAI”, que comenzamos en la práctica 10.
En la práctica 10 hemos estado trabajando con las estructuras (que mantendremos a lo largo de todo el
proyecto):
typedef struct {
int id_avion; 
char modelo[20];
int num_plazas; 
float vel_max; 
}T_AVION;
typedef struct {
int num_vuelo; 
char origen[4];
char destino[4];
int id_avion; 
char dia[10]; 
T_HORARIO hora_salida;
int num_pas;

float precio; 
} T_RECORRIDO;
ATENCIÓN: Añadir el nuevo campo precio a la estructura T_RECORRIDO

Además, vamos a añadir una nueva estructura T_VENTA que va a contener las ventas de billetes que
se han realizado. La estructura será:
typedef struct {
int id_venta; 
int num_vuelo; 
int id_avion; 
int num_billetes; 
float precio_total; 
int tarjeta_embarque; 
}T_VENTA;
Ahora que ya sabemos manejar archivos, podemos añadir a nuestro proyecto la posibilidad de hacer la
carga automática. De hecho, le vamos a dejar elegir al usuario qué tipo de carga quiere realizar.
Partiendo del código desarrollado en la práctica 10, se ha de preguntar al principio del programa
principal si el usuario quiere realizar la carga manual o automática. En caso de elegir la carga manual,
se ejecutarán las funciones creadas para llevarlas a cabo en la práctica 10. Si se elige la carga
automática va a ser necesario:

Abrir los archivos de texto aviones.txt y recorridos.txt en modo lectura (deben estar
creados y se pueden crear con un editor de textos como Block de Notas, NotePad o el propio
editor de Codelite).
Utilizando las funciones ContarAviones() y ContarRecorridos() comprobar los datos
de cuántos aviones y cuántos recorridos hay en los ficheros. Ambas funciones devolverán por
referencia el número de aviones o recorridos encontrados en los archivos de texto.
void ContarAviones(FILE *pf, int *pcont);
void ContarRecorridos(FILE *pf, int *pcont);


A continuación, se ha de asignar memoria dinámicamente a los dos vectores v_av y v_rec .
Una vez que se ha podido asignar la memoria dinámicamente, es necesario cargar los dos
CargaAutomaticaAviones()
y
vectores
utilizando
las
funciones
CargaAutomaticaRecoridos().
void CargaAutomaticaAviones(FILE *pf, T_AVION v_av[], int num_av);
void CargaAutomaticaRecorridos(FILE *pf, T_RECORRIDO v_rec[], int
num_rec);
Una vez que se ha realizado la carga de la información de aviones y recorridos desde los archivos de
texto, pueden cerrarse pues ya no se van a utilizar para nada más.
A continuación, se han de añadir nuevas opciones al menú, mantenimiento las que ya existían:
4.
Venta de billetes. Se le solicita al usuario cuál es el número de vuelo en el que quiere realizar
la compra y cuántos billetes se quieren comprar (los pasajeros que van a viajar).
La gestión de la venta de billetes se va a realizar a través de la función VentaBilletes()
que debe devolver:
 el valor 1 si la venta se ha podido realizar.
 el valor 0 si no se ha podido realizar porque no quedaba ninguna plaza
disponible.
 un valor negativo que indicará que no se ha podido realizar la venta porque
faltaban ese mismo valor de plazas (es decir, si el usuario ha solicitado 5
plazas y sólo había dos disponibles, la función VentaBilletes()
devolverá el valor -3, indicando que no se ha podido realizar la venta porque
faltaban 3 plazas para completar la venta).

Además de la información anterior, la función VentaBilletes() debe rellenar, en el caso de
que se haya podido realizar la venta, una estructura T_VENTA pasada por referencia con la
información de la venta.
El prototipo de la función VentaBilletes() es:
int VentaBilletes(T_AVION v_av[], int num_av, T_RECORRIDO v_rec[],
int num_rec, int num_vuelo, int num_billetes,
T_VENTA *vent);
Dentro de la función, para saber si es posible realizar la venta de los billetes solicitados, se ha
de utilizar la función BuscarRecorrido() para buscar en el vector de recorridos aquél que
tenga el número de vuelo indicado:
int BuscarRecorrido(T_RECORRIDO v_rec[], int num_rec, int num_vuelo);
La función BuscarRecorrido() devuelve el valor -1 si no se ha encontrado ningún
recorrido con ese número de vuelo, y el índice en el vector v_rec del recorrido que tenga
dicho número de vuelo en caso de haberlo encontrado.
Si se ha encontrado el número de vuelo, es necesario buscar en el vector v_av el tipo de avión
con el fin de saber el número de plazas máximo de ese tipo de avión. Para ello, se va a utilizar
la función BuscarAvion() que sabiendo el tipo de avión que va a realizar dicho recorrido
( id_avion ) va a devolver el valor -1 si no ha encontrado el identificador del avión en el
vector de aviones, y el índice de dicho avión en el vector de aviones ( v_av ) en caso de
haberlo encontrado. También va a devolver por referencia el número de plazas máximo de
dicho tipo de avión.
int BuscarAvion(T_AVION
*num_max);
v_av[],
int
num_av,
int
id_avion,
int
Con toda esta información, la función VentaBilletes() decide si se puede llevar a cabo o
no la venta. Si se puede llevar a cabo la venta, debe incrementar en el vector de recorridos
v_rec el número de pasajeros del recorrido que se corresponde con la venta y rellena la
estructura T_VENTA con la información que corresponda. Al realizar la venta de billetes, el
campo tarjeta_embarque siempre se pondrá a 0 y el identificador de la venta ( id_venta )
se genera aleatoriamente con un número entre 0 y 1.000.000.
En el programa principal, después de haber ejecutado la función VentaBilletes() y si se
ha podido realizar la venta, se mostrará por pantalla la información de la venta realizada
utilizando la función MostrarVenta():
void MostrarVenta(T_VENTA vent);
5.
Mostrar posibles recorridos con un precio más bajo al indicado por el usuario. Para ello, se va
a utilizar la función BuscarRecorridosBaratos() que va a mostrar el número de vuelo, el
origen y el destino de todos aquellos vuelos cuyo precio sea inferior al indicado por el usuario
y que dispongan de plazas libres. Para ello, va a resultar útil utilizar la función
BuscarAvion() descrita en el apartado anterior.
El prototipo de la función es:
Void BuscarRecorridosBaratos(T_RECORRIDO v_rec[], int num_rec,
T_AVION v_av[], int num_av,
float precio);
6.
Salir.
Informe de la práctica
 Entregar los listados de los programas
 Entregar un ejemplo de la salida de cada programa.
4
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20
#define M 4
#define D 10
#define PRINT_RECORRIDO "%d %s %s %d %s %d:%d %d %f\n"
#define PRINT_AVION "%d %s %d %f\n"
#define PRINT_VENTA "ID: %d\tNUM. VUELO: %d\tID AVION: %d\tNUM. BILLETES: %d\tPRECIO: %.2f\tEMBARQUE: %d\n"
#define F_AVION "aviones.txt"
#define F_RECORRIDOS "recorridos.txt"

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
  float precio;
} T_RECORRIDO;

typedef struct
{
  int id_avion;
  char modelo[N];
  int num_plazas;
  float vel_max;
} T_AVION;

typedef struct
{
  int id_venta;         /*Identificador de la venta, número aleatorio entre 0 y 1.000.000 */
  int num_vuelo;        /* Número de vuelo de la venta*/
  int id_avion;         /* Identificador del avión que realiza el vuelo*/
  int num_billetes;     /* Número de billetes de la venta */
  float precio_total;   /* Precio total de esta venta */
  int tarjeta_embarque; /* 0 indica que no se ha generado la tarjeta de embarque y 1 que sí */
} T_VENTA;

void CargaManualAviones(T_AVION v[], int num_avi);
void CargaUnAvion(T_AVION *av);

void CargaManualRecorridos(T_RECORRIDO v[], int num_rec);
void CargaUnRecorrido(T_RECORRIDO *rec);

void MostrarAviones(T_AVION v[], int num_avi);
void MostrarUnAvion(T_AVION *av);

void MostrarRecorridos(T_RECORRIDO v[], int num_rec);
void MostrarUnRecorrido(T_RECORRIDO *rec);

int RecorridoSeleccionado(T_RECORRIDO v[], int num_rec, char *origen, char *destino, T_RECORRIDO *rec_temprano);

// NUEVO EN LA PRACTICA 11
void ContarAviones(FILE *pf, int *pcont);
void ContarRecorridos(FILE *pf, int *pcont);

void CargaAutomaticaAviones(FILE *pf, T_AVION v_av[], int num_av);
void CargaAutomaticaRecorridos(FILE *pf, T_RECORRIDO v_rec[], int num_rec);

int VentaBilletes(T_AVION v_av[], int num_av, T_RECORRIDO v_rec[], int num_rec, int num_vuelo, int num_billetes, T_VENTA *vent);

int BuscarRecorrido(T_RECORRIDO v_rec[], int num_rec, int num_vuelo);
int BuscarAvion(T_AVION v_av[], int num_av, int id_avion, int *num_max);

void MostrarVenta(T_VENTA vent);

void BuscarRecorridosBaratos(T_RECORRIDO v_rec[], int num_rec, T_AVION v_av[], int num_av, float precio);

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
  int num_rec = 0, num_avi = 0;
  T_AVION *v_av;
  T_RECORRIDO *v_rec, rec_temprano;
  char origen[M], destino[M];
  int recorridos_encontrados;
  int modo;
  FILE *f_avi, *f_rec;
  float precio;
  int num_vuelo;
  int num_billetes;
  T_VENTA vent;
  int res_venta;

  srand(time(NULL));
  do
  {
    PedirInt("Pulsa 0 para carga manual\nPulsa 1 para carga automatica", &modo);
    if (modo < 0 || modo > 1)
    {
      puts("ERROR");
    }
  } while (modo < 0 || modo > 1);

  if (modo == 1)
  {
    f_avi = fopen(F_AVION, "r");
    f_rec = fopen(F_RECORRIDOS, "r");
    if (f_avi != NULL && f_rec != NULL)
    {
      ContarAviones(f_avi, &num_avi);
      ContarRecorridos(f_rec, &num_rec);

      fclose(f_avi);
      fclose(f_rec);
    }
    else
    {
      puts("Error leyendo el fichero");
    }
  }
  else
  {
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
  }

  v_av = (T_AVION *)calloc(num_avi, sizeof(T_AVION));
  v_rec = (T_RECORRIDO *)calloc(num_rec, sizeof(T_RECORRIDO));

  if (v_av != NULL && v_rec != NULL)
  {
    if (modo == 1)
    {
      f_avi = fopen(F_AVION, "r");
      f_rec = fopen(F_RECORRIDOS, "r");
      if (f_avi != NULL && f_rec != NULL)
      {
        CargaAutomaticaAviones(f_avi, v_av, num_avi);
        CargaAutomaticaRecorridos(f_rec, v_rec, num_rec);

        fclose(f_avi);
        fclose(f_rec);
      }
      else
      {
        puts("Error leyendo el fichero");
      }
    }
    else
    {
      CargaManualAviones(v_av, num_avi);
      CargaManualRecorridos(v_rec, num_rec);
    }
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
      PedirInt("Introduzca el numero de vuelo", &num_vuelo);
      do
      {
        PedirInt("Introduzca el numero de billetes", &num_billetes);
        if (num_billetes < 0)
        {
          puts("ERROR");
        }
      } while (num_billetes < 0);
      res_venta = VentaBilletes(v_av, num_avi, v_rec, num_rec, num_vuelo, num_billetes, &vent);
      if (res_venta < 0)
      {
        printf("\nNo se ha podido completar la venta, faltan %d plazas\n", (-1) * res_venta);
      }
      else if (res_venta == 0)
      {
        puts("No se ha podido completar la venta, el vuelo esta lleno o no existe\n");
      }
      else
      {
        puts("Aqui tiene los resultados de la venta:\n");
        MostrarVenta(vent);
      }
      break;
    case 5:
      PedirFloat("Introduzca el precio", &precio);
      BuscarRecorridosBaratos(v_rec, num_rec, v_av, num_avi, precio);
      break;
    case 6:
      puts("Salir\n\n");
      break;
    default:
      puts("ERROR: Opcion invalida");
    }

  } while (opcion != 6);
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
  PedirFloat("Precio: ", &(rec->precio));
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
  printf(PRINT_RECORRIDO, rec->num_vuelo, rec->origen, rec->destino, rec->id_avion, rec->dia, rec->hora_salida.hora, rec->hora_salida.minuto, rec->num_pas, rec->precio);
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

// NUEVO EN LA PRACTICA 11
void ContarAviones(FILE *pf, int *pcont)
{
  int check;

  int id_avion;
  char modelo[N];
  int num_plazas;
  float vel_max;

  *pcont = 0;
  do
  {
    check = fscanf(pf, PRINT_AVION, &id_avion, modelo, &num_plazas, &vel_max);
    if (check == 4)
    {
      *pcont = *pcont + 1;
    }
  } while (check == 4);
  return;
}

void ContarRecorridos(FILE *pf, int *pcont)
{
  int check;
  int num_vuelo;
  char origen[M];
  char destino[M];
  int id_avion;
  char dia[D];
  T_HORARIO hora_salida;
  int num_pas;
  float precio;

  *pcont = 0;
  do
  {
    check = fscanf(pf, PRINT_RECORRIDO, &num_vuelo, origen, destino, &id_avion, dia, &hora_salida.hora, &hora_salida.minuto, &num_pas, &precio);
    if (check == 9)
    {
      *pcont = *pcont + 1;
    }
  } while (check == 9);
  return;
}

void CargaAutomaticaAviones(FILE *pf, T_AVION v_av[], int num_av)
{
  int i;

  for (i = 0; i < num_av; i++)
  {
    fscanf(pf, PRINT_AVION, &v_av[i].id_avion, v_av[i].modelo, &v_av[i].num_plazas, &v_av[i].vel_max);
    LimpiarCadena(N, v_av[i].modelo);
  }

  return;
}
void CargaAutomaticaRecorridos(FILE *pf, T_RECORRIDO v_rec[], int num_rec)
{
  int i;
  for (i = 0; i < num_rec; i++)
  {
    fscanf(pf, PRINT_RECORRIDO, &v_rec[i].num_vuelo, v_rec[i].origen, v_rec[i].destino, &v_rec[i].id_avion, v_rec[i].dia, &v_rec[i].hora_salida.hora, &v_rec[i].hora_salida.minuto, &v_rec[i].num_pas, &v_rec[i].precio);
    LimpiarCadena(M, v_rec[i].origen);
    LimpiarCadena(M, v_rec[i].destino);
    LimpiarCadena(D, v_rec[i].dia);
  }
  return;
}

int VentaBilletes(T_AVION v_av[], int num_av, T_RECORRIDO v_rec[], int num_rec, int num_vuelo, int num_billetes, T_VENTA *vent)
{
  int index_recorrido;
  int index_avion;
  int res = 0;
  int plazas;
  int plazas_restantes;
  T_RECORRIDO r;

  index_recorrido = BuscarRecorrido(v_rec, num_rec, num_vuelo);
  if(index_recorrido >= 0){
    r = v_rec[index_recorrido];
    index_avion = BuscarAvion(v_av, num_av, r.id_avion, &plazas);
    if(index_avion >= 0){
      plazas_restantes = plazas - r.num_pas - num_billetes;
      if(plazas_restantes >= 0){
        res = 1;
        vent->id_venta = rand()%1000000;
        vent->num_vuelo = num_vuelo;
        vent->id_avion = r.id_avion;
        vent->num_billetes = num_billetes;
        vent->precio_total = num_billetes * r.precio;
        vent->tarjeta_embarque = 0;
      }
      else{
        res = plazas_restantes;
      }
    }
  }
  return res;
}

int BuscarRecorrido(T_RECORRIDO v_rec[], int num_rec, int num_vuelo)
{
  int i;
  int found = -1;
  for (i = 0; (i < num_rec && found == -1); i++)
  {
    if (v_rec[i].num_vuelo == num_vuelo)
    {
      found = i;
    }
  }
  return found;
}

int BuscarAvion(T_AVION v_av[], int num_av, int id_avion, int *num_max)
{
  int i;
  int found = -1;
  *num_max = 0;
  for (i = 0; (i < num_av && found == -1); i++)
  {
    if (v_av[i].id_avion == id_avion)
    {
      found = i;
      *num_max = v_av[i].num_plazas;
    }
  }
  return found;
}

void MostrarVenta(T_VENTA vent)
{
  printf(PRINT_VENTA, vent.id_venta, vent.num_vuelo, vent.id_avion, vent.num_billetes, vent.precio_total, vent.tarjeta_embarque);
  return;
}

void BuscarRecorridosBaratos(T_RECORRIDO v_rec[], int num_rec, T_AVION v_av[], int num_av, float precio)
{
  int num_vuelo;
  char origen[M];
  char destino[M];

  int i;
  T_RECORRIDO r;
  int index_avion;
  int plazas;
  int plazas_restantes;
  puts("\nMostrando recorridos mas baratos:");
  for (i = 0; i < num_rec; i++)
  {
    r = v_rec[i];
    if (r.precio <= precio)
    {
      index_avion = BuscarAvion(v_av, num_av, r.id_avion, &plazas);
      plazas_restantes = plazas - r.num_pas;
      if (index_avion >= 0 && plazas_restantes > 0)
      {
        printf("Origen: %s\tDestino: %s\tNum. vuelo: %d\tPlazas: %d\tPrecio: %.2f\n", r.origen, r.destino, r.num_vuelo, plazas_restantes, r.precio);
      }
    }
  }
  return;
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
    puts("4 - Venta de billetes");
    puts("5 - Mostrar recorridos baratos");
    puts("6 - Salir");
    PedirInt("", &opcion);
    if (opcion < 0 || opcion > 6)
    {
      puts("ERROR: Opcion incorrecta");
    }
  } while (opcion < 0 || opcion > 6);
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
  return;
}