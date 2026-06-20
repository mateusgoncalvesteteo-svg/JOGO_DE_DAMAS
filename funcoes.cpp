#include <iostream>
#include <limits>
#include "funcoes.h"

using namespace std;
// MENU
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
// JOGO
void jogar()
{
    Jogo meuJogo;
    limparTela();

    char jogador1, jogador2;
    char jogadorAtual;
    bool jogoRodando = true;
    bool jogadaValida = false;
    
    cout << "Digite P para time preto ou B para time branco: ";
    cin >> jogador1;

    limparTela();

    if (jogador1 == 'B')
        jogador2 = 'P';
    else
        jogador2 = 'B';

    jogadorAtual = 'B';

    inicializarTabuleiro(meuJogo);

    while (jogoRodando)
    {
        jogadaValida = false;
        mostrarTabuleiro(meuJogo, jogadorAtual);
        
        while (!jogadaValida) {
        
        cout << "\nJogador atual: " << jogadorAtual << endl;

        int x1, y1, x2, y2;

        cout << "Linha origem e Coluna origem: ";
        x1 = lerCoordenada();
        y1 = lerCoordenada();

        //cout << "Coluna origem: ";
        //y1 = lerCoordenada();

        cout << "Linha destino e Coluna Destino: ";
        x2 = lerCoordenada();
        y2 = lerCoordenada();

        //cout << "Coluna destino: ";
        //y2 = lerCoordenada();
                
        if(moverPeca( meuJogo, x1, y1, x2, y2,jogadorAtual))
        {
            cout << "Movimento realizado com sucesso!\n";
            jogadaValida = true;
        }
        else
        {
            cout << "Movimento invalido!\n";
        }
        
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
// INICIALIZA TABULEIRO
void inicializarTabuleiro(Jogo& jogo)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((i + j) % 2 == 1)
            {
                if (i < 3)
                    jogo.tabuleiro[i][j] = 'P'; // pretas no topo
                else if (i > 4)
                    jogo.tabuleiro[i][j] = 'B'; // brancas embaixo
                else
                    jogo.tabuleiro[i][j] = '.'; // casa vazia jogável
            }
            else
            {
                jogo.tabuleiro[i][j] = ' '; // casa inválida
            }
        }
    }
}
// MOSTRAR TABULEIRO
void mostrarTabuleiro(Jogo& jogo, char player)
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
                cout << "[" << jogo.tabuleiro[i][j] << "]";
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
                cout << "[" << jogo.tabuleiro[i][j] << "]";
            cout << endl;
        }
    }

    cout << "========================\n";
}
// MOVIMENTACAO DAS PECAS
bool moverPeca(Jogo& jogo, int x1, int y1, int x2, int y2, char jogadorAtual) {
    //verificar se existe as coordenadas requisitadas
    if(x1 < 0 || x1 > 7 || y1 < 0 || y1 > 7 || 
    x2 < 0 || x2 > 7 || y2 < 0 || y2 > 7 ) {
        return false;
    }
    
    //verificar se por exemplo: a peca branca é do jogador branco
    if(jogo.tabuleiro[x1][y1] != jogadorAtual ) {
        return false;
    }
    
    //verificar se no destino alvo ja nao tem uma peca
    if(jogo.tabuleiro[x2][y2] != '.') {
        return false;
    }
    
    // verificar movimento diagonal de 1 casa ou captura de 2 casas
    int diffX = x2 - x1;
    int diffY = y2 - y1;
    
    int absX = abs(diffX);//guardar os valores da coordenada
    int absY = abs(diffY);
    
    char peca = jogo.tabuleiro[x1][y1];
    //impedir que pecas que nao sejam a DAMA andem para tras
    if(peca == 'B' && diffX != -1 && diffX != -2) { //-1 = 1 casa e -2 = 2 casa, conta de baixo pra cima
     return false;
    }
    
    if(peca == 'P' && diffX != 1 && diffX != 2) {//no 'P' o tabuleiro inverte, por isso 1
        return false;
    }
    
    //verificar se o movimento é diagonal válida (1 casa ou captura de 2)
    if((absX != absY) || (absX != 1 && absX != 2)) {
        return false;
    }
    
    if(absX == 2 && absY == 2) {
    int meioX = (x1 + x2)/2; //achar a peca do meio
    int meioY = (y1 + y2)/2;
    
    char pecaMeio = jogo.tabuleiro[meioX][meioY];
    
    if(pecaMeio == '.') {
        return false;//peca comum nao anda 2 casas vazias
    }
    
    if(pecaMeio == jogo.tabuleiro[x1][y1]) {
        return false; //nao pode comer peca do mesmo time
    }
    
    jogo.tabuleiro[meioX][meioY] = '.';
    
    }
   
    //Mover a peca, a principal parte dessa funcao
    jogo.tabuleiro[x2][y2] = jogo.tabuleiro[x1][y1];
    jogo.tabuleiro[x1][y1] = '.';

    return true;
}
// LIMPAR TELA
void limparTela() {
    // Compatibilidade entre Windows e Linux
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
// LER A COORDENADA
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
