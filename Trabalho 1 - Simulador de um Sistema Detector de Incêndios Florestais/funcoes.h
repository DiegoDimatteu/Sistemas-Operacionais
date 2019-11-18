#ifndef FUNCOES_H_
#define FUNCOES_H_


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

#define MAX 30

char floresta[MAX][MAX], threads_mortas[100];
pthread_t mapa, queimada, central, lista_threads[100];
/*pthread_cond_t soneca = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int done = 1;*/

FILE *fptr;

typedef struct dados{
	int incendio_x, incendio_y, id, envio_x, envio_y;
	int x, y, morta, condicional;
  	char hora[100];
  //char mensagem[4][100];
}dados;

dados dado[100];



void preencher_matriz(char floresta[MAX][MAX]);
void *imprimir_matriz(void *arg);
void *incendio(void *arg);
void *identificar();
void passagem(int atual, int a, int b, int c, int d);
void *thread_central();
void bombeiro(int x, int y);

#endif