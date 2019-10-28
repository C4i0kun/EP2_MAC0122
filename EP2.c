#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHOMAXIMO 100

typedef struct _RegPilha {
    char dado[TAMANHOMAXIMO];
    struct _RegPilha *prox;
} RegPilha;

typedef RegPilha * Pilha;

RegPilha* AlocaRegPilha() {
    RegPilha *p = (RegPilha*) calloc(1, sizeof(RegPilha));
    if (p == NULL) {
        exit(-1);
    }

    strcpy(p->dado, "Início da Pilha");

    return p;
}

Pilha CriaPilha() {
    Pilha p = AlocaRegPilha();
    p->prox = NULL;
    return p;
}

void AdicionaNaPilha(Pilha p, char entrada[]) {
    RegPilha *q = AlocaRegPilha();

    strcpy(q->dado, entrada);
    q->prox = p->prox;
    p->prox = q;
}

char* RemoverDaPilha(Pilha p) {
    RegPilha *q = p->prox;
    p->prox = q->prox;

    static char saida[TAMANHOMAXIMO];
    strcpy(saida, q->dado);

    free(q);
    return saida;
}

void PrintaPilha(Pilha p) {
    printf("%s\n", p->dado);
    if (p->prox == NULL) {
        return;
    }
    PrintaPilha(p->prox);
}

void LiberaPilha(Pilha p) {
    if (p->prox != NULL) {
        LiberaPilha(p->prox);
    }
    free(p);
}



int main() {
    Pilha pilha = CriaPilha();
    AdicionaNaPilha(pilha, "oi");
    AdicionaNaPilha(pilha, "como");
    AdicionaNaPilha(pilha, "vai");

    PrintaPilha(pilha);

    printf("\n");
    printf("%s\n", RemoverDaPilha(pilha));
    printf("\n");

    PrintaPilha(pilha);
    printf("\nPilha deletada \n");
    LiberaPilha(pilha);
    PrintaPilha(pilha);


    return 0;
}