#include <stdio.h>
#include "tabuleiro.h"

int M[3][3] = { {0,0,0}, {0,0,0}, {0,0,0} };

void desenha() {
    printf("\033[2J\033[H");
    printf("----JOGO DA VELHA---\n\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if(M[i][j] == 0) printf("   ");
            else if(M[i][j] == 1) printf(" O ");
            else if(M[i][j] == 4) printf(" X ");

            if(j < 2) printf("|");
        }
        printf("\n");
        if(i < 2) printf("-----------\n");
    }
    printf("\n");
}

int temVencedor() {
    int soma;
    for(int i = 0; i < 3; i++) {
        soma = M[i][0] + M[i][1] + M[i][2];
        if(soma == 3) return 1;
        if(soma == 12) return 4;
    }
    for(int j = 0; j < 3; j++) {
        soma = M[0][j] + M[1][j] + M[2][j];
        if(soma == 3) return 1;
        if(soma == 12) return 4;
    }
    soma = M[0][0] + M[1][1] + M[2][2];
    if(soma == 3) return 1;
    if(soma == 12) return 4;

    soma = M[0][2] + M[1][1] + M[2][0];
    if(soma == 3) return 1;
    if(soma == 12) return 4;

    return 0;
}

void marcaJogada(int x, int y, int tipo) {
    M[x][y] = tipo;
}