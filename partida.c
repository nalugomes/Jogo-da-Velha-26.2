#include <stdio.h>
#include "partida.h"
#include "tabuleiro.h" 

JogadorTeclado jogador1, jogador2;

void joga(JogadorTeclado jogador) {
    int linha, coluna;
    int jogadaValida = 0;

    while(jogadaValida == 0) {
        char simbolo = (jogador.tipo == 1) ? 'O' : 'X';
        printf("Vez do jogador %c\n", simbolo);
        printf("Digite a linha (0, 1 ou 2): ");
        scanf("%d", &linha);
        printf("Digite a coluna (0, 1 ou 2): ");
        scanf("%d", &coluna);

        if(linha >= 0 && linha <= 2 && coluna >= 0 && coluna <= 2 && M[linha][coluna] == 0) {
            marcaJogada(linha, coluna, jogador.tipo);
            jogadaValida = 1;
        } else {
            printf("Jogada invalida! Tente novamente.\n");
        }
    }
}

void configuraJogadores() {
    jogador1.tipo = 4;
    jogador2.tipo = 1;
}

void inicia() {
    int turno = 0;
    int vencedor = 0;
    int jogadorAtual = 1;

    desenha();

    while(turno < 9 && vencedor == 0) {
        if(jogadorAtual == 1) {
            joga(jogador1);
            jogadorAtual = 2;
        } else {
            joga(jogador2);
            jogadorAtual = 1;
        }

        desenha();
        vencedor = temVencedor();
        turno++;
    }

    if(vencedor == 1) {
        printf("Jogador O venceu!\n");
    } else if(vencedor == 4) {
        printf("Jogador X venceu!\n");
    } else {
        printf("Empate!\n");
    }
}