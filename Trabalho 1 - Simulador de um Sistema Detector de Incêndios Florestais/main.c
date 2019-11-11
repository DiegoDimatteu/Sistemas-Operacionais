#include "funcoes.h"

int main(){
	fptr = fopen("incendios.log.txt", "w"); 
	fclose(fptr);
	srand(time(NULL));
	pthread_t t1, t2;
	int i = 0, j;
	
	preencher_matriz(floresta);
	//imprimir_matriz(floresta);
	printf("Holla!\n");
	pthread_create(&mapa, NULL, imprimir_matriz, &floresta);
	pthread_create(&queimada, NULL, incendio, &floresta);

	pthread_join(mapa, NULL);
	pthread_join(queimada, NULL);
	
	/*while(i < 30){
		incendio(floresta);
		i++;
	}*/
	

}