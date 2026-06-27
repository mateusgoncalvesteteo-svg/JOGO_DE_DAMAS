#include <iostream>
#include "funcoes.h"
using namespace std;

int main() {
    vector<PerfilJogador> perfis = carregarPerfis();
    
    char opcaoEscolhida;
    
    do {
        opcaoEscolhida = menu();
        
        switch(opcaoEscolhida)
        {
            case '1':
                jogar(perfis);
                perfis = carregarPerfis();
                salvarPerfis(perfis);
                break;
                
            case '2':
                exibirRanking(perfis);
                break;
            
            case '3':
            {
                string nomeJogador;
                cout << "Digite o nome do jogador: ";
                cin >> nomeJogador;
                carregarEExibirHistorico(nomeJogador);
                break;
            }
                
            case '0':
                cout << "\nEncerrando jogo...\n";
                break;
        }
        
    } while(opcaoEscolhida != '0');
    
    cout << "Obrigado por jogar!\n";
    return 0;
}
