# Sistema de Gerenciamento de Biblioteca — BST e Pilha em C11

Aplicação de terminal desenvolvida em linguagem **C11** que implementa uma **Árvore Binária de Busca (BST)** para o cadastro de registros de livros (Tema C — Biblioteca) e uma **Pilha dinâmica** (estrutura linear complementar) para manipulação independente de identificadores inteiros positivos.

---

## 1. Estrutura do Repositório

```text
projeto-estrutura-dados/
├── include/
│   ├── bst.h             # Definições da struct Livro, nó da BST (eloE/eloD) e protótipos
│   └── estrutura.h       # Definições da Pilha dinâmica e protótipos (push/pop)
├── src/
│   ├── main.c            # Menu interativo, validações rigorosas de entrada e fluxo principal
│   ├── bst.c             # Implementação das operações da BST (inserção, busca, remoção, em-ordem)
│   └── estrutura.c       # Implementação das operações da Pilha (LIFO)
├── tests/
│   └── roteiro_testes.md # Tabela de casos de teste reproduzíveis (Requisito R08)
├── Makefile              # Automação de compilação em C11
└── README.md             # Documentação do projeto
```

---

## 2. Funcionalidades Implementadas

### Árvore Binária de Busca (BST — Tema C: Biblioteca)
* **Cadastro (Inserção):** Armazena livros contendo `ID` (inteiro positivo e único), `Título` (até 79 caracteres úteis em `char[80]`), `Autor` (até 79 caracteres úteis em `char[80]`) e `Ano de Publicação` (inteiro entre 1 e 2026). Rejeita IDs duplicados, textos vazios/apenas espaços, textos acima do limite de 79 caracteres, anos fora da faixa permitida e estouros de capacidade numérica (`overflow`).
* **Busca por ID:** Localiza e exibe os dados completos do livro correspondente ao ID informado.
* **Remoção:** Suporta a exclusão de nós nos três cenários estruturais: nó folha (0 filhos), nó com 1 filho e nó com 2 filhos (substituição pelo sucessor em-ordem).
* **Listagem em-ordem:** Percorre a árvore em ordem simétrica (*in-order*), exibindo todos os livros ordenados crescentemente pelo ID.

### Estrutura Linear Complementar (Pilha)
* **Push (Inserir):** Insere IDs inteiros positivos no topo da pilha, operando de forma independente da BST (permite IDs repetidos e IDs inexistentes na árvore).
* **Pop (Remover):** Remove e retorna o ID armazenado no topo da pilha (política LIFO — *Last In, First Out*), retornando `-1` e exibindo um aviso seguro caso a estrutura esteja vazia.
* **Exibição:** Lista os elementos armazenados do topo até a base.

### Gerenciamento de Memória
* Ao selecionar a opção `0 - Encerrar`, o sistema libera recursivamente todos os nós alocados na BST (`liberarBST`) e percorre a Pilha liberando cada nó (`liberarPilha`) antes de finalizar a execução com segurança.

---

## 3. Ambiente, Compilação e Execução

* **Padrão da Linguagem:** C11 (`-std=c11`)
* **Compilador:** GCC (GNU Compiler Collection)
* **Sistemas Operacionais Compatíveis:** Linux (Ubuntu/Debian/Fedora) e Windows (via MinGW/MSYS2 ou WSL)

### Opção A: Compilando via Makefile (Recomendado)

No terminal, a partir da raiz do projeto, execute:

```bash
make
```

Para executar o programa gerado:
* **Linux / WSL:**
  ```bash
  ./sistema_biblioteca
  ```
* **Windows (CMD / PowerShell):**
  ```powershell
  sistema_biblioteca.exe
  ```

Para limpar os arquivos objeto (`.o`) e o executável compilado:
```bash
make clean
```

### Opção B: Compilando diretamente via GCC (Sem `make`)

Caso não possua o utilitário `make` instalado ou prefira compilar manualmente, execute o comando abaixo na raiz do projeto:

```bash
gcc -std=c11 -Wall -Wextra -Iinclude src/main.c src/bst.c src/estrutura.c -o sistema_biblioteca
```

Em seguida, execute `./sistema_biblioteca` (Linux/WSL) ou `sistema_biblioteca.exe` (Windows).

---

## 4. Como Reproduzir os Testes (Requisito R08)

Todos os casos de teste de validação funcional, de limites e de tratamento de erros estão documentados em detalhes no arquivo [`tests/roteiro_testes.md`](tests/roteiro_testes.md).

Para reproduzi-los manualmente:
1. Compile e inicie a aplicação seguindo as instruções da **Seção 3**.
2. Siga sequencialmente os cenários descritos na tabela do arquivo `tests/roteiro_testes.md` (**CT01** a **CT14**), inserindo exatamente os valores listados na coluna **Entradas** através das opções do menu interativo.
3. Compare a saída exibida no terminal com a coluna **Resultado Esperado**, verificando:
   * A ordenação crescente na listagem em-ordem (`opção 4`) após inserções e remoções de nós com 0, 1 e 2 filhos (`opção 3`).
   * O bloqueio de IDs duplicados, negativos, zero, não numéricos ou com estouro de capacidade (`overflow` acima de `INT_MAX`).
   * O bloqueio de títulos/autores vazios, contendo apenas espaços ou com mais de 79 caracteres (sem truncamento e sem poluição do buffer de entrada) e anos fora do intervalo `1..2026`.
   * O comportamento LIFO da pilha (`opções 5, 6 e 7`), permitindo IDs repetidos ou ausentes na BST, e o tratamento seguro ao tentar remover de estruturas vazias.
   * O encerramento limpo ao digitar `0` no menu principal, garantindo a liberação integral da memória alocada.
