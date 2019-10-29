#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHOMAXIMO 100

#define TRUE 1
#define FALSE 0

#define TAGABERTURA 1
#define TAGFECHAMENTO 0

#define TAG 1
#define PARAMETRO 0

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

char* UltimoDaPilha(Pilha p) {
    RegPilha *q = p->prox;
    
    static char saida[TAMANHOMAXIMO];
    strcpy(saida, q->dado);

    return saida;
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

int TipoDeTag(char caractere) {
    if (caractere == '/') {
        return TAGFECHAMENTO;
    } else {
        return TAGABERTURA;
    }
}

void GerenciamentoDePilha(Pilha p, char entrada[], int tipodetag, int linha){

} 

void XMLParaPilha(Pilha p, char arquivo[]) {
    FILE *fp;
    long int sizeoffile;
    int linha = 1;

    int abrechaves = FALSE;
    int natag = FALSE;
    int tipodetag = TAGABERTURA;
    int tipodeleitura = TAG;

    fp = fopen(arquivo, "r");
    if (fp == NULL) {
        printf("Erro de Leitura\n");
        exit(-1);
    }

    fseek(fp, 0, SEEK_END);
    sizeoffile = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char tag[TAMANHOMAXIMO];
    int posicao = 0;
    for(int i=0; i<sizeoffile; i++) {
        char caractere;
        fscanf(fp, "%c", &caractere);

        if (caractere == '\n') {
            linha++;
        }

        if (caractere == '<' && abrechaves == FALSE) {
            abrechaves = TRUE;
            continue;
        }
        
        if (abrechaves == TRUE) {
            tipodetag = TipoDeTag(caractere);
            abrechaves = FALSE;

            if (tipodetag == TAGFECHAMENTO) {
                natag = TRUE;
                tipodeleitura = TAG;
                continue;
            }

            natag = TRUE;
            tipodeleitura = TAG;
        }

        if (natag == TRUE && tipodeleitura == TAG) {
            if (caractere == ' ') {
                tipodeleitura = PARAMETRO;
            } else if (caractere == '>') {
                natag = FALSE;
                tag[posicao] = '\0';
                AdicionaNaPilha(p, tag);
                tag[0] = '\0';
                posicao = 0;
            } else {
                tag[posicao] = caractere;
                posicao++;
            }
            continue;
        }

        if (natag == TRUE && tipodeleitura == PARAMETRO) {
            if (caractere == '>') {
                natag = FALSE;
                tag[posicao] = '\0';
                AdicionaNaPilha(p, tag);
                tag[0] = '\0';
                posicao = 0;
            }
        }

    }

}

int main() {
    Pilha pilha = CriaPilha();
    char arquivo[TAMANHOMAXIMO];

    scanf("%s", arquivo);

    XMLParaPilha(pilha, arquivo);
    PrintaPilha(pilha);

    return 0;
}