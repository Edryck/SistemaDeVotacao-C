
#include "eleitor.h"



void menuEleitor() {
    limparTela();

    cabecalho("MENU ELEITOR"); // cabecalho
    // Exibição das informações do eleitor
    // Adicionar aqui a lógica para exibir as informações do eleitor

    printf("1 - Ver candidatos\n");
    printf("2 - Votar\n");
    printf("3 - Sair\n");
    printf("Escolha uma opcao: ");

    int opcao;
    scanf("%d", &opcao);
    switch(opcao) {
        case 1: // Chama a função para ver candidatos
            printf("Em desenvolvimento!\n");
            pausarTelaInt();
            menuEleitor();
            break;
        case 2: // Chama a função para votar
            printf("Em desenvolvimento!\n");
            pausarTelaInt();
            menuEleitor();
            break;
        case 3: // Sair do menu eleitor
            printf("Saindo...\n");
            pausarTelaInt();
            menuPrincipal(); // Retorna ao menu principal
            break;
        default:
            printf("Opcao invalida! Tente novamente.");
            pausarTelaInt();
            menuEleitor(); // Chama o menu novamente
            break;
    }
}
int cpfJaCadastrado(char* cpf) {
    FILE* arquivo = fopen(ARQUIVO_ELEITORES, "r");
    if (arquivo == NULL) {
        return 0; // Arquivo não existe
    }

    char linha[256];
    
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char* token = strtok(linha, "|");
        token = strtok(NULL, "|"); // Pega o CPF
        
        if (token != NULL && strcmp(token, cpf) == 0) {
            fclose(arquivo);
            return 1; 
        } else {
            fclose(arquivo);
            return 0; 
        }
    }
}