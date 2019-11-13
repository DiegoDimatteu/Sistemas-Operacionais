#include "fila.h"
#include "funcoes.h"

Fila* cria_fila()
{
    Fila* f = (Fila*)malloc(sizeof(Fila));
    if(f != NULL)
    {
      f->ini = f->fim = NULL;
    }
    return f;
}

int vazia(Fila* f)
{
    if(f->fim == NULL)
        return 1;
    else
        return 0;
}

void insere(Fila* f, char *mensagem, int i, int j)
{
    ndfila* n = (ndfila*)malloc(sizeof(ndfila*));
    strcpy(n->mensagens, mensagem);
    n->coord_x = i;
    n->coord_y = j;
    n->prox = NULL;
    if(f->fim != NULL)
        f->fim->prox = n;
    else
        f->ini = n;
    f->fim = n;
}

char* retira(Fila* f)
{
    ndfila* t;
    char *n;
    if(vazia(f))
    {
        printf("Lista Vazia!!\n");
        exit(0);
    }
    t = f->ini;
    n = t->mensagens;
    f->ini = t->prox;
    if(f->ini == NULL)
        f->fim = NULL;
    free(t);
    return n;
}

void libera(Fila* f)
{
    ndfila* q = f->ini;
    while(q!=NULL)
    {
        ndfila* t = q->prox;
        free(q);
        q = t;
    }
    free(f);
}
