#include "funcoes.h"

int main(){
  int i;
  for(i = 0; i < 100; i++){//Inicializa as variáveis da struct dado
    dado[i].condicional = 0;
    dado[i].morta = 0;
    dado[i].envio_x = 100;
    dado[i].envio_y = 100;
  }
  fptr = fopen("incendios.log.txt", "w");//Garante que toda vez o arquivo vai estar em branco quando roda o programa novamente
  fclose(fptr);
  srand(time(NULL));

  preencher_matriz(floresta);//Cria a matriz
  pthread_create(&mapa, NULL, imprimir_matriz, NULL);//Thread que imprime a matriz a cada segundo
  pthread_create(&queimada, NULL, incendio, &floresta);//Thread que cria os incêdios
  pthread_create(&central, NULL, thread_central,NULL);//Tread central que escreve a mensagem no arquivo e chama o bombeiro

  pthread_join(mapa, NULL);//Espera a thread mapa finalizar
}