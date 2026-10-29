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
        printf("\nVez do jogador %c\n", simbolo);
        printf("Digite a linha (0, 1 ou 2): ");
        scanf("%d", &linha);
        printf("Digite a coluna (0, 1 ou 2): ");
        scanf("%d", &coluna);

        if(linha >= 0 && linha <= 2 && coluna >= 0 && coluna <= 2 && M[linha][coluna] == 0) {
            marcaJogada(linha, coluna, jogador.tipo);
            jogadaValida = 1;
        } else {
            printf("\nJogada invalida! Tente novamente.\n");
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

int main() {
    configuraJogadores();
    inicia();

    printf("\nPressione ENTER para sair...");
    while(getchar() != '\n');
    getchar();
    return 0;
}