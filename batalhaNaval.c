#include <stdio.h>
#include <stdlib.h>

#define TAB 10         // tamanho do tabuleiro
#define HAB 5          // tamanho fixo das matrizes de habilidade
#define NAVIO 3        // valor que representa parte de um navio
#define HABILIDADE 5   // valor que representa área afetada

// Inicia o tabuleiro
void inicializarTabuleiro(int tabuleiro[TAB][TAB]) {
    for (int i = 0; i < TAB; i++)
        for (int j = 0; j < TAB; j++)
            tabuleiro[i][j] = 0;
}

// Mostra o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAB][TAB]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAB; i++) {
        for (int j = 0; j < TAB; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// posiciona os navios fixos
void posicionarNavios(int tabuleiro[TAB][TAB]) {
    // Horizontal
    for (int i = 0; i < 3; i++) tabuleiro[1][1 + i] = NAVIO;
    // Vertical
    for (int i = 0; i < 3; i++) tabuleiro[3 + i][4] = NAVIO;
    // Diagonal principal
    for (int i = 0; i < 3; i++) tabuleiro[6 + i][6 + i] = NAVIO;
    // Diagonal secundária
    for (int i = 0; i < 3; i++) tabuleiro[6 + i][6 - i] = NAVIO;
}

// Gera matriz em forma de cone
void gerarCone(int habilidade[HAB][HAB]) {
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            if (j >= (HAB - 1) / 2 - i && j <= (HAB - 1) / 2 + i)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// Gera matriz em forma de cruz
void gerarCruz(int habilidade[HAB][HAB]) {
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            if (i == HAB / 2 || j == HAB / 2)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// Gera matriz em forma de octaedro (losango)
void gerarOctaedro(int habilidade[HAB][HAB]) {
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            if (abs(i - HAB / 2) + abs(j - HAB / 2) <= HAB / 2)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// Aplica uma matriz de habilidade sobre o tabuleiro
void aplicarHabilidade(int tabuleiro[TAB][TAB], int habilidade[HAB][HAB], int origem_linha, int origem_coluna) {
    int offset = HAB / 2;
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            int linha = origem_linha - offset + i;
            int coluna = origem_coluna - offset + j;
            // Verifica se está dentro do tabuleiro
            if (linha >= 0 && linha < TAB && coluna >= 0 && coluna < TAB) {
                if (habilidade[i][j] == 1 && tabuleiro[linha][coluna] == 0)
                    tabuleiro[linha][coluna] = HABILIDADE;
            }
        }
    }
}

int main() {
    int tabuleiro[TAB][TAB];
    int cone[HAB][HAB], cruz[HAB][HAB], octaedro[HAB][HAB];

    inicializarTabuleiro(tabuleiro);
    posicionarNavios(tabuleiro);

    // Gera padrões de habilidade
    gerarCone(cone);
    gerarCruz(cruz);
    gerarOctaedro(octaedro);

    aplicarHabilidade(tabuleiro, cone, 2, 2);
    aplicarHabilidade(tabuleiro, cruz, 5, 5);
    aplicarHabilidade(tabuleiro, octaedro, 8, 8);

    // Mostra o resultado final
    imprimirTabuleiro(tabuleiro);

    return 0;
}
