#include <stdio.h>
#include <stdbool.h>

struct carros {
    int chassi;
    int ano;
    bool lavado;
};

typedef struct carros carros;

int main() {
    carros car = {123456789, 2025, true};
    carros car2 = {987654321, 2020, true};
    carros car3 = {918273645, 2000, false};

    
    carros lista[3] = {car, car2, car3};

    printf("Status dos carros no lava jato:\n");

    for (int i = 0; i < 3; i++) {
        printf("Carro %d:\n", i + 1);
        printf("  Chassi: %d\n", lista[i].chassi);
        printf("  Ano: %d\n", lista[i].ano);
        printf("  Lavado: %s\n", lista[i].lavado ? "Sim" : "Não");
        printf("-------------------------\n");
    }

    return 0;
}
