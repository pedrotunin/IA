#include "auxilia.h"

int backtrack (estado *atual) {

    int linha, coluna;
    if (proximaPosicaoVazia(atual, &linha, &coluna) == false) return 1;

    int valores[SIZE];
    valoresPossiveis(atual, valores);

    for (int i = 0; i < SIZE; i++) {

        if (valores[i] == 1) {
            atual->t[linha][coluna] = i + 1;

            if (backtrack(atual)) return 1;

            atual->t[linha][coluna] = 0;
        }

    }

    return 0;

}

estado* resolveBT (estado *inicial) {

    backtrack(inicial);

    return inicial;
    
}

int main (int argc, char *argv[]) {

    int matriz[SIZE][SIZE]; //matriz problema

    preencheMatrizProblema(matriz, argv[1]);

    estado *inicial = criaEstado(matriz); //estado inicial

    estado *solucao = resolveBT(inicial); //solução final

    imprimeSolucao(solucao->t);

    return 0;
}