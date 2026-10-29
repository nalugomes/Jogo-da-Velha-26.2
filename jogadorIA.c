void jogaIA(JogadorIA jogador);

#include <stdio.h>
#include "jogadorIA.h"
#include "tabuleiro.h"

int contaChances(int alvo) {
    int c = 0;
    for(int i=0; i<3; i++) if(M[i][0]+M[i][1]+M[i][2] == alvo) c++;
    for(int j=0; j<3; j++) if(M[0][j]+M[1][j]+M[2][j] == alvo) c++;
    if(M[0][0]+M[1][1]+M[2][2] == alvo) c++;
    if(M[0][2]+M[1][1]+M[2][0] == alvo) c++;
    return c;
}

int completaLinha(int alvo, int tipo) {
    for(int i=0; i<3; i++) {
        if(M[i][0]+M[i][1]+M[i][2] == alvo) {
            for(int j=0; j<3; j++) if(M[i][j]==0) { marcaJogada(i,j,tipo); return 1; }
        }
    }
    for(int j=0; j<3; j++) {
        if(M[0][j]+M[1][j]+M[2][j] == alvo) {
            for(int i=0; i<3; i++) if(M[i][j]==0) { marcaJogada(i,j,tipo); return 1; }
        }
    }
    if(M[0][0]+M[1][1]+M[2][2] == alvo) {
        if(M[0][0]==0) { marcaJogada(0,0,tipo); return 1; }
        if(M[1][1]==0) { marcaJogada(1,1,tipo); return 1; }
        if(M[2][2]==0) { marcaJogada(2,2,tipo); return 1; }
    }
    if(M[0][2]+M[1][1]+M[2][0] == alvo) {
        if(M[0][2]==0) { marcaJogada(0,2,tipo); return 1; }
        if(M[1][1]==0) { marcaJogada(1,1,tipo); return 1; }
        if(M[2][0]==0) { marcaJogada(2,0,tipo); return 1; }
    }
    return 0;
}

void jogaIA(JogadorIA j) {
    int tipo = j.tipo, opp = (tipo == 1) ? 4 : 1;


    if(completaLinha(tipo * 2, tipo)) return; 
    if(completaLinha(opp * 2, tipo)) return;  


    for(int i=0; i<3; i++) {
        for(int k=0; k<3; k++) {
            if(M[i][k] == 0) {
                M[i][k] = tipo;
                if(contaChances(tipo * 2) >= 2) return;
                M[i][k] = 0; 
            }
        }
    }


    if(M[1][1] == 0) { marcaJogada(1,1,tipo); return; }


    if(M[0][0] == opp && M[2][2] == 0) { marcaJogada(2,2,tipo); return; }
    if(M[2][2] == opp && M[0][0] == 0) { marcaJogada(0,0,tipo); return; }
    if(M[0][2] == opp && M[2][0] == 0) { marcaJogada(2,0,tipo); return; }
    if(M[2][0] == opp && M[0][2] == 0) { marcaJogada(0,2,tipo); return; }


    if(M[0][0] == 0) { marcaJogada(0,0,tipo); return; }
    if(M[0][2] == 0) { marcaJogada(0,2,tipo); return; }
    if(M[2][0] == 0) { marcaJogada(2,0,tipo); return; }
    if(M[2][2] == 0) { marcaJogada(2,2,tipo); return; }


    for(int i=0; i<3; i++) {
        for(int k=0; k<3; k++) {
            if(M[i][k] == 0) { marcaJogada(i,k,tipo); return; }
        }
    }
}