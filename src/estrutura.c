#include <stdio.h>
#include <stdlib.h>
#include "estrutura.h"

// Inicializa a pilha deixando o topo nulo
void inicializarPilha(Pilha *p) {
	
    if (p != NULL) {
        p->topo = NULL;
    }
}

// Insere um ID no topo da pilha
void push(Pilha *p, int id) {
	
    if (p == NULL) return;

    NoPilha *novoNo = (NoPilha*) malloc(sizeof(NoPilha));
    if (novoNo == NULL) {
        printf("Erro: Falha na alocacao de memoria para o no da pilha!\n");
        exit(EXIT_FAILURE);
    }

    novoNo->id = id;
    novoNo->proximo = p->topo;
    p->topo = novoNo;
    
    printf("ID %d inserido na pilha com sucesso.\n", id);
}

// Remove o ID do topo da pilha
// Retorna o ID removido, ou -1 se a pilha estiver vazia
int pop(Pilha *p) {
    if (p == NULL || p->topo == NULL) {
        printf("Aviso: A pilha esta vazia! Nao ha o que remover.\n");
        return -1; // Valor sentinela indicando pilha vazia
    }

    NoPilha *temp = p->topo;
    int idRemovido = temp->id;
    p->topo = temp->proximo;

    free(temp);
    return idRemovido;
}

// Exibe os elementos da pilha do topo para a base
void exibirPilha(Pilha *p) {
	
    if (p == NULL || p->topo == NULL) {
        printf("Aviso: A pilha esta vazia!\n");
        return;
    }

    printf("\n==========================================\n");
    printf("PILHA - TOPO A BASE\n");
    printf("==========================================\n");
    
    NoPilha *atual = p->topo;
    int posicao = 1;
    
    while (atual != NULL) {
    	
        if (posicao == 1) {
            printf("[TOPO] -> ID: %d\n", atual->id);
        } else {
            printf("       -> ID: %d\n", atual->id);
        }
        
        atual = atual->proximo;
        posicao++;
    }
    
    printf("==========================================\n");
}

// Libera toda a memória alocada para a pilha ao encerrar o programa
void liberarPilha(Pilha *p) {
	
    if (p == NULL) return;

    NoPilha *atual = p->topo;
    
    while (atual != NULL) {
        NoPilha *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    
    p->topo = NULL;
}
