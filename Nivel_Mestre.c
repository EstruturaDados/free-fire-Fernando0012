#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Definir tamanho e limites
#define TAMANHO 10
#define MAX_STRINGS 50

// Structs
typedef struct{
    char nome[MAX_STRINGS];
    char tipo[MAX_STRINGS];
    int quantidade;
    int prioridade;
} Item;

typedef enum{
    POR_NOME,
    POR_TIPO,
    POR_PRIORIDADE
} CriterioOrdenacao;

Item mochila[TAMANHO];
int numItens = 0;
long long comparacoes = 0;
bool ordenadaPorNome = false;

void limparTela();
void limparBufferEntrada();
void exibirMenu();
void inserirItem();
void removerItem();
void listarItem();
void menuDeOrdenacao();
void insertionSort(CriterioOrdenacao criterio);
int buscaBinariaPorNome(const char* nomeBusca);

int main(){
    int opcao;

    do{
        limparTela();
        exibirMenu();

        printf("Escolha uma opcao: ");
        if(scanf("%d", &opcao) != 1){
            opcao = -1;
            limparBufferEntrada();
        }
        limparBufferEntrada();

        switch(opcao){
            case 1: 
                inserirItem();
                break;
            
            case 2:
                removerItem();
                break;
            
            case 3: 
                listarItem();
                break;

            case 4:
                menuDeOrdenacao();
                break;
            
            case 5:
                {
                    char nome[MAX_STRINGS];
                    printf("Digite o nome do item para buscar: ");
                    fgets(nome, MAX_STRINGS, stdin);
                    nome[strcspn(nome, "\n")] = 0;

                    int indice = buscaBinariaPorNome(nome);
                    if(indice != -1){
                        printf("\n [SUCESSO] Item encontrado na posicao %d.\n", indice + 1);
                        printf("Nome: %s, Tipo: %s, Qtd: %d, Prioridade: %d\n",
                                mochila[indice].nome, mochila[indice].tipo,
                                mochila[indice].quantidade, mochila[indice].prioridade);
                    } else{
                        printf("\n[ERRO] Item \"%s\" nao encontrado. \n", nome);
                    }
                    break;
                }
            
            case 0:
                printf("\nSaindo da Ilha... Adeus!\n");
                break;

            default:
                printf("\nOpcao Invalida. Tente novamente.\n");
        }

        if(opcao != 0){
            printf("\nPressione ENTER para continuar...");
            limparBufferEntrada();
        }
    } while(opcao != 0);
    return 0;
}

void limparTela(){
    #ifdef _WIN32
        system("cls");
    
    #else 
        system("clear");
    #endif
    printf("===================================================\n");
    printf("== Codigo da Ilha - Gerenciamento de Mochila (C) ==\n");
    printf("====================================================\n");
}

void limparBufferEntrada(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void exibirMenu(){
    printf("\nStatus da Ordenacao por Nome: %s\n", ordenadaPorNome ? "ORDENADA" : "DESORDENADA");
    printf("------------------------------------\n");
    printf("1. Adicionar um Item\n");
    printf("2. Remover um item (pelo nome)\n");
    printf("3. Listar todos os itens\n");
    printf("4. Ordenar itens (Por Nome, Tipo ou Prioridade)\n");
    printf("5. Realizar BUSCA BINARIA por Nome\n");
    printf("0. Sair\n");
    printf("------------------------------------------\n");
}

void inserirItem(){
    if(numItens >= TAMANHO){
        printf("\n[ERRO] Mochila cheia! Nao e possivel inserir mais itens.\n");
        return;
    }

    Item novo;
    printf("\n--- Inserir Novo Item ---\n");

    printf("Nome do Item: ");
    fgets(novo.nome, MAX_STRINGS, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;

    printf("Tipo do Item (ex: Comida, Arma): ");
    fgets(novo.tipo, MAX_STRINGS, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = 0;

    printf("Quantidade: ");
    if(scanf("%d", &novo.quantidade) != 1 || novo.quantidade <= 0){
        printf("[ERRO] Quantidade invalida. Insercao cancelada.\n");
        limparBufferEntrada();
        return;
    }

    printf("Prioridade (1 - Baixa, 5 - Alta): ");
    if(scanf("%d", &novo.prioridade) != 1 || novo.prioridade < 1 || novo.prioridade > 5){
        printf("[ERRO] Prioridade invalida. Usando 1.\n");
        novo.prioridade = 1;
    } 
    limparBufferEntrada();

    mochila[numItens] = novo;
    numItens++;

    ordenadaPorNome = false;
    printf("\n[SUCESSO] Item \"%s\" adicionado. Total: %d/%d\n", novo.nome, numItens, TAMANHO);
}

void removerItem(){
    if(numItens == 0){
        printf("\nA mochila esta vazia.\n");
        return;
    }

    char nomeBusca[MAX_STRINGS];
    printf("\nDigite o nome do item para remover: ");
    fgets(nomeBusca, MAX_STRINGS, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    int indice = -1;

    for(int i = 0; i < numItens; i++){
        if(strcmp(mochila[i].nome, nomeBusca) == 0){
            indice = i;
            break;
        }
    }

    if(indice == -1){
        printf("\n[ERRO] Item \"%s\" nao encontrado na mochila.\n", nomeBusca);
        return;
    }

    for(int i = indice; i < numItens - 1; i++){
        mochila[i] = mochila[i + 1];
    }

    numItens--;
    ordenadaPorNome = false;
    printf("\n[Sucesso] Item \"%s\" removido.\n", nomeBusca);
}

void listarItens(){
    if(numItens == 0){
        printf("\nA mochila esta vazia. Nao ha itens.\n");
        return;
    }

    printf("\n======================================================================\n");
    printf("| %-25s | %-12s | %-5s | %-10s |\n", "Nome", "Tipo", "QTD", "Prioridade");
    printf("========================================================================\n");

    for(int i = 0; i < numItens; i++){
        printf("| %-25s | %-12s | %-5d | %-10d |\n",
            mochila[i].nome,
            mochila[i].tipo,
            mochila[i].quantidade,
            mochila[i].prioridade
        );
    }
    printf("==========================================================================\n");
}

void menuDeOrdenacao(){
    if(numItens < 2){
        printf("\nSao necessarios pelos menos 2 itens para ordenar.\n");
        return;
    }

    int opcao;
    printf("\n--- Escolha o Criterio de Ordenacao ---\n");
    printf("1. Por Nome (A-Z)\n");
    printf("2. Por Tipo (A-Z)\n");
    printf("3. Por Prioridade (5-1)\n");
    printf("Opcao: ");

    if(scanf("%d", &opcao) != 1){
        printf("\n[ERRO] Opcao invalida.\n");
        limparBufferEntrada();
        return;
    }
    limparBufferEntrada();

    CriterioOrdenacao criterio;
    switch(opcao){
        case 1:
            criterio = POR_NOME;
            break;

        case 2: 
            criterio = POR_TIPO;
            break;

        case 3:
            criterio= POR_PRIORIDADE;
            break;

        default:
            printf("\nCriterio nao reconhecido.\n");
            return;
    }

    comparacoes = 0;

    insertionSort(criterio);
  ordenadaPorNome = (criterio == POR_NOME);
    
    printf("\n[SUCESSO] Ordenacao concluida!\n");
    printf("Total de comparacoes feitas: %lld\n", comparacoes);
    listarItens();
}

/**
 * @brief
 * @details
 */
void insertionSort(CriterioOrdenacao criterio){
    int i, j;
    Item chave;

    for(i = 1; i < numItens; i++){
        chave = mochila[i];
        j = i - 1;

        while(j >= 0){
            bool deveMover = false;

            switch(criterio){
                case POR_NOME:
                    comparacoes++;
                    if(strcmp(mochila[j].nome, chave.nome) > 0){
                        deveMover = true;
                    }
                    break;

                case POR_TIPO:
                    comparacoes++;
                    if(strcmp(mochila[j].tipo, chave.tipo) > 0){
                        deveMover = true;
                    }
                    break;

                case POR_PRIORIDADE:
                    comparacoes++;
                    if(mochila[j].prioridade < chave.prioridade){
                        deveMover = true;
                    }
                    break;
            }

            if(deveMover){
                mochila[j + 1] = mochila[j];
                j = j - 1;
            } else{
                break;
            }
        }
        mochila[j + 1] = chave;
    }
}

/**
 * @brief
 * @return
 */

int buscaBinariaPorNome(const char* nomeBusca){
    if(!ordenadaPorNome){
        printf("\n[AVISO] A mochila nao está ordenada por nome. Execute a ordenacao (Opcao 4) primeiro.\n");
        return -1;
    }

    if(numItens == 0){
        return -1;
    }

    long long comparacoesBusca = 0;
    int esquerda = 0;
    int direita = numItens - 1;
    int meio;
    int resultado;

    while(esquerda <= direita){
        meio = esquerda + (direita - esquerda) / 2;

        resultado = strcmp(mochila[meio].nome, nomeBusca);
        comparacoesBusca++;

        if(resultado == 0){
            printf("(Busca Binaria - Comparacoes: %lld)\n", comparacoesBusca);
            return meio;
        } else if(resultado < 0){
            esquerda = meio + 1;
        } else{
            direita = meio - 1;
        }
    }

    printf("(Busca Binaria - Comparacoes: %lld)\n", comparacoesBusca);
    return -1;
}