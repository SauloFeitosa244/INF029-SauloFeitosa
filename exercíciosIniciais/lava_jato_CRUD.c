//CRUD = Creat, Read, Update, Delete
#include <stdio.h>
#include <stdbool.h>

#define TAM 3

typedef struct{
    int ano;
    int chassi;
} Carro;

int main(){
    
    Carro carros[TAM];
    int opcao;
    int carrosCont = 0;
    int qtdCarros = 0;
    bool sair = false;
    
    while(!sair){
        printf("\n------- MENU -------\n");
        printf("0 - Sair\n");
        printf("1 - Adicionar carro\n");
        printf("2 - Listar carros\n");
        printf("3 - Atualizar carro\n");
        printf("4 - Remover carro\n");
        scanf("%d", &opcao);
        
        switch(opcao){
            case 0:
                printf("Saindo...");
                sair = true;
                break;
            case 1:
                if(qtdCarros < TAM){
                    printf("Ano: ");
                    scanf("%d", &carros[carrosCont].ano);
                        if(carros[carrosCont].ano < 1886){
                            printf("Número inválido");
                            break;
                        }
                    printf("Número do chassi: ");
                    scanf("%d", &carros[carrosCont].chassi);
                        if(carros[carrosCont].chassi > 9999){
                            printf("Número inválido");
                            break;
                        }
                    qtdCarros++;
                    carrosCont++;
                    break;
                }
                else{
                    printf("Número de carros excedido\n");
                    printf("Atualize ou delete um carro para adicionar dados novos");
                    break;
                }
            case 2:
                if(qtdCarros == 0){
                    printf("Nenhum carro cadastrado...\n");
                    break;
                }
                else{
                    for(int i = 0; i < qtdCarros; i++){
                        printf("Carro %d - Ano: %d || N. Chassi: %d\n", i+1, carros[i].ano, carros[i].chassi);
                    }
                break;
                }
            case 3:
                if(qtdCarros <= 0){
                    printf("Nenhum carro cadastrado...\n");
                    break;
                }
                else{
                for(int i = 0; i < qtdCarros; i++){
                        printf("Carro %d - Ano: %d || N. Chassi: %d\n", i+1, carros[i].ano, carros[i].chassi);
                    }
                printf("Digite o número do carro que deseja atualizar: ");
                scanf("%d", &opcao);
                printf("Ano: ");
                scanf("%d", &carros[opcao-1].ano);
                printf("Número do chassi: ");
                scanf("%d", &carros[opcao-1].chassi);
                break;
                }
            case 4:
                if(qtdCarros <= 0){
                    printf("Nenhum carro cadastrado...\n");
                    break;
                }
                else{
                for(int i = 0; i < qtdCarros; i++)
                        printf("Carro %d - Ano: %d || N. Chassi: %d\n", i+1, carros[i].ano, carros[i].chassi);
                
                printf("Digite o número do carro para deletar: ");
                scanf("%d", &opcao);

                if (opcao >= 1 && opcao <= qtdCarros) {
                    for (int i = opcao - 1; i < qtdCarros - 1; i++) {
                        carros[i] = carros[i + 1];
                    }
                    qtdCarros--;
                    printf("Carro %d removido\n", opcao);
                } else {
                    printf("Opção inválida!\n");
                }
                break;
                }
                
            default:
                printf("Número inválido");
        }
    }
  
    return 0;
}