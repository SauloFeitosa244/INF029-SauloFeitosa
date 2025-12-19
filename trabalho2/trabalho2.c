#include <stdio.h>
#include <stdlib.h>
#include "trabalho2.h"

#define TAM 10

typedef struct {
    int *dados;
    int tamanho;
    int qtd;
} EstruturaAux;

EstruturaAux estruturas[TAM];

int PosicaoValida(int posicao) {
    if (posicao < 1 || posicao > 10)
        return POSICAO_INVALIDA;
    return SUCESSO;
}

void inicializar() {
    for (int i = 0; i < TAM; i++) {
        estruturas[i].dados = NULL;
        estruturas[i].tamanho = 0;
        estruturas[i].qtd = 0;
    }
}

void finalizar() {
    for (int i = 0; i < TAM; i++) {
        free(estruturas[i].dados);
        estruturas[i].dados = NULL;
    }
}

int criarEstruturaAuxiliar(int posicao, int tamanho) {
    if (PosicaoValida(posicao) != SUCESSO)
        return POSICAO_INVALIDA;

    if (tamanho < 1)
        return TAMANHO_INVALIDO;

    EstruturaAux *e = &estruturas[posicao - 1];

    if (e->dados != NULL)
        return JA_TEM_ESTRUTURA_AUXILIAR;

    e->dados = malloc(sizeof(int) * tamanho);
    if (!e->dados)
        return SEM_ESPACO_DE_MEMORIA;

    e->tamanho = tamanho;
    e->qtd = 0;
    return SUCESSO;
}

int inserirNumeroEmEstrutura(int posicao, int valor) {
    if (PosicaoValida(posicao) != SUCESSO)
        return POSICAO_INVALIDA;

    EstruturaAux *e = &estruturas[posicao - 1];

    if (!e->dados)
        return SEM_ESTRUTURA_AUXILIAR;

    if (e->qtd >= e->tamanho)
        return SEM_ESPACO;

    e->dados[e->qtd++] = valor;
    return SUCESSO;
}

int excluirNumeroDoFinaldaEstrutura(int posicao) {
    if (PosicaoValida(posicao) != SUCESSO)
        return POSICAO_INVALIDA;

    EstruturaAux *e = &estruturas[posicao - 1];

    if (!e->dados)
        return SEM_ESTRUTURA_AUXILIAR;

    if (e->qtd == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    e->qtd--;
    return SUCESSO;
}

int excluirNumeroEspecificoDeEstrutura(int posicao, int valor) {
    if (PosicaoValida(posicao) != SUCESSO)
        return POSICAO_INVALIDA;

    EstruturaAux *e = &estruturas[posicao - 1];

    if (!e->dados)
        return SEM_ESTRUTURA_AUXILIAR;

    if (e->qtd == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    int i;
    for (i = 0; i < e->qtd; i++) {
        if (e->dados[i] == valor)
            break;
    }

    if (i == e->qtd)
        return NUMERO_INEXISTENTE;

    for (; i < e->qtd - 1; i++)
        e->dados[i] = e->dados[i + 1];

    e->qtd--;
    return SUCESSO;
}

int getQuantidadeElementosEstruturaAuxiliar(int posicao) {
    if (PosicaoValida(posicao) != SUCESSO)
        return POSICAO_INVALIDA;

    EstruturaAux *e = &estruturas[posicao - 1];

    if (!e->dados)
        return SEM_ESTRUTURA_AUXILIAR;

    if (e->qtd == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    return e->qtd;
}

int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    int qtd = getQuantidadeElementosEstruturaAuxiliar(posicao);
    if (qtd <= 0)
        return qtd;

    EstruturaAux *e = &estruturas[posicao - 1];
    for (int i = 0; i < e->qtd; i++)
        vetorAux[i] = e->dados[i];

    return SUCESSO;
}

int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    int ret = getDadosEstruturaAuxiliar(posicao, vetorAux);
    if (ret != SUCESSO)
        return ret;

    int qtd = estruturas[posicao - 1].qtd;
    for (int i = 0; i < qtd - 1; i++)
        for (int j = i + 1; j < qtd; j++)
            if (vetorAux[i] > vetorAux[j]) {
                int tmp = vetorAux[i];
                vetorAux[i] = vetorAux[j];
                vetorAux[j] = tmp;
            }

    return SUCESSO;
}

void dobrar(int *x) {
    *x = (*x) * 2;
}
