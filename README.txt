Alunos:
Caio Mariano Borges Silva
Diego Gabriel Prata Juliano Dimatteu Telles
Ygor Henrique Germano Silva

Para rodar o programa, abra o terminal, entre na pasta do trabalho, após isso digite "gcc main.c funcoes.c -o p -pthread" e aperte enter. Agora digite "./p" e aperte enter.

Funções.h
	Contém as bibliotecas usadas, as variáveis globais, as threads usadas e a struct dados com os dados das threads sensores. 

função main:
	Inicializa os dados de todas as threads sensores e cria as threads necessárias

Função preencher_matriz:
	Cria a matriz floresta com as numerações de linha e coluna, os '-' e os 'T' no lugar certo. Tambem cria a lista de threads sensores.

Função imprimir_matriz:
	Uma thread que mostra na tela, a cada segundo, a matriz floresta com o horário local.

Função incendio:
	Uma thread que gera, em um elemento randomico da matriz, um incêndio a cada três segundos, e substitui o '-' por um '@' na matriz floresta. Se esse elemento for a posição de uma thread, ele substitui o 'T' por um 'X'.

Função 	identificar:
	Existem 100 threads do tipo identificar, elas verificam , a cada segundo, se os elementos em volta delas está pegando fogo. Se estiver, substitui o '@' na matriz floresta por '#', para tratar o erro do fogo ser idêntificado várias vezes, e manda as devidas informações para a posição da struct dado correspondente à thread.

Função passagem:
	Função recursiva para mandar as informações do incêndio para as threads visinhas à thread que detectou o incêndio.

Função thread_central:
	Thread central que escreve os alertas de incêndio no incendios.log e chama o bombeiro para apagar o fogo.

Função bombeiro:
	Função que após ser chamada pela thread_central, apaga o fogo da matriz floresta substituindo o '#' por '-'.


PS:
	Na pasta do trabalho existe uma pasta chamada 'Plano B', é o mesmo programa mas a thread sensor identifica o incêndio e manda para a central de maneira direta. 
