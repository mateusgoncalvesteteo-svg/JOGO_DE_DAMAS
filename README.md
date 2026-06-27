# JOGO DE DAMAS

> Um jogo de damas funcional desenvolvido em C++ com persistência de dados, histórico de partidas e algoritmos de busca e ordenação.

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Language](https://img.shields.io/badge/language-C%2B%2B-orange.svg)
![Status](https://img.shields.io/badge/status-Completo-brightgreen.svg)

## Descrição
## Avaliação

Este é o **Projeto Final da Unidade 3** da disciplina de Algoritmos e Programação.

> **Nota:** Este projeto contou com auxílio de IA para formatação, correção de erros, dúvidas técnicas e melhorias gerais. O código foi desenvolvido manualmente pelo autor.

Implementação completa de um jogo de damas 8x8 em terminal, desenvolvido como Projeto Final da disciplina de Algoritmos e Programação. O sistema inclui:

- **Jogo completo**: Regras de damas, movimentos, capturas e promoção de damas
- **Persistência**: Ranking de jogadores e histórico de partidas salvo em arquivos
- **Algoritmos**: Busca recursiva, busca binária e ordenação
- **Robustez**: Validação de entrada e tratamento de erros

## Requisitos Cumpridos

- ✅ **Modularização**: Código organizado em `main.cpp`, `funcoes.h`, `funcoes.cpp`
- ✅ **STL**: Uso de `vector<PerfilJogador>` e `vector<Jogada>`
- ✅ **Persistência**: Arquivos ASCII (`ranking.txt`, `historico_[nome].txt`)
- ✅ **Structs**: `Jogo`, `Jogada`, `PerfilJogador`
- ✅ **Algoritmos**: 
  - Busca Recursiva: `buscaRecursiva()`
  - Busca Binária: `buscaBinaria()`
  - Ordenação: `ordenaRankingPorVitorias()` (Bubble Sort)
- ✅ **Recursividade**: Implementada em `buscaRecursiva()`
- ✅ **Try-catch**: Tratamento de erros em operações de arquivo

## Instalação

### Pré-requisitos

- Compilador C++ (MinGW, GCC, Clang)
- Sistema Operacional: Windows, Linux ou macOS

### Compilar

```bash
g++ -o damas main.cpp funcoes.cpp
```

Ou com Make:

```bash
make
```

### Executar

```bash
./damas
```

## Como Jogar

### Menu Principal

```
========================================
DDDD|    AAA|   MM|  MM|   AAA|    SSSS|
D|  D|  A|  A|  MMM|MMM|  A|  A|  S|    
D|  D|  AAAAA|  MM M|MM|  AAAAA|   SSS| 
D|  D|  A|  A|  MM|  MM|  A|  A|      S|
DDDD|   A|  A|  MM|  MM|  A|  A|  SSSSS|
========================================

[1] PLAY      - Iniciar nova partida
[2] RANKING   - Ver ranking de vencedores
[3] HISTORICO - Consultar histórico de partidas
[4] REGRAS    - Ler regras do jogo
[5] CREDITOS  - Ver créditos do projeto
[0] SAIR      - Encerrar programa
```

### Jogando

1. **Escolha sua cor**: Brancas (B) ou Pretas (P)
2. **Mova as peças**: 
   - Digite linha origem (0-7) e coluna origem (0-7)
   - Digite linha destino (0-7) e coluna destino (0-7)
3. **Regras**:
   - Peças andam 1 casa na diagonal para frente
   - Damas andam qualquer distância na diagonal
   - Captura é obrigatória quando disponível
   - Peça que chega na linha oposta vira dama

### Tabuleiro

```
========================
    0   1   2   3   4   5   6   7  
 0 [ ][P][ ][P][ ][P][ ][P]
 1 [P][ ][P][ ][P][ ][P][ ]
 2 [ ][P][ ][P][ ][P][ ][P]
 3 [ ][ ][ ][ ][ ][ ][ ][ ]
 4 [ ][ ][ ][ ][ ][ ][ ][ ]
 5 [B][ ][B][ ][B][ ][B][ ]
 6 [ ][B][ ][B][ ][B][ ][B]
 7 [B][ ][B][ ][B][ ][B][ ]
========================
```

- `B` = Peça Branca
- `P` = Peça Preta
- `D` = Dama Branca
- `Q` = Dama Preta (Queen)
- `.` = Casa vazia
- `[ ]` = Casa não-jogável

## Arquitetura

### Estrutura de Pastas

```
JOGO_DE_DAMAS/
├── main.cpp           # Função principal e menu
├── funcoes.cpp        # Implementação das funções
├── funcoes.h          # Declarações e structs
├── ranking.txt        # Arquivo de ranking (criado ao jogar)
├── historico_*.txt    # Arquivos de histórico por jogador
├── Makefile           # Script de compilação
└── README.md          # Este arquivo
```

### Estrutura de Dados

#### Struct Jogada
```cpp
struct Jogada {
    int rodada;
    char jogador;       // 'B' ou 'P'
    int x1, y1;         // Posição origem
    int x2, y2;         // Posição destino
    bool foi_captura;
};
```

#### Struct Jogo
```cpp
struct Jogo {
    char tabuleiro[8][8];
    vector<Jogada> historico;
    int rodada;
};
```

#### Struct PerfilJogador
```cpp
struct PerfilJogador {
    string nome;
    int vitorias;
};
```

### Fluxo de Execução

```
main()
  ├─ carregarPerfis() → Carrega ranking.txt
  └─ menu()
      ├─ [1] PLAY
      │   ├─ jogar()
      │   ├─ inicializarTabuleiro() → limpa histórico
      │   ├─ Loop de turnos
      │   ├─ moverPeca() → registrarJogada()
      │   ├─ verificarFimDeJogo()
      │   ├─ salvarHistoricoPartida() → cria historico_[nome].txt
      │   └─ atualizarPerfil() → salvarPerfis()
      │
      ├─ [2] RANKING
      │   └─ exibirRanking()
      │
      ├─ [3] HISTORICO
      │   ├─ ordenaRankingPorVitorias() → Bubble Sort
      │   ├─ buscaBinaria() → Procura jogador
      │   └─ Exibe historico_[nome].txt
      │
      ├─ [4] REGRAS
      │   └─ exibirRegras()
      │
      ├─ [5] CREDITOS
      │   └─ exibirCreditos()
      │
      └─ [0] SAIR → Encerra
```

## Principais Funções

### Jogo

| Função | Descrição |
|--------|-----------|
| `jogar()` | Loop principal da partida |
| `moverPeca()` | Valida e executa movimento |
| `moverDama()` | Movimento especial de dama |
| `inicializarTabuleiro()` | Prepara novo jogo |
| `mostrarTabuleiro()` | Exibe tabuleiro na tela |

### Validação

| Função | Descrição |
|--------|-----------|
| `existeCaptura()` | Verifica se há captura disponível |
| `jogadorTemCaptura()` | Valida captura obrigatória |
| `verificarFimDeJogo()` | Verifica condições de vitória |
| `verificarVencedor()` | Determina quem venceu |
| `lerCoordenada()` | Valida entrada de números |

### Histórico

| Função | Descrição |
|--------|-----------|
| `registrarJogada()` | Armazena movimento em memória |
| `salvarHistoricoPartida()` | Salva histórico em arquivo .txt |
| `carregarEExibirHistorico()` | Lê e exibe histórico salvo |

### Algoritmos

| Função | Tipo | Complexidade |
|--------|------|--------------|
| `buscaRecursiva()` | Busca Sequencial Recursiva | O(n) |
| `ordenaRankingPorVitorias()` | Bubble Sort | O(n²) |
| `buscaBinaria()` | Busca Binária | O(log n) |

### Ranking

| Função | Descrição |
|--------|-----------|
| `carregarPerfis()` | Carrega ranking.txt |
| `salvarPerfis()` | Salva ranking.txt |
| `exibirRanking()` | Mostra ranking na tela |
| `atualizarPerfil()` | Atualiza vitória de jogador |

## Arquivos Gerados

### ranking.txt
```
João 5
Maria 3
Bruno 2
```

### historico_João.txt
```
HISTORICO DE PARTIDA - João
====================================
1. B (7,0) -> (5,1) 
2. P (2,1) -> (4,0) [CAPTURA]
3. B (5,1) -> (3,2) 
====================================
```

## Tratamento de Erros

O código implementa validação robusta em 3 níveis:

### Nível 1: Entrada
```cpp
lerCoordenada()  // try-catch para números inválidos
menu()           // Valida opção 1-5 ou 0
```

### Nível 2: Lógica
```cpp
moverPeca()      // Valida movimento segundo regras
existeCaptura()  // Valida captura disponível
```

### Nível 3: Persistência
```cpp
salvarHistoricoPartida()  // try-catch para arquivo
carregarPerfis()          // try-catch para leitura
```

## Exemplo de Uso

```
$ ./damas

Bem-vindo ao Jogo de Damas!

[1] PLAY
[2] RANKING
[3] HISTORICO
[4] REGRAS
[5] CREDITOS
[0] SAIR
Opcao: 1

Escolha sua equipe:
[B] Pecas Brancas
[P] Pecas Pretas
Escolha: B

Jogador 1: B
Jogador 2: P

Partida iniciando...

[Tabuleiro exibido]

Linha origem: 7
Coluna origem: 1
Linha destino: 5
Coluna destino: 2

Movimento realizado com sucesso!
```

## Tecnologias

- **Linguagem**: C++11/14
- **Paradigma**: Programação Procedural
- **Estruturas**: STL (vector)
- **Persistência**: Arquivos ASCII (txt)
- **Plataformas**: Windows, Linux, macOS

## Compiladores Testados

- GCC 11.2.0 (MinGW64)
- Clang 14.0.0
- Visual Studio 2019+

## Melhorias Futuras

- [ ] Interface gráfica (SDL2 ou Qt)
- [ ] Inteligência artificial (jogador vs máquina)
- [ ] Rede multiplayer
- [ ] Banco de dados (SQLite)
- [ ] Sistema de ratings ELO
- [ ] Replay de partidas

## Créditos

**Desenvolvido por:**
- Mateus Gonçalves Teteo
- Pablo Alves

**Instituição:** UFRN - Universidade Federal do Rio Grande do Norte  
**Curso:** Tecnologia em Análise e Desenvolvimento de Sistemas (TADS)  
**Disciplina:** Algoritmos e Programação  
**Data:** Junho/2026

## Licença

Este projeto é licenciado sob a MIT License - veja o arquivo [LICENSE](LICENSE) para detalhes.

## Como Contribuir

1. Faça um Fork do projeto
2. Crie uma branch para sua feature (`git checkout -b feature/MinhaFeature`)
3. Commit suas mudanças (`git commit -m 'Adiciona MinhaFeature'`)
4. Push para a branch (`git push origin feature/MinhaFeature`)
5. Abra um Pull Request

## Suporte

Para dúvidas ou reportar bugs, abra uma issue no repositório:
https://github.com/mateusgoncalvesteteo-svg/JOGO_DE_DAMAS/issues

## Agradecimentos

- Professor josenalde pela orientação
- Colegas por feedback e testes

**Última atualização:** junho/2026

## Disclosure de Inteligência Artificial

**Este projeto utilizou auxílio de IA (Claude)** para:

- Formatação e estruturação do código
- Correção de erros lógicos e de compilação
- Orientação sobre algoritmos (Busca Recursiva, Bubble Sort, Busca Binária)
- Dúvidas específicas sobre C++ e STL
- Validação dos requisitos do projeto
- Formatação do README.md

**Importante:** O código principal, a lógica do jogo e as decisões de arquitetura foram desenvolvidos manualmente pelo autor. A IA foi utilizada como **ferramenta de consultoria e correção**, não como gerador automático de código.

Todas as funções foram compreendidas, testadas e validadas pelo desenvolvedor.
