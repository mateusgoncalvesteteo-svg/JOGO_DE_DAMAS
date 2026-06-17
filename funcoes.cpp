#include <iostream>
#include <limits>
#include "funcoes.h"

using namespace std;

// ===============================
// MENU
// ===============================
char menu() {
    char opcao;
    do {
        cout << "================================\n";
        cout << "DAMAS\n";
        cout << "================================\n";
        cout << "1. PLAY\n";
        cout << "Opcao: ";
        cin >> opcao;

        if(opcao != '1') {
            cout << "Apenas os numeros da lista!\n";
        }
    } while(opcao != '1');

    return opcao;
}

// ===============================
// INICIALIZAÇÃO DO  TABULEIRO
// ===============================
void inicializarTabuleiro(Jogo& jogo) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 1) {
                if (i < 3)
                    jogo.tabuleiro[i][j] = 'P'; // pretas no topo
                else if (i > 4)
                    jogo.tabuleiro[i][j] = 'B'; // brancas embaixo
                else
                    jogo.tabuleiro[i][j] = '.'; // casa vazia jogável
            } else {
                jogo.tabuleiro[i][j] = ' '; // casa inválida
            }
        }
    }
}

// ===============================
// MOSTRAR O TABULEIRO
// ===============================
void mostrarTabuleiro(Jogo& jogo, char player) {
    cout << "\n========================\n";
    cout << "  ";
    for(int j = 0; j < 8; j++) {
        cout << " " << j << " ";
    }
    cout << endl;

    if (player == 'B') {
        for (int i = 0; i < 8; i++) {
            cout << i << " ";
            for (int j = 0; j < 8; j++)
                cout << "[" << jogo.tabuleiro[i][j] << "]";
            cout << endl;
        }
    } else {
        for (int i = 7; i >= 0; i--) {
            cout << i << " ";
            for (int j = 0; j < 8; j++)
                cout << "[" << jogo.tabuleiro[i][j] << "]";
            cout << endl;
        }
    }
    cout << "========================\n";
}

// ===============================
// MOVIMENTACÃO DAS PECAS
// ===============================
bool moverPeca(Jogo& jogo, int x1, int y1, int x2, int y2, char jogadorAtual) {
    // Passo 1 -> verificar se existem as coordenadas
    if(x1 < 0 || x1 > 7 || y1 < 0 || y1 > 7 || x2 < 0 || x2 > 7 || y2 < 0 || y2 > 7) {
        return false;
    }

    // VerificaO se a peca pertence ao jogador
    if(jogo.tabuleiro[x1][y1] != jogadorAtual) {
        return false;
    }

    // Verificar se no destino alvo ja nao tem uma peca
    if(jogo.tabuleiro[x2][y2] != '.') {
        return false;
    }

    // NOVA REGRA: Verificar se andou exatamente 1 casa na diagonal
    int diffX = x2 - x1;
    int diffY = y2 - y1;
    
    // Deixando o valor positivo (módulo) sem usar bibliotecas difíceis
    if (diffX < 0) diffX = -diffX; 
    if (diffY < 0) diffY = -diffY;

    // Se a diferença de casas não for exatamente 1 em X e 1 em Y, não é diagonal!
    if (diffX != 1 || diffY != 1) {
        return false;
    }

    // Movimentação da peça
    jogo.tabuleiro[x2][y2] = jogo.tabuleiro[x1][y1];
    jogo.tabuleiro[x1][y1] = '.';

    return true;
}

// ===============================
// LIMPAR TELA E LER COORDENADAS
// ===============================
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int lerCoordenada() {
    int num;
    while (true) {
        if (cin >> num) {
            if(num >= 0 && num <= 7) {
                return num;
            }
            cout << "Digite um numero entre 0 e 7: ";
        } else {
            cout << "Digite apenas numeros: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// ===============================
// JOGO (Loop Principal)
// ===============================
void jogar() {
    limparTela();

    // Criamos a nossa variável baseada na Struct
    Jogo meuJogo; 

    char jogador1, jogador2;
    char jogadorAtual;
    bool jogoRodando = true;

    cout << "Digite P para time preto ou B para time branco: ";
    cin >> jogador1;
    limparTela();

    if (jogador1 == 'B') jogador2 = 'P';
    else jogador2 = 'B';

    jogadorAtual = 'B';

    // Passamos a struct para inicializar
    inicializarTabuleiro(meuJogo);

    while (jogoRodando) {
        mostrarTabuleiro(meuJogo, jogadorAtual);
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

        // Passamos a struct para tentar mover as peca
        if(moverPeca(meuJogo, x1, y1, x2, y2, jogadorAtual)) {
            cout << "Movimento realizado com sucesso!\n";
            // Troca de turno só acontece se o movimento deu certo!
            if(jogadorAtual == 'B') jogadorAtual = 'P';
            else jogadorAtual = 'B';
        } else {
            cout << "Movimento invalido!\n";
        }
        
        char sair;
        cout << "\nContinuar jogando? (s/n): ";
        cin >> sair;
        limparTela();

        if(sair == 'n') {
            jogoRodando = false;
        }
    }
}
