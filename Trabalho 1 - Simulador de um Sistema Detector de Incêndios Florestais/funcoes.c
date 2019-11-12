#include "funcoes.h"

int qtd_m = 0, cnt_m = 0;

typedef struct dados{
	int incendio_x, incendio_y, id;
	int x,y;
}dados;

void preencher_matriz(char floresta[MAX][MAX]){
	int count_i = 1, count_j = 1, i, j, k = 0;
	dados dado[100];
	char count = 1;
	for(i = 0; i < MAX; i++){
		for(j = 0; j < MAX; j++){
			if(count_i == 2 && count_j == 2){
				floresta[i][j] = 'T';
				count++;
				count_j = 0;
				dado[k].x = i;
				dado[k].y = j;
				/*pthread_create(&lista_threads[k], NULL, identificar, &dado[k]);
				pthread_join(lista_threads[k], NULL);*/
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
	char buff[100];
	int i, j;
	while(1){
		sleep(1);
		system("clear");
		time_t now = time (0);
		strftime (buff, 100, "%H:%M:%S", localtime (&now));
		for(i = 0; i < 30; i++){
			if(i == 0){
				printf("   0%d ", i + 1);
			}
			else{
				if (i < 9){
					printf("0%d ", i + 1);
				}
				else{
					printf("%d ", i + 1);
				}
			}
			
		}
		printf("\n");
		for(i = 0; i < MAX; i++){
			for(j = 0; j < MAX; j++){
				if(j == 0){
					if (i < 9){
						printf("0%d ",i + 1);
					}
					else{
						printf("%d ",i + 1);
					}
					
				}
				printf(" %c ", (*floresta)[i][j]);
			}
			printf("\n");
		}
		printf ("%s\n", buff);
		for(i = cnt_m; i < qtd_m; i++){
			printf("Thread %d foi destruida!!\n", threads_mortas[i]);
			cnt_m++;
		}
	}

}

/*void *identificar(void *args)
 {
	dados *dado = args;
	int i, j;
	for(i = (dado -> x) - 1; i <= (dado -> x) + 1; i++){
		for(j = (dado -> y) - 1; j <= (dado -> y) + 1; j++){
			if(i != dado -> x && j != dado -> y){
				fptr = fopen("incendios.log.txt", "a"); 
				fprintf(fptr, "floresta[i][j] == %c\n", floresta[i][j]);
				fclose(fptr);
				if(floresta[i][j] == '@'){
					fptr = fopen("incendios.log.txt", "a"); 
					fprintf(fptr, "Incandio -> X = %d || Y = %d\n", i, j);
					fclose(fptr);
				}
			}
		}
	}
}*/
/*void *identificar(void *args){
	dados *dado = args;
	int i, j;
	for(i = dados -> x - 1; i <= dados -> x + 1; i++){
		for(j = dados -> j - 1; i <= dados -> j + 1; i++){
			if(i != dados -> x && j != dados -> y){
				if(floresta[i][j] == '@'){
					fptr = fopen("incendios.log.txt", "a"); 
					fprintf(fptr, "X = %d || Y = %d\n", dado -> x, dado -> y);
					fclose(fptr);
					(+2/3)
				}
			}
		}
	}
	fptr = fopen("incendios.log.txt", "a"); 
	fprintf(fptr, "X = %d || Y = %d\n", dado -> x, dado -> y);
	fclose(fptr);

}*/

void *incendio(void *arg){
	char (*floresta)[MAX][MAX] = arg;
	int id;
	while(1){
		sleep(3);
		int i = rand() % MAX;
		int j = rand() % MAX;
		if ((*floresta)[i][j] == 'T'){
			id = (10 * (((i + 2)/3) - 1)) + ((j + 2)/3);
			(*floresta)[i][j] = 'K';
			threads_mortas[qtd_m] = id;
			qtd_m++;
		}
		else{
			(*floresta)[i][j] = '@';
		}
		
		printf("\n");
	}
}


