/*
  Productor - Consumidor, 1 a 1 sin mecanismos de comunicación o
  sincronización Solo se pueden usar ciclos vacíos o sleep para sincronizar y
  archivos solo para comunicación, cada proceso tiene su
  buffer
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void set_estado(int dat) {
  FILE *est = fopen("Producer_Consumer/Files/estado.txt", "r+");
  rewind(est);
  if (dat == 0) {
    fprintf(est, "0"); // 0 estado
  } else if (dat == 1) {
    fprintf(est, "1"); // 1 estado
  } else if (dat == 2) {
    fprintf(est, "2"); // 2 estado
  } else {
    fprintf(est, "3"); // 3 estado
  }
  fclose(est);
}

void set_producto(int producto) {
  FILE *vent = fopen("Producer_Consumer/Files/datos.txt", "r+");
  char temp[64];

  fprintf(vent, "%d\n", producto);

  fclose(vent);
}

int get_estado() {
  FILE *est = fopen("Producer_Consumer/Files/estado.txt", "r");
  int num;
  if (fscanf(est, "%d", &num) == 1) {
    if (num == 0) {
      fclose(est);
      return 0;
    } else if (num == 1) {
      fclose(est);
      return 1;
    } else if (num == 2) {
      fclose(est);
      return 2;
    } else if (num == 3) {
      fclose(est);
      return 3;
    }
  }
  fclose(est);
  return -1;
}

int get_producto() {
  FILE *vent = fopen("Producer_Consumer/Files/datos.txt", "r");
  char temp[64];
  int num;

  if (fscanf(vent, "%d", &num) == 1) {
    fclose(vent);
    return num;
  }

  fclose(vent);
  return -1;
}

int main() {
  FILE *dat = fopen("Producer_Consumer/Files/datos.txt", "w"),
       *est = fopen("Producer_Consumer/Files/estado.txt", "w");
  int i, tam;

  if (dat == NULL || est == NULL) {
    printf("Error al abrir archivo\n");
    exit(0);
  }

  fprintf(dat, "0");
  fprintf(est, "0");
  fclose(dat);
  fclose(est);

  printf("Escriba el tamaño del almacén: \n");
  scanf("%d", &tam);

  printf("Escriba el número de iteraciones: \n");
  scanf("%d", &i);

  int pid = fork();

  if (pid < 0) {
    printf("Error al crear proceso\n");
  }

  if (pid > 0) { // Productor

    int ap = 0, prod = 0, buffer[tam];
    while (prod != i) {
      while (get_estado() == 1) {
        sleep(1);
      }

      while (get_estado() == 2) {
        usleep(1 * 1000);
      }

      buffer[ap++] = prod;
      set_producto(prod++);

      if (prod % tam == 0) {
        ap = 0;
        printf("El productor produjo: %d productos\n", prod);
        set_estado(1);
      } else {
        set_estado(2);
      }
    }

  } else { // Consumidor

    int compras = 0, ap = 0, *buffer = malloc(i * sizeof(int));
    while (compras != i) {
      while (get_estado() == 0) {
        sleep(1);
      }

      while (get_estado() == 3) {
        usleep(1 * 1000);
      }

      buffer[ap++] = get_producto();
      compras++;

      if (compras % tam == 0) {
        printf("El consumidor compro: %d productos\n", compras);
        set_estado(0);
      } else {
        set_estado(3);
      }
    }
    free(buffer);
  }
  return 0;
}
