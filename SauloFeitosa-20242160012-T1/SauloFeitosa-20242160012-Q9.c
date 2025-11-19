#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TAM 10
#define TOTAL_NAVIOS 6  // 1x4, 1x3, 3x1, 1x2 (pode alterar aqui)

typedef struct {
    int tamanho;
    int linha;
    int coluna;
    char direcao; // H ou V
} Navio;

char mapa1[TAM][TAM];
char mapa2[TAM][TAM];

void inicializarMapa(char mapa[TAM][TAM]) {
    for(int i = 0; i < TAM; i++)
        for(int j = 0; j < TAM; j++)
            mapa[i][j] = ' ';
}

void mostrarMapa(char mapa[TAM][TAM], int revelarNavios) {
    printf("    ");
    for(int c = 1; c <= TAM; c++) printf("%2d ", c);
    printf("\n");

    for(int i = 0; i < TAM; i++) {
        printf("%c | ", 'A' + i);
        for(int j = 0; j < TAM; j++) {
            char v = mapa[i][j];
            if(!revelarNavios && v == 'N') v = ' ';
            printf("%c  ", v);
        }
        printf("\n");
    }
}

int podeColocar(Navio n, char mapa[TAM][TAM]) {
    int i = n.linha;
    int j = n.coluna;

    for(int k = 0; k < n.tamanho; k++) {
        if(i < 0 || i >= TAM || j < 0 || j >= TAM) return 0;
        if(mapa[i][j] != ' ') return 0;
        if(n.direcao == 'H') j++;
        else i++;
    }
    return 1;
}

void colocarNavio(Navio n, char mapa[TAM][TAM]) {
    int i = n.linha;
    int j = n.coluna;

    for(int k = 0; k < n.tamanho; k++) {
        mapa[i][j] = 'N';
        if(n.direcao == 'H') j++;
        else i++;
    }
}

int atirar(char mapa[TAM][TAM], int linha, int coluna) {
    if(mapa[linha][coluna] == 'N') {
        mapa[linha][coluna] = '0';
        return 1;
    }
    if(mapa[linha][coluna] == ' '){
        mapa[linha][coluna] = 'X';
        return 0;
    }
    return -1;
}

int acabou(char mapa[TAM][TAM]) {
    for(int i = 0; i < TAM; i++)
        for(int j = 0; j < TAM; j++)
            if(mapa[i][j] == 'N') return 0;
    return 1;
}

void lerNavios(char mapa[TAM][TAM], int jogador) {
    int tamanhos[TOTAL_NAVIOS] = {4,3,1,1,1,2};

    printf("\n=== Jogador %d: Posicione seus navios ===\n", jogador);

    for(int n = 0; n < TOTAL_NAVIOS; n++) {
        Navio nv;
        nv.tamanho = tamanhos[n];

        while(1) {
            char pos[4];
            printf("Navio de tamanho %d - Ex: A1H para horizontal ou A1V para vertical: ", nv.tamanho);
            scanf("%s", pos);

            nv.linha = toupper(pos[0]) - 'A';
            nv.coluna = pos[1] - '1';
            nv.direcao = toupper(pos[2]);

            if(nv.linha < 0 || nv.linha >= TAM || nv.coluna < 0 || nv.coluna >= TAM) {
                printf("Posição inválida!\n");
                continue;
            }

            if(nv.direcao != 'H' && nv.direcao != 'V') {
                printf("Direção inválida! Use H ou V.\n");
                continue;
            }

            if(podeColocar(nv, mapa)) {
                colocarNavio(nv, mapa);
                mostrarMapa(mapa, 1);
                break;
            } else {
                printf("Não é possível colocar aqui!\n");
            }
        }
    }
}

int main() {
    inicializarMapa(mapa1);
    inicializarMapa(mapa2);

    lerNavios(mapa1, 1);
    lerNavios(mapa2, 2);

    int jogador = 1;

    while(1) {
        char pos[3];
        int linha, coluna;

        printf("\n=== Jogador %d, sua vez de atirar ===\n", jogador);

        printf("Tabuleiro do oponente (visão limitada):\n");
        mostrarMapa(jogador == 1 ? mapa2 : mapa1, 0);

        printf("Digite a posição do tiro (Ex: B5): ");
        scanf("%s", pos);

        linha = toupper(pos[0]) - 'A';
        coluna = pos[1] - '1';

        if(linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM) {
            printf("Jogada inválida!\n");
            continue;
        }

        int r = atirar(jogador == 1 ? mapa2 : mapa1, linha, coluna);

        if(r == -1) {
            printf("Você já atirou aqui!\n");
            continue;
        } else if(r == 1) {
            printf("ACERTOU!\n");
        } else {
            printf("ÁGUA!\n");
        }

        if(acabou(jogador == 1 ? mapa2 : mapa1)) {
            printf("\nJOGADOR %d VENCEU! Todos os navios inimigos foram destruídos.\n", jogador);
            break;
        }

        jogador = (jogador == 1 ? 2 : 1);
    }

    return 0;
}
