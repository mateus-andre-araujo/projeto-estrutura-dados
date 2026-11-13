#ifndef ESTRUTURA_H
#define ESTRUTURA_H

// Nó da pilha (estrutura linear escolhida)
typedef struct {
    int id;
    struct NoPilha *proximo;
} NoPilha;

// Estrutura da pilha
typedef struct {
    NoPilha *topo;
} Pilha;

// Protótipos das operações da pilha
void inicializarPilha(Pilha *p);
void push(Pilha *p, int id);
int pop(Pilha *p, int *idRemovido);
void exibirPilha(Pilha *p);
void liberarPilha(Pilha *p);

#endif
