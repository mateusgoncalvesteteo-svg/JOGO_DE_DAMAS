#ifndef FUNCOES_H
#define FUNCOES_H
#include <vector>
#include <string>      

using namespace std;

// Struct do Jogo
struct Jogo {
    char tabuleiro[8][8];
};

// Struct do Perfil
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
bool jogadorTemMovimentos(Jogo& jogo, char jogador);
bool verificarFimDeJogo(Jogo& jogo, char jogadorAtual, bool desistiu);
char verificarVencedor(Jogo& jogo, char jogadorAtual, bool desistiu);
int buscaRecursiva(const vector<PerfilJogador>& perfis, string nomeBuscado, int indiceAtual);
void atualizarPerfil(vector<PerfilJogador>& perfis, string nomeJogador);
void limparTela();
int lerCoordenada();

#endif
