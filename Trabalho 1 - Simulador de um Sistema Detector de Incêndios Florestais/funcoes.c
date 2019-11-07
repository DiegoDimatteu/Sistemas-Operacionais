#include "funcoes.h"


void preencher_matriz(char floresta[MAX][MAX]){
	int count_i = 1, count_j = 1, i, j;
	char count = 1;
	for(i = 0; i < MAX; i++){
		for(j = 0; j < MAX; j++){
			if(count_i == 2 && count_j == 2){
				floresta[i][j] = 'T';
				count++;
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

void *imprimir_matriz(void *arg){
	char (*floresta)[MAX][MAX] = arg;
	int i, j;
	while(1){
		sleep(1);
		system("clear");
		for(i = 0; i < MAX; i++){
			for(j = 0; j < MAX; j++){
				printf("%c ", (*floresta)[i][j]);
			}
			printf("\n");
		}
	}

}

void *incendio(void *arg){
	char (*floresta)[MAX][MAX] = arg;
	while(1){
		sleep(3);
		int i = rand() % MAX;
		int j = rand() % MAX;
		(*floresta)[i][j] = '@';
		printf("\n");
	}
}

//**************
/*typedef struct informacoes{
	int fogo = 0;
	int posicao_i, posicao_j;
};
*/
