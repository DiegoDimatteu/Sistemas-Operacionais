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
				printf("   0%d ", i);
			}
			else{
				if (i <= 9){
					printf("0%d ", i);
				}
				else{
					printf("%d ", i);
				}
			}
			
		}
		printf("\n");
		for(i = 0; i < MAX; i++){
			for(j = 0; j < MAX; j++){
				if(j == 0){
					if (i <= 9){
						printf("0%d ",i);
					}
					else{
						printf("%d ",i);
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
	dados *dado = args;
	int i, j;
  char buff[100], mensagem[100];
  while(1){
    time_t now = time (0);
    strftime (buff, 100, "%H:%M:%S", localtime (&now));
    for(i = (dado -> x) - 1; i <= (dado -> x) + 1; i++){
      for(j = (dado -> y) - 1; j <= (dado -> y) + 1; j++){
        if(floresta[i][j] == '@' && dado -> condicional == 0 && dado -> morta == 0){
				  floresta[i][j] = '#';
			    dado -> id = (10 * ((((dado -> x) + 2)/3) - 1)) + (((dado -> y) + 2)/3);
			    dado -> incendio_x = i;
			    dado -> incendio_y = j;
			    dado -> condicional = 1;
          strcpy(dado -> hora, buff);
			    /**if(dado -> x = 1 || dado -> x = 28 || dado -> y = 1 || dado -> y = 28){ //Se a condicional for aceita significa que a Thread está na borda
            
			    }*/
        }
    }
  }
  sleep(1);
  }
}

void *incendio(void *arg)
{
	char (*floresta)[MAX][MAX] = arg;
	int num;
	while(1)
  {
		sleep(3);
		int i = rand() % MAX;
		int j = rand() % MAX;
    //sem_wait(&mutex);
		if ((*floresta)[i][j] == 'T'){
			num = (10 * (((i + 2)/3) - 1)) + ((j + 2)/3);
      dado[num - 1].morta = 1;
			(*floresta)[i][j] = 'X';
			threads_mortas[qtd_m] = num;
			qtd_m++;
		}
		else{
			(*floresta)[i][j] = '@';
		}
		
		printf("\n");
    //sem_post(&mutex);
	}
}



void *thread_central()
{
  int i, num;
  while(1)
  {  
    for(i = 0; i < 100; i++){
      //for(j = 0; j < 30; j++){
        //if(x == 1 || x == 28 || y == 1 || y == 28){
          num = i + 1;
          if(floresta[dado[num - 1].incendio_x][dado[num - 1].incendio_y] == '#' && dado[num - 1].morta == 0){
            fptr = fopen("incendios.log.txt", "a"); 
            fprintf(fptr, "A thread %d detectou um incendio na posicao [%d][%d] as %s\n", dado[num - 1].id, dado[num - 1].incendio_x, dado[num - 1].incendio_y, dado[num - 1].hora);
            fclose(fptr);
            dado[num - 1].condicional = 0;
            bombeiro(dado[num - 1].incendio_x, dado[num - 1].incendio_y);
          }
        //}
      //}
    }
  }
}

void bombeiro(int x, int y)
{
  sleep(2);
  floresta[x][y] = '-' ;
}