#include <iostream>
#include "funcoes.h" 

using namespace std;

int main() {
    // Chamar o menuu
    char opcaoEscolhida = menu();

    // Se o usuário digitou somente 1, inicializa o jogo
    if (opcaoEscolhida == '1') {
        jogar();
    }

    cout << "Obrigado por jogar!\n";
    return 0;
}
