#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

struct nodefila
{
    char *mensagens[100];
    int coord_x, coord_y;
    struct nodefila* prox;
};
typedef struct nodefila ndfila;

struct fila
{
    ndfila* ini;
    ndfila* fim;
};
typedef struct fila Fila;


Fila* cria_fila();
int vazia(Fila* f);
void insere(Fila* f, char *mensagens, int i, int j);
char* retira(Fila* f);
void libera(Fila* f);





#endif // FILA_H_INCLUDED
