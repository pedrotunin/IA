#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

#define SIZE 9

struct estadoSudoku {
    int t[SIZE][SIZE];
};
typedef struct estadoSudoku estado;

//cria um estado
estado* criaEstado(int m[SIZE][SIZE]){

    estado *novo = new estado;

    for (int i = 0; i < SIZE; i++) {

        for (int j = 0; j < SIZE; j++) novo->t[i][j] = m[i][j];
        
    }
    return novo;

}

//preenche a matriz problema
void preencheMatrizProblema (int m[SIZE][SIZE], char *entrada) {

    int k = 0;
    for (int i = 0; i < SIZE; i++) {

        for (int j = 0; j < SIZE; j++) {
            m[i][j] = entrada[k] == '.' ? 0 : entrada[k] - 48;
            k++;
        }
    }

}

//imprime a solução de uma instância do problema sudoku
void imprimeSolucao (int m[SIZE][SIZE]) {

    for (int i = 0; i < SIZE; i++) {

        for (int j = 0; j < SIZE; j++) printf("%d", m[i][j]);

    }
    printf("\n");

}

//verifica se o estado é uma solução para o sudoku
bool verificaSolucao(estado *atual) {

    const int controle = 45; // soma de uma linha/coluna/quadrante do sudoku

    //verifica linhas e colunas
    int somaLin = 0, somaCol = 0;
    for (int i = 0; i < SIZE; i++) {

        for(int j = 0; j < SIZE; j++) {

            if (atual->t[i][j] == 0 || atual->t[j][i] == 0) return false;
            somaLin += atual->t[i][j];
            somaCol += atual->t[j][i];

        }
        if (somaLin != controle || somaCol != controle) return false;
        somaLin = 0;
        somaCol = 0;

    }

    //verifica quadrantes
    int somaQuad = 0;

    for (int l = 0; l <= 6; l += 3) {

        for (int k = 0; k <= 6; k += 3) {

            somaQuad = 0;
            for(int i = k; i < 3 + k; i++) {

                for(int j = l; j < 3 + l; j++) {
                    somaQuad += atual->t[i][j];
                }
                
            }
            if (somaQuad != controle) return false;

        }

    }

    return true;

}

//verifica se o valor x está presente na determinada linha
//retorna verdadeiro caso x esteja presente, falso caso contrário
bool verificaLinha (int *linha, int x) {

    for (int i = 0; i < SIZE; i++) {
        if (linha[i] == x) return true;
    }
    return false;

}

//verifica se o valor x está presente na determinada coluna
//retorna verdadeiro caso x esteja presente, falso caso contrário
bool verificaColuna (int m[SIZE][SIZE], int coluna, int x) {

    for (int i = 0; i < SIZE; i++) {
        if (m[i][coluna] == x) return true;
    }
    return false;

}

//verifica se o valor x está presente no determinado quadrante
//retorna verdadeiro caso x esteja presente, falso caso contrário
bool verificaQuadrante (int m[SIZE][SIZE], int linha, int coluna, int x) {

    linha -= linha % 3;
    coluna -= coluna % 3;

    for (int i = linha; i < linha + 3; i++) {
        for (int j = coluna; j < coluna + 3; j++){
            if (m[i][j] == x) return true;
        }
    }
    return false;

}

//descobre a proxima posição vazia
//caso não tenha nenhuma posição valida, retorna falso, verdadeiro caso contrario
bool proximaPosicaoVazia(estado *atual, int *lin, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (atual->t[i][j] == 0) {
                *lin = i;
                *col = j;
                return true;
            }
        }
    }
    return false;
}

//dado um estado, retorna os possiveis valores para o proximo espaço em branco
void valoresPossiveis(estado *atual, int *v) {
    
    for(int i = 0; i < 9; i++) v[i] = 1;

    int lin, col;
    if (proximaPosicaoVazia(atual, &lin, &col)) {

        for(int num = 1; num <= SIZE; num++) {
            if (verificaLinha(atual->t[lin], num) || verificaColuna(atual->t, col, num) || verificaQuadrante(atual->t, lin, col, num)){
                v[num - 1] = 0;
            }
        }

    } else {

        for(int i = 0; i < SIZE; i++) v[i] = 0;

    }

}

//retorna a quantidade de valores possíveis para uma posição
int qtdValoresPossiveis(estado *atual, int linha, int coluna) {

    int qtd = SIZE;
    for(int num = 1; num <= SIZE; num++) {
        if (verificaLinha(atual->t[linha], num) || verificaColuna(atual->t, coluna, num) || verificaQuadrante(atual->t, linha, coluna, num)){
            qtd--;
        }
    }
    return qtd;

}

//retorna falso caso alguma posição vazia não tenha valores possíveis para inserção, verdadeiro caso contrário
bool ehPossivel(estado *atual) {

    for (int lin = 0; lin < SIZE; lin++) {
        for (int col = 0; col < SIZE; col++) {
            if (atual->t[lin][col] == 0 && qtdValoresPossiveis(atual, lin, col) == 0) return false;
        }
    }
    return true;

}