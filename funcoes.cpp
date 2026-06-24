#include <iostream>
#include <limits>
#include <fstream>//para ofstream
#include <vector>
#include <string> 
#include <cctype>//para toupper
#include <cstdlib> //  para a função abs() funcionar perfeitamente
#include "funcoes.h"

using namespace std;

// MENU (estilizado, bonitao)
char menu()
{
    char opcao;

    do
    {
        limparTela();

        cout << "========================================\n";
        cout << "DDDD|    AAA|   MM|  MM|   AAA|    SSSS|\n";
        cout << "D|  D|  A|  A|  MMM|MMM|  A|  A|  S|    \n";
        cout << "D|  D|  AAAAA|  MM M|MM|  AAAAA|   SSS| \n";
        cout << "D|  D|  A|  A|  MM|  MM|  A|  A|      S|\n";
        cout << "DDDD|   A|  A|  MM|  MM|  A|  A|  SSSSS|\n";
        cout << "========================================\n";

        cout << "====================================\n";
        cout << "          MENU PRINCIPAL\n";
        cout << "====================================\n";
        cout << "[1] PLAY\n";
        cout << "[2] RANKING\n";
        cout << "[0] SAIR\n";
        cout << "Opcao: ";

        cin >> opcao;

        if(opcao != '1' && opcao != '2' && opcao != '0')
        {
            cout << "\nOpcao invalida!\n";
        }

    } while(opcao != '1' && opcao != '2' && opcao != '0');

    return opcao;
}

// FUNCAO JOGAR
void jogar(vector<PerfilJogador>& perfis) {
Jogo meuJogo;
limparTela();

char jogador1, jogador2;
char jogadorAtual;
bool jogoRodando = true;
bool jogadaValida = false;
bool desistiu = false;

cout << "====================================\n";
cout << "      ESCOLHA SUA EQUIPE\n";
cout << "====================================\n";

cout << "[B] Pecas Brancas\n";
cout << "[P] Pecas Pretas\n";
cout << "\nJogador 1 escolha: ";

cin >> jogador1;
jogador1 = toupper(jogador1);

while(jogador1 != 'B' && jogador1 != 'P')
{
    cout << "\nOpcao invalida!\n";
    cout << "Digite apenas B ou P: ";

    cin >> jogador1;
    jogador1 = toupper(jogador1);
}

limparTela();

// definir equipe do jogador 2
if (jogador1 == 'B')
    jogador2 = 'P';
else
    jogador2 = 'B';

jogadorAtual = 'B';

cout << "\nJogador 1: " << jogador1;
cout << "\nJogador 2: " << jogador2;
cout << "\n\nPartida iniciando...\n";

inicializarTabuleiro(meuJogo);

while(jogoRodando)
{
    jogadaValida = false;

    mostrarTabuleiro(meuJogo, jogadorAtual);

    cout << "\n================================";
    cout << "\n BRANCAS: " << contarPecas(meuJogo,'B');
    cout << " | PRETAS: " << contarPecas(meuJogo,'P');
    cout << "\n================================\n";

    while(!jogadaValida)
    {
        cout << "\nJogador atual: " << jogadorAtual << endl;

        int x1,y1,x2,y2;

        cout << "Linha origem e Coluna origem: ";
        x1 = lerCoordenada();
        y1 = lerCoordenada();

        cout << "Linha destino e Coluna destino: ";
        x2 = lerCoordenada();
        y2 = lerCoordenada();

        bool capturaObrigatoria =
        jogadorTemCaptura(meuJogo,jogadorAtual);

        if(capturaObrigatoria &&
           !existeCaptura(meuJogo,x1,y1))
        {
            int distancia = abs(x2-x1);

            if(distancia != 2)
            {
                cout << "\n================================";
                cout << "\n CAPTURA OBRIGATORIA!";
                cout << "\n Voce precisa comer uma peca";
                cout << "\n================================\n";

                continue;
            }
        }

        if(moverPeca(meuJogo,x1,y1,x2,y2,jogadorAtual))
        {
            cout << "\nMovimento realizado com sucesso!\n";

            jogadaValida = true;

            // guardar o quanto a peça andou
            int distancia = abs(x2-x1);

            // só entra aqui se capturou
            if(distancia == 2)
            {
                while(existeCaptura(meuJogo,x2,y2))
                {
                    mostrarTabuleiro(meuJogo,jogadorAtual);

                    cout << "\n================================";
                    cout << "\n CAPTURA DISPONIVEL!";
                    cout << "\n Voce deve continuar capturando";
                    cout << "\n================================\n";

                    x1 = x2;
                    y1 = y2;

                    cout << "\nNova linha e coluna destino: ";

                    x2 = lerCoordenada();
                    y2 = lerCoordenada();

                    if(!moverPeca(
                        meuJogo,
                        x1,y1,
                        x2,y2,
                        jogadorAtual))
                    {
                        cout << "\nMovimento invalido!\n";

                        x2 = x1;
                        y2 = y1;
                    }
                }
            }
        }
        else
        {
            cout << "\nMovimento invalido!\n";
        }

    } // fim while(!jogadaValida)


    // perguntar se quer continuar
    char sair;

    cout << "\nContinuar jogando? (s/n): ";
    cin >> sair;

    if(sair == 'n')
    {
        desistiu = true;
    }

    // verificar se a partida terminou
    if(verificarFimDeJogo(
        meuJogo,
        jogadorAtual,
        desistiu))
    {
        char vencedor;

        vencedor = verificarVencedor(meuJogo,jogadorAtual,desistiu);

        cout << "\n================================";
        cout << "\n        FIM DE JOGO";
        cout << "\n================================";
        cout << "\nVencedor: " << vencedor;
        cout << "\n================================\n";

        string nomeVencedor;

        cout << "\nDigite o nick do Vencedor: ";
        cin >> nomeVencedor;

        atualizarPerfil(perfis, nomeVencedor);

        jogoRodando = false;

        cout << "\nPressione ENTER...";
        cin.ignore();//voltar ao menu
    }
    else
    {
        // troca de turno somente se continuar
        if(jogadorAtual == 'B')
            jogadorAtual = 'P';
        else
            jogadorAtual = 'B';
    }

    limparTela();

} // fim while(jogoRodando)

} // fim jogar

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

// MOVIMENTACAO DA DAMA
bool moverDama(Jogo& jogo, int x1, int y1, int x2, int y2, char jogadorAtual) {
    char peca = jogo.tabuleiro[x1][y1];
    
    int diffX = x2 - x1;
    int diffY = y2 - y1;

    // Verificar se o movimento é diagonal
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

// MOVIMENTACAO DAS PECAS
bool moverPeca(Jogo& jogo, int x1, int y1, int x2, int y2, char jogadorAtual) {
    // 1. Verificar se as coordenadas existem
    if(x1 < 0 || x1 > 7 || y1 < 0 || y1 > 7 || 
       x2 < 0 || x2 > 7 || y2 < 0 || y2 > 7 ) {
        return false;
    }
    
    char peca = jogo.tabuleiro[x1][y1];

    // Verificar se a peça pertence ao jogador (incluindo Damas 'D' e 'Q')
    if (jogadorAtual == 'B' && (peca != 'B' && peca != 'D')) return false;
    if (jogadorAtual == 'P' && (peca != 'P' && peca != 'Q')) return false;
    
    // Verificar se destino já não tem uma peca
    if(jogo.tabuleiro[x2][y2] != '.') {
        return false;
    }

    // Se for Dama , repassar a funcao para ela
    if (peca == 'D' || peca == 'Q') {
        return moverDama(jogo, x1, y1, x2, y2, jogadorAtual);
    }
    
    // Lógica da peca normal
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

    // PROMOCAO DA DAMA
    if (jogo.tabuleiro[x2][y2] == 'B' && x2 == 0) {
        jogo.tabuleiro[x2][y2] = 'D'; // Vira Dama Branca (Letra D)
    } else if (jogo.tabuleiro[x2][y2] == 'P' && x2 == 7) {
        jogo.tabuleiro[x2][y2] = 'Q'; // Vira Dama Preta (Letra Q de Queen)
    }

    return true;
}

//UPGRADE DE COMER PECA(possibilidade de comer mais de uma peca por turno)
bool existeCaptura(Jogo& jogo, int x, int y)
{
    // descobrir qual peça está na posição atual
    char peca = jogo.tabuleiro[x][y];

    // matriz que guarda direções
    int direcoes[4][2];
    int quantidade;

    // definir direções dependendo da peça
    if(peca == 'B')
    {
        quantidade = 2;

        // cima-esquerda
        direcoes[0][0] = -1;
        direcoes[0][1] = -1;

        // cima-direita
        direcoes[1][0] = -1;
        direcoes[1][1] = 1;
    }

    else if(peca == 'P')
    {
        quantidade = 2;

        // baixo-esquerda
        direcoes[0][0] = 1;
        direcoes[0][1] = -1;

        // baixo-direita
        direcoes[1][0] = 1;
        direcoes[1][1] = 1;
    }

    else // D ou Q (damas)
    {
        quantidade = 4;

        direcoes[0][0] = -1;
        direcoes[0][1] = -1;

        direcoes[1][0] = -1;
        direcoes[1][1] = 1;

        direcoes[2][0] = 1;
        direcoes[2][1] = -1;

        direcoes[3][0] = 1;
        direcoes[3][1] = 1;
    }

    // testar cada direção possível
    for(int i = 0; i < quantidade; i++)
    {
        int dx = direcoes[i][0];
        int dy = direcoes[i][1];

        // posição da peça que pode ser comida
        int meioX = x + dx;
        int meioY = y + dy;

        // posição depois da peça
        int destinoX = x + (dx * 2);
        int destinoY = y + (dy * 2);

        // impedir sair do tabuleiro
        if(meioX < 0 || meioX > 7 ||
           meioY < 0 || meioY > 7 ||
           destinoX < 0 || destinoX > 7 ||
           destinoY < 0 || destinoY > 7)
        {
            continue;
        }

        char pecaMeio = jogo.tabuleiro[meioX][meioY];

        // verificar inimigo
        bool inimigo = false;

        if(peca == 'B' || peca == 'D')
        {
            if(pecaMeio == 'P' || pecaMeio == 'Q')
                inimigo = true;
        }

        if(peca == 'P' || peca == 'Q')
        {
            if(pecaMeio == 'B' || pecaMeio == 'D')
                inimigo = true;
        }

        // inimigo no meio + espaço vazio depois
        if(inimigo &&
           jogo.tabuleiro[destinoX][destinoY] == '.')
        {
            return true;
        }
    }

    return false;
}

//CAPTURA OBRIGATORIA
bool jogadorTemCaptura(Jogo& jogo, char jogadorAtual) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            char peca = jogo.tabuleiro[i][j];

            // peças do jogador branco
            if(jogadorAtual == 'B' && (peca == 'B' || peca == 'D')) {
                if(existeCaptura(jogo, i, j)) {
                    return true;
                }
            }

            // peças do jogador preto
            if(jogadorAtual == 'P' && (peca == 'P' || peca == 'Q')) {
                if(existeCaptura(jogo, i, j)) {
                    return true;
                }
            }
        }
    }

    return false;
}

//CONTAR PECAS
int contarPecas(Jogo& jogo, char jogador)
{
    int quantidade = 0;

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            char peca = jogo.tabuleiro[i][j];

            // contar peças brancas
            if(jogador == 'B')
            {
                if(peca == 'B' || peca == 'D')
                {
                    quantidade++;
                }
            }

            // contar peças pretas
            else if(jogador == 'P')
            {
                if(peca == 'P' || peca == 'Q')
                {
                    quantidade++;
                }
            }
        }
    }

    return quantidade;
}

//VERIFICAR MOVIMENTOS
bool jogadorTemMovimentos(Jogo& jogo, char jogador)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            char peca = jogo.tabuleiro[i][j];

            // verificar peças do jogador branco
            if(jogador == 'B' &&
              (peca == 'B' || peca == 'D'))
            {
                // verificar captura
                if(existeCaptura(jogo,i,j))
                {
                    return true;
                }

                // verificar movimento simples da peça branca
                if(peca == 'B')
                {
                    if(i-1 >= 0)
                    {
                        if(j-1 >= 0 &&
                           jogo.tabuleiro[i-1][j-1] == '.')
                        {
                            return true;
                        }

                        if(j+1 <= 7 &&
                           jogo.tabuleiro[i-1][j+1] == '.')
                        {
                            return true;
                        }
                    }
                }

                // verificar movimento da dama branca
                if(peca == 'D')
                {
                    return true;
                }
            }

            // verificar peças do jogador preto
            if(jogador == 'P' &&
              (peca == 'P' || peca == 'Q'))
            {
                // verificar captura
                if(existeCaptura(jogo,i,j))
                {
                    return true;
                }

                // verificar movimento simples peça preta
                if(peca == 'P')
                {
                    if(i+1 <= 7)
                    {
                        if(j-1 >= 0 &&
                           jogo.tabuleiro[i+1][j-1] == '.')
                        {
                            return true;
                        }

                        if(j+1 <= 7 &&
                           jogo.tabuleiro[i+1][j+1] == '.')
                        {
                            return true;
                        }
                    }
                }

                // verificar dama preta
                if(peca == 'Q')
                {
                    return true;
                }
            }
        }
    }

    return false;
}

//VERIFICAR DESISTENCIA
bool verificarFimDeJogo(Jogo& jogo,char jogadorAtual,bool desistiu)
{
    // desistência
    if(desistiu)
    {
        return true;
    }

    // sem peças
    if(contarPecas(jogo,'B') == 0)
    {
        return true;
    }

    if(contarPecas(jogo,'P') == 0)
    {
        return true;
    }

    // travado
    if(!jogadorTemMovimentos(jogo,jogadorAtual))
    {
        return true;
    }

    // continua
    return false;
}

//VERIFICAR GANHADOR
char verificarVencedor(Jogo& jogo,char jogadorAtual,bool desistiu)
{
    // desistiu
    if(desistiu)
    {
        if(jogadorAtual == 'B')
            return 'P';
        else
            return 'B';
    }

    // sem peças
    if(contarPecas(jogo,'B') == 0)
        return 'P';

    if(contarPecas(jogo,'P') == 0)
        return 'B';

    // travado
    if(!jogadorTemMovimentos(jogo,jogadorAtual))
    {
        if(jogadorAtual == 'B')
            return 'P';
        else
            return 'B';
    }

    return 'N'; // ninguém venceu ainda
}

// BUSCA E RECURSIVIDADE
int buscaRecursiva(const vector<PerfilJogador>& perfis,string nomeBuscado,int indiceAtual)
{
    if(indiceAtual >= perfis.size())
        return -1;

    if(perfis[indiceAtual].nome == nomeBuscado)
        return indiceAtual;

    return buscaRecursiva(perfis,nomeBuscado,indiceAtual+1);
}

// USO DE STL (VECTOR)
void atualizarPerfil(vector<PerfilJogador>& perfis,string nomeJogador)
{
    int indice = buscaRecursiva(perfis,nomeJogador,0);

    if(indice!=-1)
    {
        perfis[indice].vitorias++;

        cout<<"\nVitorias atualizadas!\n";
    }
    else
    {
        PerfilJogador novoJogador;
        novoJogador.nome = nomeJogador;
        novoJogador.vitorias=1;
        perfis.push_back(
        novoJogador);
        cout<<"\nNovo perfil criado!\n";
    }

    salvarPerfis(perfis); //salvar imediatamente
}

// SALVAR PERFIS EM ARQUIVO
void salvarPerfis(const vector<PerfilJogador>& perfis) {
    ofstream arquivo("ranking.txt");//nome do arquivo

    if(!arquivo.is_open()) {//se nao foi aberto
        
        cout << "\nErro ao salvar ranking\n";
        return;
    }

    for(const auto& perfil : perfis) {//igual ao exemplo dado em sala de aula
        //mostrar o nome e as vitorias
        arquivo << perfil.nome << " " << perfil.vitorias << endl;
    }

    arquivo.close();//fechar o arquivo depois de aberto
}

//CARREGAR PERFIS DO ARQUIVO
vector<PerfilJogador> carregarPerfis() {

    vector<PerfilJogador> perfis;
    ifstream arquivo("ranking.txt");//carregar o perfil nesse aruivo

    if(!arquivo.is_open()) {//se nao foi aberto

    return perfis;//arquivo vazio retorna nada
    }

    string nome;
    int vitorias;

    while(arquivo >> nome >> vitorias) {

        PerfilJogador perfil;
        perfil.nome = nome;
        perfil.vitorias = vitorias;
        perfis.push_back(perfil);//salvar tudo em perfis
    }

    arquivo.close();
    return perfis;
}

//RANKING
void exibirRanking(const vector<PerfilJogador>& perfis) {

    limparTela();

     
    cout << "====================================\n";
    cout << "       RANKING DE VENCEDORES\n";
    cout << "====================================\n";

    if(perfis.empty()) { //se estiver vazio
        cout << "Nenhum vencedor registrado ainda!\n";
    } else {
        cout << "Pos | Nick           | Vitorias\n";
        cout << "====================================\n";

        for(int i = 0; i<perfis.size(); i++) {
            cout << i+1 << "   | " << perfis[i].nome << " | " << perfis[i].vitorias << endl;

        }
    }

    cout << "====================================\n";
    cout << "\nPressione ENTER para voltar...";
    cin.ignore();
    cin.get();
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
