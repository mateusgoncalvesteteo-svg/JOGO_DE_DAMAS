#ifndef FUNCOES_H
#define FUNCOES_H

// ===============================
// TABULEIRO
// ===============================
void inicializarTabuleiro();
void mostrarTabuleiro(char player);

// ===============================
// JOGO (PASSO 1)
// ===============================
bool moverPeca(int x1, int y1, int x2, int y2, char jogadorAtual);
bool jogoTerminou();

// ===============================
// UTILITÁRIO (opcional mas recomendado)
// ===============================
int contarPecas(char peca);

#endif