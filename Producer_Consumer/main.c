/*
  Productor - Consumidor, 1 a 1 sin mecanismos de comunicación o
  sincronización Solo se pueden usar ciclos vacíos o sleep para sincronizar y
  archivos solo para comunicación, cada proceso tiene su
  buffer
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void set_estado(int op) {
  FILE *est = fopen("Producer_Consumer/Files/estado.txt", "w");
  if (op == 0) {
    fprintf(est, "0"); // 0 vacío
  } else if (op == 1) {
    fprintf(est, "1"); // 1 lleno
  } else if (op == 2) {
    fprintf(est, "2"); // 2 sincronización (P)
  } 
  fclose(est);
}

void set_producto(int producto) {
  FILE *vent = fopen("Producer_Consumer/Files/datos.txt", "w");
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
    }
  }
  fclose(est);
  return -1;
}

int get_producto() {
  FILE *vent = fopen("Producer_Consumer/Files/datos.txt", "r");
  int num;

  if (fscanf(vent, "%d", &num) == 1) {
    fclose(vent);
    return num;
  }

  fclose(vent);
  return -1;
}

int vaciar_buffer(int buffer[], int *ap, int tam) {
  while (get_estado() == 1) {
    sleep(1);
  }

  while (get_estado() == 2) {
    usleep(1 * 1000);
  }

  set_producto(buffer[(*ap)++]);

  if (*ap == tam) {
    *ap = 0;
    set_estado(1);
    return 1;
  } else {
    set_estado(2);
    return 0;
  }
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

  if (i % tam != 0) {
    i = (i / tam) * tam;
  }

  int pid = fork();

  if (pid < 0) {
    printf("Error al crear proceso\n");
  }

  if (pid > 0) { // Productor

    int ap = 0, prod = 0, buffer[tam];
    while (prod <= i) {

      if (ap == tam) {
        ap = 0;
        while (vaciar_buffer(buffer, &ap, tam) == 0);
        printf("El productor produjo: %d productos\n", prod);
      }

      buffer[ap++] = prod++;
    }

  } else { // Consumidor

    int compras = 0, ap = 0, *buffer = malloc(i * sizeof(int));
    while (compras < i) {

      while (get_estado() == 0) {
        usleep(1 * 1000);
      }

      buffer[ap++] = get_producto();
      compras++;

      if (compras % tam == 0) {
        set_estado(0);
        printf("El consumidor compro: %d productos\n", compras);
      } else {
        set_estado(0);
      }
    }
    free(buffer);
  }
  return 0;
}
