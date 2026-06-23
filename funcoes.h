#ifndef FUNCOES_H
#define FUNCOES_H

#include <string>
#include <vector>

using namespace std;

// Struct jogo
struct Jogo {
    char tabuleiro[8][8];
};

// Perfil do Jogador
struct PerfilJogador {
    string nome;
    int vitorias;
};

// Declaração das funções
char menu();
void jogar();
void inicializarTabuleiro(Jogo& jogo);
void mostrarTabuleiro(Jogo& jogo, char player);
bool moverPeca(Jogo& jogo, int x1, int y1, int x2, int y2, char jogadorAtual);
bool moverDama(Jogo& jogo, int x1, int y1, int x2, int y2, char jogadorAtual);
bool existeCaptura(Jogo& jogo, int x, int y);
bool jogadorTemCaptura(Jogo& jogo, char jogadorAtual);
int contarPecas(Jogo& jogo, char jogador);
void limparTela();
int lerCoordenada();
int buscaRecursiva(const vector<PerfilJogador>& perfis, string nomeBuscado, int indiceAtual);
void atualizarPerfil(vector<PerfilJogador>& perfis, string nomeJogador);

#endif
