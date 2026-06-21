#ifndef FUNCOES_H
#define FUNCOES_H

// Criamos a Struct um dos pedidos do prof
struct Jogo {
    char tabuleiro[8][8];
};

// Declaração das funções
char menu();
void jogar();
void inicializarTabuleiro(Jogo& jogo);
void mostrarTabuleiro(Jogo& jogo, char player);
bool moverPeca(Jogo& jogo, int x1, int y1, int x2, int y2, char jogadorAtual);
bool moverDama(Jogo& jogo, int x1, int y1, int x2, int y2, char jogadorAtual); // <-- Função da Dama adicionada!
void limparTela();
int lerCoordenada();

#endif
