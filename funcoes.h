#ifndef funcoes_h
#define funcoes_h

// a Struct 
    char tabuleiro[8][8];
};

// Declaração das funções
char menu();
void jogar();
void inicializarTabuleiro(Jogo& jogo);
void mostrarTabuleiro(Jogo& jogo, char player);
bool moverPeca(Jogo& jogo, int x1, int y1, int x2, int y2, char jogadorAtual);
void limparTela();
int lerCoordenada();

#endif
