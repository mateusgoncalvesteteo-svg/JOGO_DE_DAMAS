#include <iostream>
#include "funcoes.h"
using namespace std;

int main() {
    vector<PerfilJogador> perfis = carregarPerfis(); // Carregar ranking
    
    char opcaoEscolhida;
    
    do {
        opcaoEscolhida = menu();
        
        switch(opcaoEscolhida)
        {
            case '1':
                jogar(perfis);
                perfis = carregarPerfis(); // Recarregar após partida
                salvarPerfis(perfis);
                break;
                
            case '2':
                exibirRanking(perfis);
                break;
                
            case '0':
                cout << "\nEncerrando jogo...\n";
                break;
        }
        
    } while(opcaoEscolhida != '0');
    
    cout << "Obrigado por jogar!\n";
    return 0;
}
