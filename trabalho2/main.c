#include <stdio.h>
#include "trabalho2.h"

int main() {
    int opcao;
    int posicao, tamanho, valor;
    int vetorAux[100];

    inicializar();

    do {
        printf("\n====== MENU ======\n");
        printf("1 - Criar estrutura auxiliar\n");
        printf("2 - Inserir numero em estrutura\n");
        printf("3 - Excluir numero do final da estrutura\n");
        printf("4 - Excluir numero especifico da estrutura\n");
        printf("5 - Listar dados da estrutura\n");
        printf("6 - Listar dados ordenados da estrutura\n");
        printf("7 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

        case 1:
            printf("Posicao (1 a 10): ");
            scanf("%d", &posicao);
            printf("Tamanho da estrutura: ");
            scanf("%d", &tamanho);
            printf("Retorno: %d\n",
                   criarEstruturaAuxiliar(posicao, tamanho));
            break;

        case 2:
            printf("Posicao: ");
            scanf("%d", &posicao);
            printf("Valor: ");
            scanf("%d", &valor);
            printf("Retorno: %d\n",
                   inserirNumeroEmEstrutura(posicao, valor));
            break;

        case 3:
            printf("Posicao: ");
            scanf("%d", &posicao);
            printf("Retorno: %d\n",
                   excluirNumeroDoFinaldaEstrutura(posicao));
            break;

        case 4:
            printf("Posicao: ");
            scanf("%d", &posicao);
            printf("Valor a excluir: ");
            scanf("%d", &valor);
            printf("Retorno: %d\n",
                   excluirNumeroEspecificoDeEstrutura(posicao, valor));
            break;

        case 5:
            printf("Posicao: ");
            scanf("%d", &posicao);
            if (getDadosEstruturaAuxiliar(posicao, vetorAux) == SUCESSO) {
                int qtd = getQuantidadeElementosEstruturaAuxiliar(posicao);
                for (int i = 0; i < qtd; i++)
                    printf("%d ", vetorAux[i]);
                printf("\n");
            }
            break;

        case 6:
            printf("Posicao: ");
            scanf("%d", &posicao);
            if (getDadosOrdenadosEstruturaAuxiliar(posicao, vetorAux) == SUCESSO) {
                int qtd = getQuantidadeElementosEstruturaAuxiliar(posicao);
                for (int i = 0; i < qtd; i++)
                    printf("%d ", vetorAux[i]);
                printf("\n");
            }
            break;

        case 7:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }

    } while (opcao != 7);

    finalizar();
    return 0;
}
