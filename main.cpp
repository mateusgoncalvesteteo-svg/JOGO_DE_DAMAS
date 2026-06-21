#include <iostream>
#include "funcoes.h"

using namespace std;

int main() {
    // Chama o menu
    char opcaoEscolhida = menu();

    // Se o usuário digitou 1, inicia o jogo
    switch(opcaoEscolhida)
{
    case '1':
        jogar();
        break;

    case '0':
        cout << "\nEncerrando jogo...\n";
        break;
    }

    cout << "Obrigado por jogar!\n";
    return 0;
}
