/*
 * Write a program to store and analyze information about account balance from 
 * bank customers, following these steps:
 *
 * 1. Read from the keyboard, the number of customers (validate that the number 
 * is positive, greater than 0). 
 * 
 * 2. Dynamically allocate memory to a vector v_clientes of T_CLIENTE_SALDO structures. 
 * Each structure T_CLIENTE_SALDO, stores the customer name and a vector of balances 
 * with the balances at last day of month for the first six months of the 
 * year (6 balances from January to June).
 *
 * typedef struct{
 *   char name[40];
 *   float vsaldos[6];
 * }T_CLIENTE_SALDO;
 * 
 * 3. You need to fill the vector v_clientes of T_CLIENTE_SALDO structures, 
 * reading information from the keyboard. To do this, you must use the 
 * function RellenarClientes(), this function should fill the entire vector of 
 * customers along with their balances.
 * 
 * The function RellenarClientes() should call repeatedly the function RellenarUnCliente(). 
 * The function RellenarUnCliente() reads from the keyboard the information and returns 
 * the structure by reference. 
 *
 * 4. Then you have to count, using the function ContarSaldosInferiores() 
 * (which will be called from the main program), the number of customers whose 
 * average balance of these 6 months is less than 5,000 €. This counter is returned 
 * to main program by reference.
 *
 * 5. Dynamically allocate memory to another vector v_saldos_medios of T_CLIENTE_MEDIO 
 * structures, to store customer information whose average balance is less 
 * than 5,000 € (as many as has returned the function ContarSaldosInferiores()).
 * typedef struct{
 *   char name [40];
 *   float saldo_medio;
 * }T_CLIENTE_MEDIO;
 *
 * 6. Fill the v_saldos_medios vector of T_CLIENTE_MEDIO structures using 
 * the function CopiarInformacion() that receives the vector v_clientes and 
 * must fill the v_saldos_medios vector. 
 *
 * 7. From the main() display on screen the information contained in the 
 * vector v_saldos_medios.
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define NAME_LEN 40
#define SALDOS_LEN 6
#define BALANCE 5000

typedef struct{
  char name[NAME_LEN];
  float vsaldos[SALDOS_LEN];
}T_CLIENTE_SALDO;

typedef struct{
  char name [NAME_LEN];
  float saldo_medio;
}T_CLIENTE_MEDIO;

void RellenarClientes(T_CLIENTE_SALDO *v_clientes, int num_clientes);
void RellenarUnCliente(T_CLIENTE_SALDO *t_client);
void ContarSaldosInferiores(T_CLIENTE_SALDO *v_clientes, int num_clientes, int *counter);
void CopiarInformacion(T_CLIENTE_SALDO *v_clientes, int num_clientes, T_CLIENTE_MEDIO *v_saldos_medios);

void MostrarClientes(T_CLIENTE_SALDO *v_clientes, int num_clientes);
void MostrarClientesMedios(T_CLIENTE_MEDIO *v_saldos_medios, int num_saldos_medios);
float BalanceMedio(T_CLIENTE_SALDO cliente);

int main(void){
  T_CLIENTE_SALDO *v_clientes;
  T_CLIENTE_MEDIO *v_saldos_medios;
  int num_clientes = 0;
  int i;
  int j;
  int counter;

  do{
    printf("\nEnter the number of customers: ");
    scanf("%d", &num_clientes);
    if(num_clientes <= 0){
      printf("\nERROR: Number of customers must be greater than 0.");
    }
  }while(num_clientes <= 0);

  v_clientes = (T_CLIENTE_SALDO *) calloc(num_clientes, sizeof(T_CLIENTE_SALDO));

  if(v_clientes == NULL){
    printf("\nERROR: Can't allocate memory.");
  }else{
    RellenarClientes(v_clientes, num_clientes);
    printf("\nSHOWING ALL CUSTOMERS:");
    MostrarClientes(v_clientes, num_clientes);
    ContarSaldosInferiores(v_clientes, num_clientes, &counter);
    v_saldos_medios = (T_CLIENTE_MEDIO *) calloc(counter, sizeof(T_CLIENTE_MEDIO));
    if(v_saldos_medios == NULL){
      printf("\nERROR: Can't allocate memory.");
    }else{
      CopiarInformacion(v_clientes, num_clientes, v_saldos_medios);
      printf("\n\nSHOWING CUSTOMERS WITH BALANCE EQUALS OR HIGHER THAN %d", BALANCE);
      MostrarClientesMedios(v_saldos_medios, counter);
    }
    free(v_clientes);
    free(v_saldos_medios);
  }
  printf("\n");
  return 0;
}

void RellenarClientes(T_CLIENTE_SALDO *v_clientes, int num_clientes){
  int i;
  for(i = 0; i < num_clientes; i++){
    printf("\nCustomer %d data:", i + 1);
    RellenarUnCliente(&v_clientes[i]);
  }
  return;
}

void RellenarUnCliente(T_CLIENTE_SALDO *t_cliente){
  int i;
  //Like fflush(stdin) to avoid storing the /n in the stdin so the fgets will be skipped.
  getchar();
  printf("\nIntroduce name: ");
  fgets(t_cliente->name, NAME_LEN, stdin);
  for(i = 0; i < SALDOS_LEN; i++){
    printf("\nIntroduce balance for month %d: ", i + 1);
    scanf("%f", &t_cliente->vsaldos[i]);
  }
  return;
}

void ContarSaldosInferiores(T_CLIENTE_SALDO *v_clientes, int num_clientes, int *counter){
  int i;
  int c = 0;
  for(i = 0; i < num_clientes; i++){
    if(BalanceMedio(v_clientes[i]) >= BALANCE){
      c++;
    }
  }
  *counter = c;
  return;
}

void CopiarInformacion(T_CLIENTE_SALDO *v_clientes, int num_clientes, T_CLIENTE_MEDIO *v_saldos_medios){
  int i;
  int j = 0;
  for(i = 0; i < num_clientes; i++){
    if(BalanceMedio(v_clientes[i]) >= BALANCE){
      strcpy(v_saldos_medios[j].name, v_clientes[i].name);
      v_saldos_medios[j].saldo_medio = BalanceMedio(v_clientes[i]);
      j++;
    }
  }
  return;
}

void MostrarClientes(T_CLIENTE_SALDO *v_clientes, int num_clientes){
  int i;
  int j;
  for(i = 0; i < num_clientes; i++){
    printf("\n\nCustomer %d", i + 1);
    printf("\nName: %s", v_clientes[i].name);
    printf("Balances: ");
    for(j = 0; j < SALDOS_LEN; j++){
      printf("%.2f\t", v_clientes[i].vsaldos[j]);
    }
  }
  return;
}

void MostrarClientesMedios(T_CLIENTE_MEDIO *v_saldos_medios, int num_saldos_medios){
  int i;
  for(i = 0; i < num_saldos_medios; i++){
    printf("\n\nCustomer %d", i + 1);
    printf("\nName: %s", v_saldos_medios[i].name);
    printf("Average balance: ");
    printf("%.2f\t", v_saldos_medios[i].saldo_medio);
  }
  return;
}

float BalanceMedio(T_CLIENTE_SALDO cliente){
  float sum = 0;
  int j;
  for(j = 0; j < SALDOS_LEN; j++){
    sum += cliente.vsaldos[j];
  }
  return sum / SALDOS_LEN;
}
