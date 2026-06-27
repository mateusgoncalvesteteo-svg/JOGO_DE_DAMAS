#ifndef FUNCOES_H
#define FUNCOES_H
#include <vector>
#include <string>      

using namespace std;
//structs usadas
struct Jogada {
    int rodada;
    char jogador;
    int x1, y1;
    int x2, y2;
    bool foi_captura;
};

struct Jogo {
    char tabuleiro[8][8];
    vector<Jogada> historico;
    int rodada;
};

struct PerfilJogador {
    string nome;
    int vitorias;
};

// Declaração das funções
char menu();
void jogar(vector<PerfilJogador>& perfis);
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
void salvarPerfis(const vector<PerfilJogador>& perfis);
vector<PerfilJogador> carregarPerfis();
void exibirRanking(const vector<PerfilJogador>& perfis);
void limparTela();
int lerCoordenada();
void registrarJogada(Jogo& jogo, int x1, int y1, int x2, int y2, char jogador, bool captura);
void salvarHistoricoPartida(const Jogo& jogo, const string& nomeVencedor);
void exibirHistorico(const Jogo& jogo);
void carregarEExibirHistorico(const string& nomeJogador);

#endif
