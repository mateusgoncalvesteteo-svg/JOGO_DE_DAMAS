#include <iostream>
#include "funcoes.h"

using namespace std;

// ===============================
// TABULEIRO GLOBAL (estado do jogo)
// ===============================
char tabuleiro[8][8];

// ===============================
// INICIALIZA TABULEIRO
// ===============================
void inicializarTabuleiro()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((i + j) % 2 == 1)
            {
                if (i < 3)
                    tabuleiro[i][j] = 'P'; // pretas no topo
                else if (i > 4)
                    tabuleiro[i][j] = 'B'; // brancas embaixo
                else
                    tabuleiro[i][j] = '.'; // casa vazia jogável
            }
            else
            {
                tabuleiro[i][j] = ' '; // casa inválida
            }
        }
    }
}

// ===============================
// MOSTRAR TABULEIRO
// ===============================
void mostrarTabuleiro(char player)
{
    cout << "\n========================\n";

    cout << "  ";
    for(int j = 0; j < 8; j++) {
        cout << " " << j << " ";
    }
    cout << endl;

    if (player == 'B')
    {
        // visão normal (branco embaixo)
        for (int i = 0; i < 8; i++)
        {
            cout << i << " ";

            for (int j = 0; j < 8; j++)
                cout << "[" << tabuleiro[i][j] << "]";
            cout << endl;
        }
    }
    else
    {
        // visão invertida (preto embaixo)
        for (int i = 7; i >= 0; i--)
        {
            cout << i << " ";

            for (int j = 0; j < 8; j++)
                cout << "[" << tabuleiro[i][j] << "]";
            cout << endl;
        }
    }

    cout << "========================\n";
}
// ===============================
// MOVIMENTACAO DAS PECAS
// ===============================
bool moverPeca(int x1, int y1, int x2, int y2, char jogadorAtual) {
    //passo1 -> verificar se existir as coodeenadas requisitadas
    if(x1 < 0 || x1 > 7 || y1 < 0 || y1 > 7 ||
    x2 < 0 || x2 > 7 || y2 < 0 || y2 > 7) {
        return false;
    }

    // Verificar se a peça , por exemplo branca é do jogador branco
    if(tabuleiro[x1][y1] != jogadorAtual) {
        return false;
    }

    //Verificar se no destino alvo ja nao tem uma peca
    if(tabuleiro[x2][y2] != '.') {
        return false;
    }

    //Mover a peca, a principal parte dessa funcao
    tabuleiro[x2][y2] = tabuleiro[x1][y1];
    tabuleiro[x1][y1] = '.';

    return true;
}
