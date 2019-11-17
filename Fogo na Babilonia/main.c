#include "funcoes.h"

int main(){
	fptr = fopen("incendios.log.txt", "w"); 
	fclose(fptr);
	srand(time(NULL));
	int k;

	preencher_matriz(floresta);
	pthread_create(&mapa, NULL, imprimir_matriz, NULL);
	pthread_create(&queimada, NULL, incendio, &floresta);
  pthread_create(&central, NULL, thread_central,NULL);

	pthread_join(mapa, NULL);
  //printf("fasfasfasafsfasagdfgafshsfajfhsjasf");
	//pthread_join(queimada, NULL);
  //pthread_join(central, NULL);
  
  //erro aqui
  //for(k=0;k<100;k++){
  //  pthread_join(lista_threads[k], NULL);
  //}

}