#include <stdio.h>

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

typedef struct {
    int tipo;
} JogadorTeclado;

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

typedef struct {
    int tipo;
} JogadorIA;

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