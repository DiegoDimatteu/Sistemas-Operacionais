#ifndef FUNCOES_H_
#define FUNCOES_H_


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 30

char floresta[MAX][MAX];

void preencher_matriz(char floresta[MAX][MAX]);
void *imprimir_matriz(void *arg);
void *incendio(void *arg);


#endif