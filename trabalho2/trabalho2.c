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
    for (i = 0; i < e->qtd; i++)
        if (e->dados[i] == valor)
            break;

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

int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int k = 0;
    int tem = 0;

    for (int i = 0; i < TAM; i++) {
        if (estruturas[i].dados && estruturas[i].qtd > 0) {
            tem = 1;
            for (int j = 0; j < estruturas[i].qtd; j++)
                vetorAux[k++] = estruturas[i].dados[j];
        }
    }

    if (!tem)
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;

    return SUCESSO;
}

int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int ret = getDadosDeTodasEstruturasAuxiliares(vetorAux);
    if (ret != SUCESSO)
        return ret;

    int total = 0;
    for (int i = 0; i < TAM; i++)
        if (estruturas[i].dados)
            total += estruturas[i].qtd;

    for (int i = 0; i < total - 1; i++)
        for (int j = i + 1; j < total; j++)
            if (vetorAux[i] > vetorAux[j]) {
                int tmp = vetorAux[i];
                vetorAux[i] = vetorAux[j];
                vetorAux[j] = tmp;
            }

    return SUCESSO;
}

int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho) {
    if (PosicaoValida(posicao) != SUCESSO)
        return POSICAO_INVALIDA;

    EstruturaAux *e = &estruturas[posicao - 1];
    if (!e->dados)
        return SEM_ESTRUTURA_AUXILIAR;

    if (novoTamanho < 0 && e->tamanho + novoTamanho < 1)
        return NOVO_TAMANHO_INVALIDO;

    int novo = e->tamanho + novoTamanho;
    int *novoVetor = realloc(e->dados, sizeof(int) * novo);
    if (!novoVetor)
        return SEM_ESPACO_DE_MEMORIA;

    e->dados = novoVetor;
    e->tamanho = novo;
    if (e->qtd > novo)
        e->qtd = novo;

    return SUCESSO;
}

No *montarListaEncadeadaComCabecote() {
    No *cab = malloc(sizeof(No));
    cab->prox = NULL;

    No *atual = cab;

    for (int i = 0; i < TAM; i++) {
        if (estruturas[i].dados) {
            for (int j = 0; j < estruturas[i].qtd; j++) {
                No *novo = malloc(sizeof(No));
                novo->conteudo = estruturas[i].dados[j];
                novo->prox = NULL;
                atual->prox = novo;
                atual = novo;
            }
        }
    }

    return cab;
}

void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]) {
    int i = 0;
    No *aux = inicio->prox;

    while (aux) {
        vetorAux[i++] = aux->conteudo;
        aux = aux->prox;
    }
}

void destruirListaEncadeadaComCabecote(No **inicio) {
    No *aux = *inicio;
    while (aux) {
        No *tmp = aux;
        aux = aux->prox;
        free(tmp);
    }
    *inicio = NULL;
}

void dobrar(int *x) {
    *x = (*x) * 2;
}
