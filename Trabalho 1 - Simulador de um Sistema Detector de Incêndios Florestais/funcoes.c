#include "funcoes.h"

int qtd_m = 0, cnt_m = 0, time_m = 0, bomb = 0;


void preencher_matriz(char floresta[MAX][MAX]){ //preenche a matriz colocando os Ts em suas devidas posições
	int count_i = 1, count_j = 1, i, j, k = 0;
	
	char count = 1;
	for(i = 0; i < MAX; i++){
		for(j = 0; j < MAX; j++){
			if(count_i == 2 && count_j == 2){//Coloca o t quando os contadores i e j forem iguais a 2
				floresta[i][j] = 'T';
				count++;
				count_j = 0;
				dado[k].x = i; //salva na struct de cada thread sua posição de origem
				dado[k].y = j;
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
  for(i = 0; i < 100; i++){
   pthread_create(&lista_threads[i], NULL, identificar, NULL);//Cria o vetor de threads
  }
}

void *imprimir_matriz(void *arg){
	char buff[100];
	int i, j;
	while(1){
		sleep(1);
		system("clear");
		time_t now = time (0);
		strftime (buff, 100, "%H:%M:%S", localtime (&now));//Guarda a string hora na variável buff
		for(i = 0; i < 30; i++){//identa as linhas para os numeros meores que 10 terem um 0 antes
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
			for(j = 0; j < MAX; j++){//identa as colunas para os numeros meores que 10 terem um 0 antes
				if(j == 0){
					if (i <= 9){
						printf("0%d ",i);
					}
					else{
						printf("%d ",i);
					}
					
				}
				if(floresta[i][j] == '#'){//Quando vê # coloca @ no mapa
          printf(" @ ");
          bomb ++;
        }
        else{
          printf(" %c ", (floresta)[i][j]);
        }
			}
			printf("\n");
		}
		printf ("%s\n", buff);//Imprime o horário em baixo do mapa
		for(i = cnt_m; i < qtd_m; i++){
			printf("Thread %d foi destruida!!\n", threads_mortas[i]);//imprime a thread que morreu
			time_m++;
			if(time_m == 3){//Faz com que ela fique 3s no mapa
				cnt_m++;
				time_m = 0;
			}
		}
	}

}

void *incendio(void *arg)
{
	char (*floresta)[MAX][MAX] = arg;
	int num;
	while(1)
  {
		sleep(3);
		int i = rand() % MAX;//gera um valor de i e j aleatório
		int j = rand() % MAX;
		if ((*floresta)[i][j] == 'T'){//Se for thread ela mata a thread
			num = (10 * (((i + 2)/3) - 1)) + ((j + 2)/3);
      dado[num - 1].morta = 1;
			(*floresta)[i][j] = 'X';
			threads_mortas[qtd_m] = num;
			qtd_m++;
      fptr = fopen("incendios.log.txt", "a"); 
      fprintf(fptr, "Thread %d morreu\n", num);
      fclose(fptr);
		}
		else{
			(*floresta)[i][j] = '@';//Coloca @ no lugar do incêndio
		}
		
		printf("\n");
	}
}


void *identificar()
{
  int i, j, t, num;
  char buff[100];
  while(1){
    time_t now = time (0);
    strftime (buff, 100, "%H:%M:%S", localtime (&now));//Guarda a string hora na variável buff
    for(t = 0; t < 100; t++){
      for(i = (dado[t].x) - 1; i <= (dado[t].x) + 1; i++){
        for(j = (dado[t].y) - 1; j <= (dado[t].y) + 1; j++){
          if(floresta[i][j] == '@' && dado[t].condicional == 0 && dado[t].morta == 0){//Se ela não tiver dado armazedado internamente, não estiver morta e tiver achado um icendio
            floresta[i][j] = '#';                                                        //ela armazena os dados na sua struct
            num = (10 * ((((dado[t].x) + 2)/3) - 1)) + (((dado[t].y) + 2)/3);
            dado[t].id = num;
            dado[t].incendio_x = i;
            dado[t].incendio_y = j;
            dado[t].condicional = 1;
            strcpy(dado[t].hora, buff);
            if(dado[t].x != 1 && dado[t].x != 28 && dado[t].y != 1 && dado[t].y != 28){//se a thread não estiver na borda ela passa para as outras threads ao redor
              dado[t].condicional = 0;//limpa sua condicional para receber mais dados
              passagem(t, num-2, num, num + 9, num - 11);//as quatro threads ao redor
            }
          }
        }
      }
    }
  sleep(1);//Espera 1s para fazer a verificação conforme o trabalho pede
  }
}

void passagem(int atual, int a, int b, int c, int d){//passagem por forma recursiva
  int num, env_x, env_y;
  env_x = dado[atual].x;
  env_y = dado[atual].y;
  dado[atual].envio_x = 100;//valor colocado para que a thread atual(a que enviou para as vizinhas, após o envio esteja livre para receber dados de outra thread)
  dado[atual].envio_y = 100;
  if((dado[a].condicional == 0) && (dado[a].morta == 0) && (dado[a].envio_x != dado[atual].x) && (dado[a].envio_y != dado[atual].y) && floresta[dado[atual].incendio_x][dado[atual].incendio_y] == '#'){
    num = (10 * ((((dado[a].x) + 2)/3) - 1)) + (((dado[a].y) + 2)/3);
    dado[a].id = dado[atual].id;
    dado[a].incendio_x = dado[atual].incendio_x;
    dado[a].incendio_y = dado[atual].incendio_y;
    strcpy(dado[num-1].hora,dado[atual].hora);
    dado[a].envio_x = env_x;
    dado[a].envio_y = env_y;
    dado[a].condicional = 1;
    if(dado[a].x != 1 && dado[a].x != 28 && dado[a].y != 1 && dado[a].y != 28){
      dado[a].condicional = 0;
      passagem(a, num - 2, num, num + 9, num - 11);
    }
  }
  if(dado[b].condicional == 0 && dado[b].morta == 0 && dado[b].envio_x != dado[atual].x && dado[b].envio_y != dado[atual].y && floresta[dado[atual].incendio_x][dado[atual].incendio_y] == '#'){
    num = (10 * ((((dado[b].x) + 2)/3) - 1)) + (((dado[b].y) + 2)/3);
    dado[b].id = dado[atual].id;
    dado[b].incendio_x = dado[atual].incendio_x;
    dado[b].incendio_y = dado[atual].incendio_y;
    strcpy(dado[b].hora,dado[atual].hora);
    dado[b].envio_x = env_x;
    dado[b].envio_y = env_y;
    dado[b].condicional = 1;
    if(dado[b].x != 1 && dado[b].x != 28 && dado[b].y != 1 && dado[b].y != 28){
      dado[b].condicional = 0;
      passagem(b, num - 2, num, num + 9, num - 11);
    }
  }
  if(dado[c].condicional == 0 && dado[c].morta == 0 && dado[c].envio_x != dado[atual].x && dado[c].envio_y != dado[atual].y && floresta[dado[atual].incendio_x][dado[atual].incendio_y] == '#'){
    num = (10 * ((((dado[c].x) + 2)/3) - 1)) + (((dado[c].y) + 2)/3);
    dado[c].id = dado[atual].id;
    dado[c].incendio_x = dado[atual].incendio_x;
    dado[c].incendio_y = dado[atual].incendio_y;
    strcpy(dado[c].hora,dado[atual].hora);
    dado[c].envio_x = env_x;
    dado[c].envio_y = env_y;
    dado[c].condicional = 1;
    if(dado[c].x != 1 && dado[c].x != 28 && dado[c].y != 1 && dado[c].y != 28){
      dado[c].condicional = 0;
      passagem(c, num - 2, num, num + 9, num - 11);
    }
  }
  if(dado[d].condicional == 0 && dado[d].morta == 0 && dado[d].envio_x != dado[atual].x && dado[d].envio_y != dado[atual].y && floresta[dado[atual].incendio_x][dado[atual].incendio_y] == '#'){
    num = (10 * ((((dado[d].x) + 2)/3) - 1)) + (((dado[d].y) + 2)/3);
    dado[d].id = dado[atual].id;
    dado[d].incendio_x = dado[atual].incendio_x;
    dado[d].incendio_y = dado[atual].incendio_y;
    strcpy(dado[num-1].hora,dado[atual].hora);
    dado[d].envio_x = env_x;
    dado[d].envio_y = env_y;
    dado[d].condicional = 1;
    if(dado[d].x != 1 && dado[d].x != 28 && dado[d].y != 1 && dado[d].y != 28){
      dado[d].condicional = 0;
      passagem(d, num - 2, num, num + 9, num - 11);
    }
  }
}


void *thread_central()//faz a verificação constantemente para que qualquer thread da borda que identificou o icendio possa chamar bombeiro
{
  int i, j, num;
  while(1)
  { 
    for(i = 1; i < 29; i += 27){
      for(j = 1; j < 29; j += 3){
        num = (10 * (((i + 2)/3) - 1)) + ((j + 2)/3);
        if(floresta[dado[num - 1].incendio_x][dado[num - 1].incendio_y] == '#' && dado[num - 1].morta == 0 && dado[num - 1].condicional == 1){
          fptr = fopen("incendios.log.txt", "a"); 
          fprintf(fptr, "A thread %d detectou um incendio na posicao [%d][%d] as %s\n", dado[num - 1].id, dado[num - 1].incendio_x, dado[num - 1].incendio_y, dado[num - 1].hora);
          fclose(fptr);//escreve mendsagem antes de chamar bmbeiro
          bombeiro(dado[num - 1].incendio_x, dado[num - 1].incendio_y);
          }
          dado[num - 1].condicional = 0;
          dado[num - 1].envio_x = 100;
          dado[num - 1].envio_y = 100;
      }

    }
    for(j = 1; j < 29; j += 27){
      for(i = 1; i < 29; i += 3){
        num = (10 * (((i + 2)/3) - 1)) + ((j + 2)/3);
        if(floresta[dado[num - 1].incendio_x][dado[num - 1].incendio_y] == '#' && dado[num - 1].morta == 0 && dado[num - 1].condicional == 1){
          
          fptr = fopen("incendios.log.txt", "a"); 
          fprintf(fptr, "A thread %d detectou um incendio na posicao [%d][%d] as %s\n", dado[num - 1].id, dado[num - 1].incendio_x, dado[num - 1].incendio_y, dado[num - 1].hora);
          fclose(fptr);
          
          bombeiro(dado[num - 1].incendio_x, dado[num - 1].incendio_y);        
        }
        dado[num - 1].condicional = 0;
        dado[num - 1].envio_x = 100;
        dado[num - 1].envio_y = 100;
      }
    }
  }
}

void bombeiro(int x, int y)
{
    fptr = fopen("incendios.log.txt", "a"); 
    fprintf(fptr, "Bombeiro apagou o incendio na posicao [%d][%d]\n", x, y);
    fclose(fptr);
    floresta[x][y] = '-' ;
}