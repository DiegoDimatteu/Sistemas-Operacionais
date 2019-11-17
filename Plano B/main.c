#include "funcoes.h"

int main(){
  int i;
  for(i = 0; i < 101; i++){
    dado[i].condicional = 0;
    dado[i].morta = 0;
  }
	fptr = fopen("incendios.log.txt", "w"); 
	fclose(fptr);
	srand(time(NULL));
	int k;

	preencher_matriz(floresta);
	pthread_create(&mapa, NULL, imprimir_matriz, NULL);
	pthread_create(&queimada, NULL, incendio, &floresta);
  	pthread_create(&central, NULL, thread_central,NULL);

	pthread_join(mapa, NULL);
 
}