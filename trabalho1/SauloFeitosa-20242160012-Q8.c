#include <stdio.h>
#include <ctype.h>

char tab[3][3];

void inicializarTabuleiro() {
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            tab[i][j] = ' ';
}

void mostrarTabuleiro(int jogador) {
    printf("\nJogador %d, informe sua jogada:\n\n", jogador);
    printf("     1   2   3\n");
    printf("A  [ %c | %c | %c ]\n", tab[0][0], tab[0][1], tab[0][2]);
    printf("   ----------------\n");
    printf("B  [ %c | %c | %c ]\n", tab[1][0], tab[1][1], tab[1][2]);
    printf("   ----------------\n");
    printf("C  [ %c | %c | %c ]\n\n", tab[2][0], tab[2][1], tab[2][2]);
}

int ganhou(char m) {
    for(int i = 0; i < 3; i++) {
        if(tab[i][0] == m && tab[i][1] == m && tab[i][2] == m) return 1;
        if(tab[0][i] == m && tab[1][i] == m && tab[2][i] == m) return 1;
    }
    if(tab[0][0] == m && tab[1][1] == m && tab[2][2] == m) return 1;
    if(tab[0][2] == m && tab[1][1] == m && tab[2][0] == m) return 1;
    return 0;
}

int main() {
    inicializarTabuleiro();
    int jogadas = 0;
    int jogador = 1;
    char marca, linhaLetra;
    int coluna, linha;

    while(1) {
        mostrarTabuleiro(jogador);
        marca = (jogador == 1 ? 'X' : 'O');

        char entrada[3];
        printf("Exemplo de jogada: B3\n");
        printf("Digite sua jogada: ");
        scanf("%s", entrada);

        linhaLetra = toupper(entrada[0]);
        coluna = entrada[1] - '0';

        if(linhaLetra < 'A' || linhaLetra > 'C' || coluna < 1 || coluna > 3) {
            printf("\nJogada inválida! Tente novamente.\n");
            continue;
        }

        linha = linhaLetra - 'A';
        coluna--;

        if(tab[linha][coluna] != ' ') {
            printf("\nPosição ocupada! Tente outra.\n");
            continue;
        }

        tab[linha][coluna] = marca;
        jogadas++;

        if(ganhou(marca)) {
            mostrarTabuleiro(jogador);
            printf("Jogador %d venceu!\n", jogador);
            break;
        }

        if(jogadas == 9) {
            mostrarTabuleiro(jogador);
            printf("Empate! Ninguém ganhou.\n");
            break;
        }

        jogador = (jogador == 1 ? 2 : 1);
    }

    return 0;
}