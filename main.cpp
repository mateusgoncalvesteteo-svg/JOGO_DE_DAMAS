#include <iostream>
#include "funcoes.h"

using namespace std;

int main() {
    char jogador1, jogador2;
    char jogadorAtual;
    bool jogoRodando = true;

    // ===============================
    // 1. ESCOLHA DE COR DO JOGADOR 1
    // ===============================
    cout << "Digite P para time preto ou B para time branco: ";
    cin >> jogador1;

    // jogador 2 recebe automaticamente a outra cor
    if (jogador1 == 'B')
        jogador2 = 'P';
    else
        jogador2 = 'B';

    // branco sempre começa
    jogadorAtual = 'B';

    // ===============================
    // 2. INICIALIZA TABULEIRO
    // ===============================
    inicializarTabuleiro();

    // ===============================
    // 3. LOOP PRINCIPAL DO JOGO
    // ===============================
    while (jogoRodando) {

        // mostra tabuleiro a cada rodada
        mostrarTabuleiro(jogadorAtual);

        cout << "\nJogador atual: " << jogadorAtual << endl;

        // ======================================
        // MOVIMENTO DE PEÇAS
        // ======================================
        int x1, y1, x2, y2;

        cout << "Linha origem: ";
        cin >> x1;

        cout << "Coluna origem: ";
        cin >> y1;

        cout << "Linha destino: ";
        cin >> x2;

        cout << "Coluna destino: ";
        cin >> y2;

        if (moverPeca(x1, y1, x2, y2, jogadorAtual)) {
            cout << "Movimento realizado com sucesso!\n";
        } else {
            cout << "Movimento invalido\n";
        }

        // ===============================
        // 4. TROCA DE JOGADOR (TURNOS)
        // ===============================
        if (jogadorAtual == 'B')
            jogadorAtual = 'P';
        else
            jogadorAtual = 'B';

        // ===============================
        // 5. CONDIÇÃO DE SAÍDA (TEMPORÁRIA)
        // ===============================
        char sair;
        cout << "\nContinuar jogando? (s/n): ";
        cin >> sair;

        if (sair == 'n') {
            jogoRodando = false;
        }
    }

    cout << "Jogo encerrado...\n";
    return 0;
}