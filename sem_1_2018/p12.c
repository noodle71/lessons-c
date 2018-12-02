/*
GE_V_ICAI: Gestión y Venta de billetes de avión de la
Agencia de Viajes ICAI.
Entrega 3
Y seguimos con el proyecto GEVICAI “Gestión y Venta de billetes de avión de la Agencia de Viajes ICAI”, que
comenzamos en la práctica 10 y que vamos a terminar con esta práctica.
Nuevamente, vamos a partir del programa que hemos realizado en la práctica 11 seguimos añadiéndole
funcionalidad.
Como ya hemos aprendido a manejar archivos binarios, vamos a crear un nuevo archivo binario en el que vamos
a escribir en él y leer de él las ventas que se han realizado. Para ello, va a ser necesario que, después de haber
rellenado los vectores de aviones y recorridos, y antes de llegar al menú con las opciones del programa, abrir el
archivo binario ventas_realizadas.dat en modo lectura/escritura con las comprobaciones que sean
necesarias. No hay que olvidar que al finalizar la ejecución del programa, va a ser necesario cerrar el archivo
siempre y cuando se haya podido abrir correctamente.
El archivo ventas_realizadas.dat va a contener las ventas que se han ido realizando a través de la función
VentaBilletes(). Si después de haber ejecutado la opción de venta, en el programa principal se comprueba
que se ha podido realizar la venta, además de mostrar la estructura T_VENTA por pantalla (que ya se hacía en la
entrega anterior), se debe almacenar (escribir) la venta realizada al final del archivo ventas_realizadas.dat .
Hay que recordar que según se realiza la venta, el campo tarjeta_embarque de la estructura T_VENTA está
puesto a 0, indicando que no se ha generado la tarjeta de embarque todavía.
Además, se van a añadir dos nuevas opciones al menú:
6.
Mostrar el contenido del archivo ventas_realidas.dat. Para llevar a cabo esta opción, va a
utilizarse la función
void MostrarArchivoVentas(FILE *pfv);
A su vez, esta función utilizará la función MostrarVenta() creada en la entrega anterior y que
mostraba por pantalla la información de la venta recibida como argumento.
void MostrarVenta(T_VENTA vent);
7.
Obtener la tarjeta de embarque. En esta opción lo que se busca es simular que llegado el momento, se
va a sacar la tarjeta de embarque (o tarjetas de embarque si la venta es de varias plazas) de una venta
realizada previamente.
Antes de hacer la llamada a la función ObtenerTarjetas() se le debe preguntar al usuario de qué
identificador de venta ( id_venta ) quiere obtener la tarjeta de embarque (recordemos que el
identificador de la venta se generaba aleatoriamente al hacer la venta del billetes).
El prototipo de la función ObtenerTarjetaS() es:
int ObtenerTarjetas(FILE *pfv, int id_venta, int *posicion_venta);
La función devuelve un valor entero que indica:
 Un valor >= 0 sí se han obtenido las tarjetas de embarque y la venta que se corresponde con el
id_venta está en la posición indicada por el valor. Es decir, si la función devuelve el valor 2
indica que se han podido generar las tarjetas de embarque y la venta es la tercera del archivo
binario (si es la primera se devuelve el valor 0).
 -1, no se han podido obtener las tarjetas de embarque porque no existe ese identificador de
venta en el archivo binario.
 -2, no se han podido obtener las tarjetas de embarque porque ya se han obtenido previamente
(el campo de tarjeta_embarque de esa venta está puesto a 1).

Dentro de la función ObtenerTarjetas() en caso de poder obtener las tarjetas de embarque, será
necesario modificar en el archivo binario la venta cuyo identificador se corresponda con el id_venta ,
poniendo a 1 el campo tarjeta_embarque de dicha venta.
En el programa principal se mostrará un mensaje indicando si han podido o no obtener las tarjetas de
embarque. Si no se han podido obtener se indicará el motivo, y si se han podido obtener se mostrará un
mensaje similar a:
“Obtenidas las tarjetas de embarque de la venta con identificador 33445 para
3 billetes entre MAD y NYC en el Boeing 737”
Para poder mostrar este mensaje puede ser útil utilizar las funciones BuscarAvion() y
BuscarRecorrido() creadas en la entrega anterior.
8.
(Opcional) Generar un informe de las ventas realizadas.
Para realizar este informe, se va a utilizar la función GenerarInforme() que generará un informe en
un archivo de texto cuyo nombre se le solicitará al usuario. En este nuevo archivo, hay que escribir la
siguiente información:
 Ventas realizadas en formato de tabla con todos sus campos.
 Importe total de las ventas realizadas.
 Porcentaje de billetes con la tarjeta de embarque emitidas.
 Porcentaje de billetes con la tarjeta de embarque no emitidas.
 Venta destacada: se corresponde con la venta de mayor importe.
El prototipo de la función GenerarInforme() es:
void GenerarInforme(FILE *pfv);
Dado que no se pasa el puntero del archivo de texto a crear se entiende que se abre y cierra dentro de la
función.
9.
Salir.
Informe de la práctica
 Entregar los listados de los programas.
 Entregar un ejemplo de la salida de cada programa.
3
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
#define F_VENTAS "ventas_realidas.dat"

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

//NUEVO EN LA PRACTICA 12
void MostrarArchivoVentas(FILE *pfv);
int ObtenerTarjetas(FILE *pfv, int id_venta, int *posicion_venta);

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
  FILE *f_avi, *f_rec, *f_ven;
  float precio;
  int num_vuelo;
  int num_billetes;
  T_VENTA vent;
  int res_venta;
  int id_venta;
  int res_tarjeta;
  int posicion_venta;

  srand((unsigned)time(NULL));
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
        f_ven = fopen(F_VENTAS, "ab");
        fseek(f_ven, 0, SEEK_END);
        if (f_ven != NULL)
        {
          fwrite(&vent, sizeof(T_VENTA), 1, f_ven);
          fclose(f_ven);
        }
        MostrarVenta(vent);
      }
      break;
    case 5:
      PedirFloat("Introduzca el precio", &precio);
      BuscarRecorridosBaratos(v_rec, num_rec, v_av, num_avi, precio);
      break;
    case 6:
      f_ven = fopen(F_VENTAS, "rb");
      puts("Mostrando ventas:\n");
      MostrarArchivoVentas(f_ven);
      fclose(f_ven);
      break;
    case 7:
      f_ven = fopen(F_VENTAS, "rb+");
      PedirInt("Introduzca el ID de venta", &id_venta);
      posicion_venta = -1;
      res_tarjeta = ObtenerTarjetas(f_ven, id_venta, &posicion_venta);
      if (res_tarjeta == -1)
      {
        puts("ID venta no encontrado");
      }
      else if (res_tarjeta == -2)
      {
        puts("Tarjetas de embarque ya emitidas");
      }
      else
      {
        fseek(f_ven, res_tarjeta  * sizeof(T_VENTA), SEEK_SET);
        fread(&vent, sizeof(T_VENTA), 1, f_ven);
        MostrarVenta(vent);
        // printf("Obtenidas las tarjetas de embarque de la venta con identificador %d para %d billetes entre %s y %s en el %s");
      }

      fclose(f_ven);
      break;
    case 8:
      puts("Salir\n\n");
      break;
    default:
      puts("ERROR: Opcion invalida");
    }

  } while (opcion != 8);
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
  if (index_recorrido >= 0)
  {
    r = v_rec[index_recorrido];
    index_avion = BuscarAvion(v_av, num_av, r.id_avion, &plazas);
    if (index_avion >= 0)
    {
      plazas_restantes = plazas - r.num_pas - num_billetes;
      if (plazas_restantes >= 0)
      {
        res = 1;
        vent->id_venta = rand() % 1000000;
        vent->num_vuelo = num_vuelo;
        vent->id_avion = r.id_avion;
        vent->num_billetes = num_billetes;
        vent->precio_total = num_billetes * r.precio;
        vent->tarjeta_embarque = 0;
        v_rec[index_recorrido].num_pas += num_billetes;
      }
      else
      {
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

//NUEVO EN LA PRACTICA 12
void MostrarArchivoVentas(FILE *pfv)
{
  int check = 1;
  T_VENTA venta;
  fseek(pfv, 0, SEEK_SET);
  do
  {
    check = fread(&venta, sizeof(T_VENTA), 1, pfv);
    if (check > 0)
    {
      MostrarVenta(venta);
    }
  } while (check > 0);
  return;
}

int ObtenerTarjetas(FILE *pfv, int id_venta, int *posicion_venta)
{
  int check = 1;
  int cont;
  T_VENTA venta;
  cont = 0;
  *posicion_venta = -1;
  fseek(pfv, 0, SEEK_SET);
  do
  {
    check = fread(&venta, sizeof(T_VENTA), 1, pfv);
    
    if (check > 0 && id_venta == venta.id_venta)
    {
      if (venta.tarjeta_embarque != 1)
      {
        venta.tarjeta_embarque = 1;
        *posicion_venta = cont;
        fseek(pfv, cont * sizeof(T_VENTA), SEEK_SET);
        fwrite(&venta, sizeof(T_VENTA), 1, pfv);
      }
      else
      {
        *posicion_venta = -2;
      }
    }
    cont++;
  } while (check > 0 && *posicion_venta == -1);
  return *posicion_venta;
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
    puts("6 - Mostrar Ventas");
    puts("7 - Obtener tarjetas embarque");
    puts("8 - Salir");
    PedirInt("", &opcion);
    if (opcion < 0 || opcion > 8)
    {
      puts("ERROR: Opcion incorrecta");
    }
  } while (opcion < 0 || opcion > 8);
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