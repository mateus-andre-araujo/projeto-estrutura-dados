#ifndef BST_H
#define BST_H

#define MAX_STRING 80

// Estrutura do livro (conteúdo do nó)
typedef struct {
    int id;
    char titulo[MAX_STRING];
    char autor[MAX_STRING];
    int ano;
} Livro;

// Nó da Árvore Binária de Busca (BST)
typedef struct NoBST {
    Livro dados;
    struct NoBST *eloE;
    struct NoBST *eloD;
} NoBST;

// Protótipos das operações da BST
NoBST* inserirBST(NoBST* raiz, Livro livro, int *sucesso);
NoBST* buscarBST(NoBST* raiz, int id);
NoBST* removerBST(NoBST* raiz, int id, int *sucesso);
void listarEmOrdem(NoBST* raiz);
void liberarBST(NoBST* raiz);

#endif
