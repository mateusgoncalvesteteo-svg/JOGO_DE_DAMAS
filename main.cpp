#include <iostream>
#include "funcoes.h"

using namespace std;

int main()
{
    char opcao = menu();

    switch(opcao)
    {
        case '1':
            jogar();
            break;
    }

    return 0;
}
