#include <stdio.h>
#include "partida.h"

int main() {
    configuraJogadores();
    inicia();

    printf("\nPressione ENTER para sair...");
    while(getchar() != '\n');
    getchar();
    return 0;
}