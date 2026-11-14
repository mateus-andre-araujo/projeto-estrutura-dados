#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

// Função auxiliar para criar um novo nó da BST
static NoBST* criarNo(Livro livro) {
	
    NoBST *novo = (NoBST*) malloc(sizeof(NoBST));
    
    if (novo == NULL) {
        printf("Erro: Falha na alocacao de memoria para o no da BST!\n");
        exit(EXIT_FAILURE);
    }
    
    novo->dados = livro;
    novo->eloE = NULL;
    novo->eloD = NULL;
    
    return novo;
}

// Inserção na BST com unicidade de ID
NoBST* inserirBST(NoBST* raiz, Livro livro, int *sucesso) {
	
    if (raiz == NULL) {
        *sucesso = 1;
        return criarNo(livro);
    }

    if (livro.id == raiz->dados.id) {
        *sucesso = 0; // ID duplicado rejeitado
        return raiz;
    }

    if (livro.id < raiz->dados.id) {
        raiz->eloE = inserirBST(raiz->eloE, livro, sucesso);
    } else {
        raiz->eloD = inserirBST(raiz->eloD, livro, sucesso);
    }

    return raiz;
}

// Busca por ID na BST
NoBST* buscarBST(NoBST* raiz, int id) {
	
    if (raiz == NULL || raiz->dados.id == id) {
        return raiz;
    }

    if (id < raiz->dados.id) {
        return buscarBST(raiz->eloE, id);
    } else {
        return buscarBST(raiz->eloD, id);
    }
}

// Função auxiliar para encontrar o nó com o menor ID (usado na remoção com 2 filhos)
static NoBST* menorNo(NoBST* no) {
	
    NoBST* atual = no;
    
    while (atual && atual->eloE != NULL) {
        atual = atual->eloE;
    }
    
    return atual;
}

// Remoção de um nó da BST (0, 1 ou 2 filhos)
NoBST* removerBST(NoBST* raiz, int id, int *sucesso) {
	
    if (raiz == NULL) {
        *sucesso = 0; // ID não encontrado
        return NULL;
    }

    if (id < raiz->dados.id) {
        raiz->eloE = removerBST(raiz->eloE, id, sucesso);
    } else if (id > raiz->dados.id) {
        raiz->eloD = removerBST(raiz->eloD, id, sucesso);
    } else {
        *sucesso = 1; // ID encontrado para remoção

        // Caso 1: Nó sem filhos (folha) ou com apenas um filho
        if (raiz->eloE == NULL) {
            NoBST *temp = raiz->eloD;
            free(raiz);
            return temp;
        } else if (raiz->eloD == NULL) {
            NoBST *temp = raiz->eloE;
            free(raiz);
            return temp;
        }

        // Caso 2: Nó com dois filhos
        // Pega o sucessor em-ordem (menor valor da subárvore direita)
        NoBST *temp = menorNo(raiz->eloD);

        // Copia os dados do sucessor para o nó atual
        raiz->dados = temp->dados;

        // Remove o sucessor da subárvore direita
        int aux;
        raiz->eloD = removerBST(raiz->eloD, temp->dados.id, &aux);
    }
    
    return raiz;
}

// Listagem em-ordem (Crescente por ID)
void listarEmOrdem(NoBST* raiz) {
	
    if (raiz != NULL) {
    	
        listarEmOrdem(raiz->eloE);
        
        printf("----------------------------------------\n");
        printf("ID: %d\n", raiz->dados.id);
        printf("Titulo : %s\n", raiz->dados.titulo);
        printf("Autor  : %s\n", raiz->dados.autor);
        printf("Ano    : %d\n", raiz->dados.ano);
        
        listarEmOrdem(raiz->eloD);
    }
}

// Liberação recursiva da memória da BST
void liberarBST(NoBST* raiz) {
	
    if (raiz != NULL) {
        liberarBST(raiz->eloE);
        liberarBST(raiz->eloD);
        free(raiz);
    }
}
