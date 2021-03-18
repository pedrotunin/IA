#include "auxilia.h"

estado* resolveBFS(estado *inicial) {

    if (verificaSolucao(inicial)) return inicial;

    queue<estado*> fila;
    fila.push(inicial);

    while (!fila.empty()) {

        estado *atual = fila.front();
        fila.pop();

        if(!ehPossivel(atual)) {
            delete atual;
            continue;
        }

        int estadosPossiveis[9];
        valoresPossiveis(atual, estadosPossiveis);
        
        int lin, col;
        proximaPosicaoVazia(atual, &lin, &col);

        for(int i = 0; i < SIZE; i++) {
            
            if (estadosPossiveis[i] != 0) {

                estado *novo = criaEstado(atual->t);
                novo->t[lin][col] = i + 1;

                if (verificaSolucao(novo)) return novo;
                
                fila.push(novo);
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

    estado *solucao = resolveBFS(inicial); //solução final

    imprimeSolucao(solucao->t);

    return 0;
}