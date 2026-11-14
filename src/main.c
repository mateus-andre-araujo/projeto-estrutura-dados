#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "bst.h"
#include "estrutura.h"

// Função auxiliar para limpar o buffer de entrada do teclado
void limparBuffer() {
	
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função segura para ler uma string, rejeitando se exceder o limite máximo
int lerStringSegura(const char *mensagem, char *destino, int tamanhoMax) {
	
    char buffer[256]; // Buffer temporário maior para inspecionar o tamanho real digitado
    printf("%s", mensagem);
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    // Verifica se a string contém a quebra de linha ('\n'). 
    // Se não contiver, significa que o usuário digitou mais do que o buffer temporário suporta ou o tamanho estourou.
    size_t len = strlen(buffer);
    
	if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    } else {
        // A linha digitada excedeu o tamanho do buffer temporário e limpa o restante do stdin
        limparBuffer();
        printf("Erro: O texto inserido excede o limite permitido!\n");
        return 0;
    }

    // Como o limite máximo para o campo é tamanhoMax - 1, há 79 caracteres úteis
    if ((int)len >= tamanhoMax) {
        printf("Erro: O texto excede o limite maximo de %d caracteres!\n", tamanhoMax - 1);
        return 0;
    }

    // Validação: Não pode estar vazia ou conter apenas espaços
    int apenasEspacos = 1;
    
    for (size_t i = 0; i < len; i++) {
        if (!isspace((unsigned char)buffer[i])) {
            apenasEspacos = 0;
            break;
        }
    }

    if (len == 0 || apenasEspacos) {
        return 0;
    }

    // Copia para o destino final com segurança
    strcpy(destino, buffer);
    return 1;
}

// Função segura para ler um número inteiro positivo com validação estrita de overflow
int lerInteiroPositivo(const char *mensagem, int *valor) {
	
    char entrada[100];
    printf("%s", mensagem);
    
    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
        return 0;
    }

    // Remove '\n'
    size_t len = strlen(entrada);
    
    if (len > 0 && entrada[len - 1] == '\n') {
        entrada[len - 1] = '\0';
        len--;
    }

    // Verifica se a string está vazia ou contém caracteres não numéricos
    if (len == 0) return 0;
    
    for (size_t i = 0; i < len; i++) {
        if (!isdigit((unsigned char)entrada[i])) {
            return 0; // Contém caracteres não numéricos
        }
    }

    // Validação de comprimento e tamanho máximo antes de converter para evitar overflow
    // O valor máximo para um inteiro positivo padrão em C é INT_MAX (2147483647, que tem 10 dígitos)
    if (len > 10) {
        return 0; // Excede o número de dígitos possíveis para um int padrão
    }

    long temp = atol(entrada);

    // Verifica se excede o limite de INT_MAX ou se é menor/igual a zero
    if (temp <= 0 || temp > INT_MAX) {
        return 0;
    }

    *valor = (int)temp;
    return 1;
}

// Função específica para ler a opção do menu (aceita 0 para encerrar e inteiros positivos de 1 a 7)
int lerOpcaoMenu(int *valor) {
	
    char entrada[100];
    printf("Escolha uma opcao: ");
    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
        return 0;
    }

    // Remove '\n'
    size_t len = strlen(entrada);
    
    if (len > 0 && entrada[len - 1] == '\n') {
        entrada[len - 1] = '\0';
        len--;
    }

    if (len == 0) return 0;
    
    for (size_t i = 0; i < len; i++) {
        if (!isdigit((unsigned char)entrada[i])) {
            return 0; // Contém caracteres não numéricos
        }
    }

    if (len > 10) return 0;

    long temp = atol(entrada);
    if (temp < 0 || temp > INT_MAX) {
        return 0;
    }

    *valor = (int)temp;
    return 1;
}

int main() {
    NoBST *raizBST = NULL;
    Pilha pilhaIDs;
    inicializarPilha(&pilhaIDs);

    int opcao;

    do {
        printf("\n==========================================\n");
        printf("SISTEMA DE ESTRUTURA DE DADOS (BIBLIOTECA)\n");
        printf("==========================================\n");
        printf("1 - Cadastrar registro na BST\n");
        printf("2 - Buscar registro por ID na BST\n");
        printf("3 - Remover registro da BST\n");
        printf("4 - Listar registros em-ordem\n");
        printf("5 - Inserir ID na pilha\n");
        printf("6 - Remover da pilha\n");
        printf("7 - Exibir pilha\n");
        printf("0 - Encerrar\n");
        printf("==========================================\n");

        if (!lerOpcaoMenu(&opcao)) {
            printf("Opcao invalida! Digite um numero inteiro correspondente ao menu.\n");
            continue;
        }

        switch (opcao) {
        	
            case 1: {
                // Cadastrar registro na BST (Tema C: ID, Título, Autor, Ano)
                printf("\n--- CADASTRO DE LIVRO NA BST ---\n");
                
                int id;
                if (!lerInteiroPositivo("Digite o ID (inteiro positivo): ", &id)) {
                    printf("Erro: ID invalido! Deve ser um inteiro positivo.\n");
                    break;
                }

                Livro novoLivro;
                novoLivro.id = id;

                if (!lerStringSegura("Digite o Titulo (max 79 caracteres): ", novoLivro.titulo, MAX_STRING)) {
                    printf("Erro: Titulo invalido (vazio ou excedeu limite)!\n");
                    break;
                }

                if (!lerStringSegura("Digite o Autor (max 79 caracteres): ", novoLivro.autor, MAX_STRING)) {
                    printf("Erro: Autor invalido (vazio ou excedeu limite)!\n");
                    break;
                }

                int ano;
                if (!lerInteiroPositivo("Digite o Ano de Publicacao (1 a 2026): ", &ano) || ano < 1 || ano > 2026) {
                    printf("Erro: Ano invalido! Deve estar entre 1 e 2026.\n");
                    break;
                }
                
                novoLivro.ano = ano;

                int sucesso = 0;
                raizBST = inserirBST(raizBST, novoLivro, &sucesso);
                
                if (sucesso) {
                    printf("Livro cadastrado com sucesso na BST!\n");
                } else {
                    printf("Erro: Ja existe um livro com o ID %d na BST (ID duplicado rejeitado).\n", id);
                }
                break;
            }
            
            case 2: {
                // Buscar registro por ID na BST
                printf("\n--- BUSCA DE LIVRO NA BST ---\n");
                int id;
                
                if (!lerInteiroPositivo("Digite o ID que deseja buscar: ", &id)) {
                    printf("Erro: ID invalido!\n");
                    break;
                }

                NoBST *encontrado = buscarBST(raizBST, id);
                
                if (encontrado != NULL) {
                    printf("\nRegistro encontrado na BST:\n");
                    printf("----------------------------------------\n");
                    printf("ID     : %d\n", encontrado->dados.id);
                    printf("Titulo : %s\n", encontrado->dados.titulo);
                    printf("Autor  : %s\n", encontrado->dados.autor);
                    printf("Ano    : %d\n", encontrado->dados.ano);
                    printf("----------------------------------------\n");
                } else {
                    printf("Aviso: Livro com ID %d nao foi encontrado na BST.\n", id);
                }
                break;
            }
            
            case 3: {
                // Remover registro da BST
                printf("\n--- REMOCAO DE LIVRO DA BST ---\n");
                int id;
                
                if (!lerInteiroPositivo("Digite o ID do livro a ser removido: ", &id)) {
                    printf("Erro: ID invalido!\n");
                    break;
                }

                int sucesso = 0;
                raizBST = removerBST(raizBST, id, &sucesso);
                
                if (sucesso) {
                    printf("Livro com ID %d removido da BST com sucesso!\n", id);
                } else {
                    printf("Aviso: Livro com ID %d nao encontrado na BST para remocao.\n", id);
                }
                break;
            }
            
            case 4: {
                // Listar registros em-ordem
                printf("\n==========================================\n");
                printf("LISTAGEM EM-ORDEM DOS LIVROS (BST)\n");
                
                if (raizBST == NULL) {
                    printf("A BST esta vazia.\n");
                } else {
                    listarEmOrdem(raizBST);
                }
                
                printf("==========================================\n");
                break;
            }
            
            case 5: {
                // Inserir ID na pilha
                printf("\n--- INSERIR ID NA PILHA ---\n");
                int id;
                
                if (!lerInteiroPositivo("Digite o ID inteiro positivo para a pilha: ", &id)) {
                    printf("Erro: ID invalido! Deve ser inteiro positivo.\n");
                    break;
                }
                
                push(&pilhaIDs, id);
                break;
            }
            
            case 6: {
                // Remover da pilha
                printf("\n--- REMOVER DA PILHA ---\n");
                int idRemovido = pop(&pilhaIDs);
                if (idRemovido != -1) {
                    printf("ID %d removido do topo da pilha com sucesso.\n", idRemovido);
                }
                break;
            }
            
            case 7: {
                // Exibir pilha
                exibirPilha(&pilhaIDs);
                break;
            }
            
            case 0:
                printf("\nEncerrando o programa e liberando memoria...\n");
                break;
                
            default:
                printf("Opcao invalida! Escolha um numero entre 0 e 7.\n");
        }

    } while (opcao != 0);

    // Limpeza final de memória antes de sair
    liberarBST(raizBST);
    liberarPilha(&pilhaIDs);

    printf("Memoria liberada com sucesso.\n");
    return EXIT_SUCCESS;
}
