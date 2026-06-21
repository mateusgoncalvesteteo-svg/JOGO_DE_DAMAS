#include <iostream>
#include <limits>
#include <cstdlib> // Adicionado para a função abs() funcionar perfeitamente
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

            cout << "Linha origem e Coluna origem (separados por espaco): ";
            x1 = lerCoordenada();
            y1 = lerCoordenada();

            cout << "Linha destino e Coluna Destino (separados por espaco): ";
            x2 = lerCoordenada();
            y2 = lerCoordenada();
                    
            if(moverPeca(meuJogo, x1, y1, x2, y2, jogadorAtual))
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

// ===============================
// MOVIMENTO EXCLUSIVO DA DAMA
// ===============================
bool moverDama(Jogo& jogo, int x1, int y1, int x2, int y2, char jogadorAtual) {
    char peca = jogo.tabuleiro[x1][y1];
    
    int diffX = x2 - x1;
    int diffY = y2 - y1;

    // Verificar se o movimento é perfeitamente diagonal
    if (abs(diffX) != abs(diffY)) {
        return false;
    }

    // Descobrir direção do movimento (+1 avança, -1 recua)
    int passoX = (diffX > 0) ? 1 : -1;
    int passoY = (diffY > 0) ? 1 : -1;

    bool encontrouInimigo = false;
    int captX = -1, captY = -1;

    int atualX = x1 + passoX;
    int atualY = y1 + passoY;

    // Varredura da matriz: Anda casa por casa até o destino (Fail Fast logic)
    while (atualX != x2 && atualY != y2) {
        char casaAtual = jogo.tabuleiro[atualX][atualY];

        if (casaAtual != '.') {
            bool aliado = false;
            if (jogadorAtual == 'B' && (casaAtual == 'B' || casaAtual == 'D')) aliado = true;
            if (jogadorAtual == 'P' && (casaAtual == 'P' || casaAtual == 'Q')) aliado = true;

            if (aliado) {
                return false; // Bateu em uma peça do próprio time
            } else {
                if (encontrouInimigo) {
                    return false; // Tentou pular mais de 1 inimigo de uma vez na mesma diagonal
                }
                encontrouInimigo = true;
                captX = atualX;
                captY = atualY;
            }
        }
        atualX += passoX;
        atualY += passoY;
    }

    // Se encontrou inimigo, remove a peça
    if (encontrouInimigo) {
        jogo.tabuleiro[captX][captY] = '.';
    }

    // Mover a Dama
    jogo.tabuleiro[x2][y2] = peca;
    jogo.tabuleiro[x1][y1] = '.';

    return true;
}

// ===============================
// MOVIMENTACAO DAS PECAS (PRINCIPAL)
// ===============================
bool moverPeca(Jogo& jogo, int x1, int y1, int x2, int y2, char jogadorAtual) {
    // 1. Verificar se as coordenadas existem
    if(x1 < 0 || x1 > 7 || y1 < 0 || y1 > 7 || 
       x2 < 0 || x2 > 7 || y2 < 0 || y2 > 7 ) {
        return false;
    }
    
    char peca = jogo.tabuleiro[x1][y1];

    // 2. Verificar se a peça pertence ao jogador (incluindo Damas 'D' e 'Q')
    if (jogadorAtual == 'B' && (peca != 'B' && peca != 'D')) return false;
    if (jogadorAtual == 'P' && (peca != 'P' && peca != 'Q')) return false;
    
    // 3. Verificar se destino já não tem uma peca
    if(jogo.tabuleiro[x2][y2] != '.') {
        return false;
    }

    // ===============================================
    // SE FOR DAMA, REPASSA PARA A FUNÇÃO DELA!
    // ===============================================
    if (peca == 'D' || peca == 'Q') {
        return moverDama(jogo, x1, y1, x2, y2, jogadorAtual);
    }
    
    // ===============================================
    // LÓGICA DA PEÇA NORMAL (Sua lógica perfeita)
    // ===============================================
    int diffX = x2 - x1;
    int diffY = y2 - y1;
    int absX = abs(diffX);
    int absY = abs(diffY);
    
    // Impedir que pecas andem para trás
    if(peca == 'B' && diffX != -1 && diffX != -2) return false; 
    if(peca == 'P' && diffX != 1 && diffX != 2) return false;
    
    if((absX != absY) || (absX != 1 && absX != 2)) return false;
    
    if(absX == 2 && absY == 2) {
        int meioX = (x1 + x2)/2; 
        int meioY = (y1 + y2)/2;
        char pecaMeio = jogo.tabuleiro[meioX][meioY];
        
        if(pecaMeio == '.') return false;
        
        // Não pode comer peça aliada (incluindo damas aliadas)
        if (jogadorAtual == 'B' && (pecaMeio == 'B' || pecaMeio == 'D')) return false;
        if (jogadorAtual == 'P' && (pecaMeio == 'P' || pecaMeio == 'Q')) return false;
        
        jogo.tabuleiro[meioX][meioY] = '.';
    }
   
    // Mover a peca normal
    jogo.tabuleiro[x2][y2] = jogo.tabuleiro[x1][y1];
    jogo.tabuleiro[x1][y1] = '.';

    // ===============================================
    // PROMOÇÃO (Se chegar no final, vira Dama!)
    // ===============================================
    if (jogo.tabuleiro[x2][y2] == 'B' && x2 == 0) {
        jogo.tabuleiro[x2][y2] = 'D'; // Vira Dama Branca (Letra D)
    } else if (jogo.tabuleiro[x2][y2] == 'P' && x2 == 7) {
        jogo.tabuleiro[x2][y2] = 'Q'; // Vira Dama Preta (Letra Q de Queen)
    }

    return true;
}

// LIMPAR TELA
void limparTela() {
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
            if(num >= 0 && num <= 7) return num;
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
