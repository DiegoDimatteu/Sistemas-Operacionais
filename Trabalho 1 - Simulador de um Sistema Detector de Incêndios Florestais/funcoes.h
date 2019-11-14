#ifndef FUNCOES_H_
#define FUNCOES_H_


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 30

char floresta[MAX][MAX], threads_mortas[100];
pthread_t mapa, queimada, central, passagem, lista_threads[100];
FILE *fptr;

typedef struct dados{
	int incendio_x, incendio_y, id;
	int x, y, condicional = 0;
}dados;

dados dado[100];

void preencher_matriz(char floresta[MAX][MAX]);
void *imprimir_matriz(void *arg);
void *incendio(void *arg);
void *identificar(void *args);
void* thread_central();



#endif