#include "funcoes.h"

int main(){
  int i;
  for(i = 0; i < 101; i++){
    dado[i].condicional = 0;
    dado[i].morta = 0;
    dado[i].envio_x = 100;
    dado[i].envio_y = 100;
  }
	fptr = fopen("incendios.log.txt", "w"); 
	fclose(fptr);
	srand(time(NULL));
	


	preencher_matriz(floresta);
	pthread_create(&mapa, NULL, imprimir_matriz, NULL);
	pthread_create(&queimada, NULL, incendio, &floresta);
  pthread_create(&central, NULL, thread_central,NULL);

	pthread_join(mapa, NULL);


}