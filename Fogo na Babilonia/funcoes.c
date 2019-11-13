#include "funcoes.h"

int qtd_m = 0, cnt_m = 0, time_m = 0;



void preencher_matriz(char floresta[MAX][MAX]){
	int count_i = 1, count_j = 1, i, j, k = 0;
	
	char count = 1;
	for(i = 0; i < MAX; i++){
		for(j = 0; j < MAX; j++){
			if(count_i == 2 && count_j == 2){
				floresta[i][j] = 'T';
				count++;
				count_j = 0;
				dado[k].x = i;
				dado[k].y = j;
				pthread_create(&lista_threads[k], NULL, identificar, &dado[k]);
				k++;
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
	//char (*floresta)[MAX][MAX] = arg;
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
				if(floresta[i][j] == '#'){
          printf(" @ ");
        }
        else{
          printf(" %c ", (floresta)[i][j]);
        }
			}
			printf("\n");
		}
		printf ("%s\n", buff);
		for(i = cnt_m; i < qtd_m; i++){
			printf("Thread %d foi destruida!!\n", threads_mortas[i]);
			time_m++;
			if(time_m == 3){
				cnt_m++;
				time_m = 0;
			}
		}
	}

}

void *identificar(void *args)
{
  int id;
	dados *dado = args;
	int i, j, c=0;
  char buff[100], mensagem[100];
  while(1){
    time_t now = time (0);
    strftime (buff, 100, "%H:%M:%S", localtime (&now));
    for(i = (dado -> x) - 1; i <= (dado -> x) + 1; i++){
      for(j = (dado -> y) - 1; j <= (dado -> y) + 1; j++){
        if(floresta[i][j] == '@'){
          floresta[i][j] = '#';
          id = (10 * (((i + 2)/3) - 1)) + ((j + 2)/3);
          sprintf(mensagem,"A thread %d detectou fogo na posição [%d][%d]. %s\n", id, j+1, i+1,buff);
          strcpy(dado->mensagem, mensagem);
        }
      }
    }
    sleep(1);
  }
}

void *incendio(void *arg)
{
	char (*floresta)[MAX][MAX] = arg;
	int id;
	while(1)
  {
		sleep(3);
		int i = rand() % MAX;
		int j = rand() % MAX;
    //sem_wait(&mutex);
		if ((*floresta)[i][j] == 'T'){
			id = (10 * (((i + 2)/3) - 1)) + ((j + 2)/3);
			(*floresta)[i][j] = 'X';
			threads_mortas[qtd_m] = id;
			qtd_m++;
		}
		else{
			(*floresta)[i][j] = '@';
		}
		
		printf("\n");
    //sem_post(&mutex);
	}
}

void bombeiro(int x, int y)
{
  sleep(2);
  floresta[x][y] = '-' ;
}

void* thread_central()
{
  int i;
  while(1)
  {
      for(i=0;i<100;i++){
        fptr = fopen("incendios.log.txt", "a"); 
        fprintf(fptr, "%s", dado[i].mensagem);
        fclose(fptr);
        strcpy(dado[i].mensagem, "");
        dado
      }
    //bombeiro(mensagens->coord_x, mensagens->coord_y);
    //retira(mensagens);
  }
}
