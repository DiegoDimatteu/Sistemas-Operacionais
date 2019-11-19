#ifndef FUNCOES_H_
#define FUNCOES_H_

//Bibliotecas utilizadas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define MAX 30//Tamanho máximo para a matriz floresta

char floresta[MAX][MAX], threads_mortas[100];
pthread_t mapa, queimada, central, lista_threads[100];

FILE *fptr;//Arquivo para armazenar os logs

//Struct para guardar as informações das threads
typedef struct dados{
	int incendio_x, incendio_y, id, envio_x, envio_y;
	int x, y, morta, condicional;
  	char hora[100];
}dados;

dados dado[100];//Vetor de dados para cada uma das 100 threads

//Headers das funções
void preencher_matriz(char floresta[MAX][MAX]);
void *imprimir_matriz(void *arg);
void *incendio(void *arg);
void *identificar();
void passagem(int atual, int a, int b, int c, int d);
void *thread_central();
void bombeiro(int x, int y);

#endif
