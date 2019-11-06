#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX 30

void preencher_matriz(char floresta[MAX][MAX]){
	int count_i = 1, count_j = 1, i, j;
	for(i = 0; i < MAX; i++){
		for(j = 0; j < MAX; j++){
			if(count_i == 2 && count_j == 2){
				floresta[i][j] = 'T';
				count_j = 0;
			}
			else{
				floresta[i][j] = '-';
				if (count_j == 2){
					count_j = 0;
				}
				else{
					count_j++;
				}
			}

		}
		if(count_i == 2){
			count_i = 0;
		}
		else{
			count_i++;
		}
	}
}

void imprimir_matriz(char floresta[MAX][MAX]){
	int i, j;
	for(i = 0; i < MAX; i++){
		for(j = 0; j < MAX; j++){
			printf("%c ", floresta[i][j]);
		}
		printf("\n");
	}

}

void incendio(char floresta[MAX][MAX]){
	srand(time(NULL));
	int i = rand() % MAX;
	//srand(time(NULL));
	int j = rand() % MAX;
	floresta[i][j] = '@';
	sleep(2);
	printf("\n");
	imprimir_matriz(floresta);

}

int main(){
	int i = 0, j;
	char floresta[MAX][MAX];
	preencher_matriz(floresta);
	imprimir_matriz(floresta);
	while(i < 30){
		incendio(floresta);
		i++;
	}
	

}