#include <iostream>
#include <limits>
#include "funcoes.h"

using namespace std;

// ===============================
// TABULEIRO GLOBAL (estado do jogo)
// ===============================
char tabuleiro[8][8];
// ===============================
// MENU
// ===============================
char menu()
{
    char opcao;

    do
    {
        cout << "================================\n";
        cout << "DAMAS\n";
        cout << "================================\n";
        cout << "1. PLAY\n";
        cout << "Opcao: ";

        cin >> opcao;

        if(opcao != '1')
        {
            cout << "Apenas os numeros da lista!\n";
        }

    } while(opcao != '1');

    return opcao;
}

// ===============================
// JOGO
// ===============================
void jogar()
{
    limparTela();

    char jogador1, jogador2;
    char jogadorAtual;
    bool jogoRodando = true;

    cout << "Digite P para time preto ou B para time branco: ";
    cin >> jogador1;

    limparTela();

    if (jogador1 == 'B')
        jogador2 = 'P';
    else
        jogador2 = 'B';

    jogadorAtual = 'B';

    inicializarTabuleiro();

    while (jogoRodando)
    {
        mostrarTabuleiro(jogadorAtual);

        cout << "\nJogador atual: " << jogadorAtual << endl;

        int x1, y1, x2, y2;

        cout << "Linha origem: ";
        x1 = lerCoordenada();

        cout << "Coluna origem: ";
        y1 = lerCoordenada();

        cout << "Linha destino: ";
        x2 = lerCoordenada();

        cout << "Coluna destino: ";
        y2 = lerCoordenada();

        if(moverPeca(x1, y1, x2, y2, jogadorAtual))
        {
            cout << "Movimento realizado com sucesso!\n";
        }
        else
        {
            cout << "Movimento invalido!\n";
        }
        
        // troca de turno
        if(jogadorAtual == 'B')
            jogadorAtual = 'P';
        else
            jogadorAtual = 'B';

        char sair;

        cout << "\nContinuar jogando? (s/n): ";
        cin >> sair;

        limparTela();

        if(sair == 'n')
        {
            jogoRodando = false;
        }
    }
}
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
// ===============================
// LIMPAR TELA
// ===============================
void limparTela() {
    // Compatibilidade entre Windows e Linux
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
// ===============================
// LIMPAR TELA
// ===============================
int lerCoordenada() {
    int num;

    while (true)
    {
        if (cin >> num)
        {
            if(num >= 0 && num <= 7)
            {
                return num;
            }

            cout << "Digite um numero entre 0 e 7: ";
        }
        else
        {
            cout << "Digite apenas numeros: ";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
