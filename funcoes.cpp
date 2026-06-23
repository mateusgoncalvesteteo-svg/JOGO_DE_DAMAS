#include <iostream>
#include <limits>
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
        cout << "[0] SAIR\n";
        cout << "Opcao: ";

        cin >> opcao;

        if(opcao != '1' && opcao != '0')
        {
            cout << "\nOpcao invalida!\n";
        }

    } while(opcao != '1' && opcao != '0');

    return opcao;
}

// FUNCAO JOGAR
void jogar() { 
    vector<PerfilJogador> listaDePerfis;
    Jogo meuJogo;
    limparTela();

    char jogador1, jogador2;
    char jogadorAtual;
    bool jogoRodando = true;
    bool jogadaValida = false;
    
    cout << "====================================\n";
    cout << "      ESCOLHA SUA EQUIPE\n";
    cout << "====================================\n";

    cout << "[B] Pecas Brancas\n";
    cout << "[P] Pecas Pretas\n";
    cout << "\nJogador 1 escolha: ";

    cin >> jogador1;

    jogador1 = toupper(jogador1);

    while(jogador1 != 'B' && jogador1 != 'P') {
    cout << "\nOpcao invalida!\n";
    cout << "Digite apenas B ou P: ";

    cin >> jogador1;
    jogador1 = toupper(jogador1);
}

    limparTela();

    if (jogador1 == 'B')
        jogador2 = 'P';
    else
        jogador2 = 'B';

    jogadorAtual = 'B';

    cout << "\nJogador 1: " << jogador1;
    cout << "\nJogador 2: " << jogador2;

    cout << "\n\nPartida iniciando...\n";

    inicializarTabuleiro(meuJogo);

    while (jogoRodando) {
        jogadaValida = false;
        mostrarTabuleiro(meuJogo, jogadorAtual);

        cout << "\n================================";
        cout << "\n BRANCAS: " << contarPecas(meuJogo,'B');
        cout << " | PRETAS: " << contarPecas(meuJogo,'P');
        cout << "\n================================\n";
        
        while (!jogadaValida) {
            cout << "\nJogador atual: " << jogadorAtual << endl;

            int x1, y1, x2, y2;

            cout << "Linha origem e Coluna origem (separados por espaco): ";
            x1 = lerCoordenada();
            y1 = lerCoordenada();
             
            cout << "Linha destino e Coluna Destino (separados por espaco): ";
            x2 = lerCoordenada();
            y2 = lerCoordenada();

        bool capturaObrigatoria = jogadorTemCaptura(meuJogo, jogadorAtual);

        if(capturaObrigatoria && !existeCaptura(meuJogo,x1,y1))
        {
            int distancia = abs(x2 - x1);

            if(distancia != 2)
            {
                cout << "\n====================================";
                cout << "\n CAPTURA OBRIGATORIA!";
                cout << "\n Voce precisa comer uma peca.";
                cout << "\n====================================\n";

                continue;
            }
        }
       
        if(moverPeca(meuJogo, x1, y1, x2, y2, jogadorAtual)) {

            cout << "\nMovimento realizado com sucesso!\n";

            jogadaValida = true;
            //guardar o quanto a peca andou
            int distancia = abs(x2-x1);
            // So entra aqui se acabou de capturar
            if(distancia == 2)
            {
            while(existeCaptura(meuJogo,x2,y2)) 
            {
                mostrarTabuleiro(meuJogo,jogadorAtual);

                    cout << "\n====================================";
                    cout << "\n CAPTURA DISPONIVEL!";
                    cout << "\n Voce deve continuar capturando";
                    cout << "\n====================================\n";

                    x1 = x2;
                    y1 = y2;

                    cout << "\nNova linha e coluna destino: ";

                     x2 = lerCoordenada();
                     y2 = lerCoordenada();

                if(!moverPeca(meuJogo,x1,y1,x2,y2,jogadorAtual)) 
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
        cout << "Movimento invalido!\n";
        }
    }
        
        // troca de turno
        if(jogadorAtual == 'B')
            jogadorAtual = 'P';
        else
            jogadorAtual = 'B';

        char sair;
        cout << "\nContinuar jogando? (s/n): ";
        cin >> sair;

        limparTela();

        if(sair == 'n')
        {
            jogoRodando = false;
            
            // ==================================================
            // REGISTAR VENCEDOR (Uso da STL e Recursividade)
            // ==================================================
            cout << "====================================\n";
            cout << "          FIM DE JOGO!\n";
            cout << "====================================\n";
            
            string nomeVencedor;
            cout << "Digite o nome do jogador vencedor (ou 'empate'): ";
            cin >> nomeVencedor;
            
            if (nomeVencedor != "empate") {
                atualizarPerfil(listaDePerfis, nomeVencedor);
                
                // Pausa para o utilizador ler a mensagem de vitória
                cout << "\nPrima qualquer tecla e Enter para voltar ao menu...";
                char pausa;
                cin >> pausa;
            }
        }
    }
}

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
// ==========================================
//          BUSCA E RECURSIVIDADE
// ==========================================
int buscaRecursiva(const vector<PerfilJogador>& perfis, string nomeBuscado, int indiceAtual) {
    if (indiceAtual >= perfis.size()) {
        return -1; 
    }
    
    if (perfis[indiceAtual].nome == nomeBuscado) {
        return indiceAtual; 
    }
    
    return buscaRecursiva(perfis, nomeBuscado, indiceAtual + 1);
}

// ==========================================
//           USO DE STL (VECTOR)
// ==========================================
void atualizarPerfil(vector<PerfilJogador>& perfis, string nomeJogador) {
    int indice = buscaRecursiva(perfis, nomeJogador, 0);

    if (indice != -1) {
        perfis[indice].vitorias++;
        cout << "\nO jogador " << nomeJogador << " ja tinha registo. Vitorias atualizadas para: " << perfis[indice].vitorias << "!\n";
    } else {
        PerfilJogador novoJogador;
        novoJogador.nome = nomeJogador;
        novoJogador.vitorias = 1; 
        
        perfis.push_back(novoJogador); 
        cout << "\nNovo perfil criado para " << nomeJogador << " com 1 vitoria!\n";
    }
}
