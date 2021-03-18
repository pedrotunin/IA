#include "auxilia.h"

int f_n(estado *atual);

struct Compara {
    bool operator()(estado *a, estado *b) { //função de comparação personalizada da priority queue
        if (f_n(a) > f_n(b)) return true;
        else return false;
    }
};

//g(n) -> função de custo
//soma da quantidade de valores possiveis para a proxima casa em branco
int g_n(estado *atual) {

    int qtdFilhos = 0;

    int lin, col;
    proximaPosicaoVazia(atual, &lin, &col);

    qtdFilhos = qtdValoresPossiveis(atual, lin, col);

    return qtdFilhos;

}

//h(n) -> função heurística
//soma da quantidade de valores possiveis de todos os espaços em branco do tabuleiro
int h_n(estado *atual) {

    int total = 0;
    for (int lin = 0; lin < SIZE; lin++) {
        for (int col = 0; col < SIZE; col++) {
            if (atual->t[lin][col] == 0) total += qtdValoresPossiveis(atual, lin, col);
        }
    }
    return total;

}

//f(n) = g(n) + h(n)
int f_n(estado *atual) {
    return g_n(atual) + h_n(atual);
}

estado* resolveAEstrela(estado *inicial) {

    if (verificaSolucao(inicial)) return inicial;

    priority_queue<estado*, vector<estado*>, Compara> pq;
    pq.push(inicial);

    while (!pq.empty()) {

        estado *atual = pq.top();
        pq.pop();

        if (verificaSolucao(atual)) return atual;

        int estadosPossiveis[SIZE];
        valoresPossiveis(atual, estadosPossiveis);

        int lin, col;
        proximaPosicaoVazia(atual, &lin, &col);

        for (int i = 0; i < SIZE; i++) {

            if (estadosPossiveis[i] != 0) {

                estado *novo = criaEstado(atual->t);
                novo->t[lin][col] = i + 1;
                pq.push(novo);

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

    estado *solucao = resolveAEstrela(inicial); //solução final

    imprimeSolucao(solucao->t);
    
    return 0;
}