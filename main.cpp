#include <iostream>
#include "funcoes.h"

using namespace std;

int main() {
    // Chama o menu
    char opcaoEscolhida = menu();

    // Se o usuário digitou 1, inicia o jogo
    if (opcaoEscolhida == '1') {
        jogar();
    }

    cout << "Obrigado por jogar!\n";
    return 0;
}
