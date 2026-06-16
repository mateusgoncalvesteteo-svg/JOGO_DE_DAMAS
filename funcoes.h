#ifndef FUNCOES_H
#define FUNCOES_H
// ===============================
// MENU
// ===============================
char menu();
void jogar();
// ===============================
// TABULEIRO
// ===============================
void inicializarTabuleiro();
void mostrarTabuleiro(char player);

// ===============================
// JOGO (PASSO 1)//dividir em passos torna mais facil
// ===============================
bool moverPeca(int x1, int y1, int x2, int y2, char jogadorAtual);
bool jogoTerminou();

// ===============================
// UTILITÁRIO (futuro)
// ===============================
int contarPecas(char peca);// mais pra frente eu faço (Mateus)
// ===============================
// LIMPAR TELA
// ===============================
void limparTela();

#endif
