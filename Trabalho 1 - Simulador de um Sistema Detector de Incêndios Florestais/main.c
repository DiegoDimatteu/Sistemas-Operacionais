#include "funcoes.h"

int main(){
	srand(time(NULL));
	pthread_t t1, t2;
	int i = 0, j;
	
	preencher_matriz(floresta);
	//imprimir_matriz(floresta);
	printf("Holla!\n");
	pthread_create(&t1, NULL, imprimir_matriz, &floresta);
	pthread_create(&t2, NULL, incendio, &floresta);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	/*while(i < 30){
		incendio(floresta);
		i++;
	}*/
	

}