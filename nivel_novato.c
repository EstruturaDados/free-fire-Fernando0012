/*

======================= NÍVEL NOVATO ==========================================

    =================== OBJETIVO ==================
    Criar um programa em C com as seguintes funcionalidades:
    * Adicionar itens à mochila (nome, tipo e quantidade)
    * Remover itens pelo nome
    * Listar os itens cadastrados
    
    ================= Funcionalidades ============= 
    * Utilização de struct para representar cada item
    * Vetor estático com capacidade para até 10 item 
    * Leitura e escrita via terminal (scanf, printf) 
    * Menu interativo com swicth e do-while
    
    ================== Simplicidade ================
    * Sem ordenações, buscas especializadas ou uso de ponteiros
    * Ideal para praticar manipulação básica de estruturas e arrays
    
    ===================== Entrada ===================
    O usuário escolhe ações no menu e preenche os dados dos itens conforme solicitado

    ====================== Saída ==========================
    O programa exibe os dados organizados em formato de tabela, com nome, tipo e quantidade.
*/

// Bibliotecas
#include <stdio.h> // Funções (printf e scanf)
#include <stdlib.h> // Funções de alocação (malloc, calloc, free, rand, srand).
#include <string.h> // Para trabalhar com strings (strcpy, strcmp)


// Define as constantes que serão usadas
#define MAX_STRINGS 50
#define TAM_MAX 10

// Lista estatica
typedef struct{
    char nome[MAX_STRINGS];
    char tipo[MAX_STRINGS];
    int quantidade;
} Item;

typedef struct{
    Item itens[TAM_MAX];
    int quantidade;
}Mochila;

// Função de limpar o buffer
void limparBufferEntrada();

// Prototipos
void inicializarMochila(Mochila *mochila);
void inserirItens(Mochila *mochila);
void removerItens(Mochila *mochila, const char* nomeBusca);
void listarItens(const Mochila *mochila);
void menuMochila();


// Menus 
void inicializarMochila(Mochila *mochila){
    mochila->quantidade = 0;
}

void menuMochila(){
    Mochila mochila; // Instância da nova struct
    inicializarMochila(&mochila);
    char nomeBusca[MAX_STRINGS]; // Usado apenas para a remoção
    int opcao;

    do{
        printf("\n --- Menu Da Mochila (Lista Estativa) ---\n");
        printf("1. Adicionar Novo Item\n");
        printf("2. Remover Item pelo Nome.\n");
        printf("3. Listar Todos os Itens.\n");
        printf("0. Voltar ao Menu Principal.\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch(opcao){
            case 1:
                inserirItens(&mochila);
                break;

            case 2:
                printf("Digite o Nome do item a remover: ");
                fgets(nomeBusca, MAX_STRINGS, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = 0;
                removerItens(&mochila, nomeBusca);
                break;

            case 3:
                listarItens(&mochila);
                break;

            case 0:
                printf("Voltando...\n");
                break;
            
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
}

// -----------------------------------------------
// FUNÇÃO PRINCIPAL (MAIN)
// -----------------------------------------------

int main(){
    int opcao;
    do{
        printf("\n--- MANIPULACAO DE ITEM DA MOCHILA ---\n");
        printf("1. Usar Mochila Estatica\n");
        printf("2. Usar Mochila Encadeada (Em Breve)\n");
        printf("0. Sair do programa\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch(opcao){
            case 1:
                menuMochila();
                break;

            case 2:
                printf("Em producao com o DEV\n");
                break;
            
            case 0:
                printf("Saindo do Programa.\n");

            default:
                printf("Opcao invalida!\n");
        }
    }   while(opcao != 0);
        return 0;
}

// MOCHILA ESTATICA

void inserirItens(Mochila *mochila){
    // 1. Verifica se está cheia
    if(mochila->quantidade == TAM_MAX){
        printf("Erro: Mochila cheia! Nao e possivel inserir.\n");
        return;
    }   

    // 2. Coleta os dados do novo item
    Item novoItem;

    printf("\n--- Novo Item ---\n");

    printf("Nome do Item (Max %d chars): ", MAX_STRINGS - 1);
    fgets(novoItem.nome, MAX_STRINGS, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = 0; // Remove o '\n'

    printf("Tipo do Item (ex: Comida, Arma): ");
    fgets(novoItem.tipo, MAX_STRINGS, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = 0;

    printf("Quantidade: ");
    if(scanf("%d", &novoItem.quantidade) != 1){
        printf("Erro: Quantidade invalida. Cancelando insercao.\n");
        limparBufferEntrada();
        return;
    }

    limparBufferEntrada(); 

    // 3. Adiciona o Item no final do vetor e incrementa o contador
    mochila->itens[mochila->quantidade] = novoItem; //Atribuição de struct completa
    mochila->quantidade++;

    printf("\n[SUCESSO] Item \"%s\" (x%d) adicionado a mochila.\n", novoItem.nome, novoItem.quantidade);

}   

void removerItens(Mochila *mochila, const char* nomeBusca){
    int i, pos = -1;

    // 1. Busca o item pelo nome
    for(i = 0; i < mochila->quantidade; i++){
        // Compara o nome do item atual com o nome de busca (strcmp retorna 0 se forma iguais)
        if(strcmp(mochila->itens[i].nome, nomeBusca) == 0){
            pos = i;
            break;
        }
    }

    // 2. Tratamento de Erro: não encontrado
    if(pos == -1){
        printf("Erro: Item \"%s\" nao encontrado na mochila.\n", nomeBusca);
        return;
    }

    // 3. Fechar a Lacuna: Desloca todos os itens após a posição 'pos' uma casa para a esquerda
    for(i = pos; i < mochila->quantidade - 1; i++){
        // Copia a struct completa do item seguinte para a posição atual
        mochila->itens[i], mochila->itens[i+1];
    }

    // 4. Atualiza o contador
    mochila->quantidade--;
    printf("\n[Sucesso] Item \"%s\" removido com sucesso.\n", nomeBusca);
}

void listarItens(const Mochila *mochila){
    if(mochila->quantidade == 0){
        printf("A mochila esta vazia. Nao ha itens para listar. \n");
        return;
    }

    // Cria o cabeçalho formato em tabela
    printf("\n-------------------------------------------------\n");
    printf("| %-20s | %-10s | %-10s |\n", "Nome", "TIPO", "QUANTIDADE");
    printf("---------------------------------------------------\n");


    // Imprime cada item
    for(int i = 0; i < mochila->quantidade; i++){
        printf("| %-20s | %-10s | %-10d |\n",
            mochila->itens[i].nome,
            mochila->itens[i].tipo,
            mochila->itens[i].quantidade
        );
    }
    printf("----------------------------------------------------\n");
}

void limparBufferEntrada(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}