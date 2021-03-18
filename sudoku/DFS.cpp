#include "auxilia.h"

estado* resolveDFS (estado *inicial) {

    if(verificaSolucao(inicial)) return inicial;

    vector<estado*> pilha;
    pilha.push_back(inicial);

    while (!pilha.empty()) {

        estado *atual = pilha.back();
        pilha.pop_back();

        if(verificaSolucao(atual)) return atual;

        int estadosPossiveis[SIZE];
        valoresPossiveis(atual, estadosPossiveis);
        
        int lin, col;
        proximaPosicaoVazia(atual, &lin, &col);

        for (int i = 0; i < SIZE; i++) {

            if (estadosPossiveis[i] != 0) {
                
                estado *novo = criaEstado(atual->t);
                novo->t[lin][col] = i + 1;
                pilha.push_back(novo);

            }

        }
        delete atual;
    }
    return NULL;
}

int main (int argc, char *argv[]) {

    int matriz[SIZE][SIZE]; //matriz problema

    preencheMatrizProblema(matriz, argv[1]);

    estado *inicial = criaEstado(matriz); //estado inicial

    estado *solucao = resolveDFS(inicial); //solução final

    imprimeSolucao(solucao->t);

    return 0;
}