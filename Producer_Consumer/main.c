/*
  Productor - Consumidor, 1 a 1 sin mecanismos de comunicación o
  sincronización Solo se pueden usar ciclos vacíos o sleep para sincronizar y
  archivos solo para comunicación (no almacenamiento)
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int get_linea(int op, int seek) {
  int num = -1, cont = 0;
  char buff[16];

  if (op == 0) {
    FILE *comp = fopen("Producer_Consumer/Files/compra.txt", "r");
    
    while (fgets(buff, sizeof(buff), comp) != NULL) {
      if (cont == seek) {
        num = fgetc(comp) - '0';
        seek = cont;
      }
      cont++;
    }

    fclose(comp);
    return num;
  } else {
    FILE *vent = fopen("Producer_Consumer/Files/venta.txt", "r");

    while (fgets(buff, sizeof(buff), vent) != NULL) {
      if (cont == seek) {
        num = fgetc(vent) - '0';
        seek = cont;
      }
      cont++;
    }

    fclose(vent);
    return num;
  }
}

int producir(int productos[], int *ap, int *ventas, int *seek, int tam) {
  FILE *vent = fopen("Producer_Consumer/Files/venta.txt", "a");
  int num = get_linea(0, *seek);

  if (num == 0) {
    (*ventas)++;
    productos[*ap] = 0;

    if (*ap != 0) {
      (*ap)--;
    }
  }

  productos[*ap] = 1;

  if (*ap == tam) {
    fclose(vent);
    return 1;
  } 

  fprintf(vent, "%d\n", productos[*ap]);
  (*ap)++; 

  fclose(vent);
  return 0;
}

int comprar(int *compras, int *seek) {
  FILE *comp = fopen("Producer_Consumer/Files/compra.txt", "a");
  int num = get_linea(1, *seek);

  if (num == 1) {
    (*compras)++;
    fprintf(comp, "%d\n", 0);
  } else {
    fclose(comp);
    return 1;
  }

  fclose(comp);
  return 0;
}

int main() {
  FILE *comp = fopen("Producer_Consumer/Files/compra.txt", "w"),
       *vent = fopen("Producer_Consumer/Files/venta.txt", "w");
  int prod, tam;

  if (comp == NULL || vent == NULL) {
    printf("Error al abrir archivo\n");
    exit(0);
  }

  fclose(comp);

  printf("Escriba el tamaño del almacén: \n");
  scanf("%d", &tam);

  printf("Escriba el número de productos: \n");
  scanf("%d", &prod);

  int pid = fork();

  if (pid > 0) { // Productor

    int productos[tam], ap = 0, ventas = 0, seek = 0;
    while (ventas != prod) {
      while (producir(productos, &ap, &ventas, &seek, tam) == 1) {
        sleep(1);
      }
    }
    printf("Ventas efectuadas: %d\n", ventas);

  } else { // Consumidor

    int compras = 0, seek = 0;
    while (compras != prod) {
      while (comprar(&compras, &seek) == 1) {
        sleep(1);
      }
    }
    printf("Compras efectuadas: %d\n", compras);
  }
  return 0;
}
