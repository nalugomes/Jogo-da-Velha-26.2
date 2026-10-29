#include <stdio.h>
#include "partida.h"   
#include "tabuleiro.h" 
#include "jogadorIA.h" 


void joga(JogadorTeclado jogador);

int main() {
    JogadorTeclado humano;
    JogadorIA computador;
    humano.tipo = 4;     
    computador.tipo = 1; 

    int turno = 0, vencedor = 0, jogadorAtual = 1;
    
    desenha();

    while(turno < 9 && vencedor == 0) {
        if(jogadorAtual == 1) {
            joga(humano);
            jogadorAtual = 2;
        } else {
            printf("\nVez do computador (IA)...\n");
            jogaIA(computador);
            jogadorAtual = 1;
        }

        desenha();
        vencedor = temVencedor();
        turno++;
    }

    if(vencedor == 1) printf("Computador (IA) venceu!\n");
    else if(vencedor == 4) printf("Voce venceu!\n");
    else printf("Empate!\n");

    printf("\nPressione ENTER para sair...");
    while(getchar() != '\n');
    getchar();

    return 0;
}