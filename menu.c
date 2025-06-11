#include "menu.h"

/**
 * Exibe o menu principal do sistema de votação.
 * O usuário pode escolher entre administrador, eleitor, cadastro ou sair.
 */
void menuPrincipal() {
    limparTela();
    cabecalho("SISTEMA DE VOTACAO");

    printf("1 - Entrar como Administrador\n");
    printf("2 - Entrar como Eleitor\n");
    printf("3 - Cadastrar Eleitor\n");
    printf("4 - Sair\n");
    quebrarLinha();
    desenharLinhaHorizontal('=');
    printf("Escolha uma opcao: ");
    
    int opcao;
    if (scanf("%d", &opcao) != 1) {
        printf("Entrada inválida! Tente novamente.\n");
        pausarTelaInt();
        menuPrincipal();
        return;
    }

    switch(opcao) {
        case 1:
            menuAdmin();
            pausarTelaInt();
            break;
        case 2:
            menuEleitor();
            pausarTelaInt();
            break;
        case 3:
            menuCadastro();
            pausarTelaInt();
            menuPrincipal();
            break;
        case 4:
            printf("Saindo...\n");
            pausarTelaInt();
            exit(0);
            break;
        default:
            printf("Opcao invalida! Tente novamente.");
            pausarTelaInt();
            menuPrincipal();
            break;
    }
}



/**
 * Exibe o menu de cadastro de eleitor.
 */
void menuCadastro() {
    limparTela();
    mostrarTextoCentralizado("CADASTRO DE ELEITOR");
    quebrarLinha();
    Eleitor novoEleitor;
    
    printf("Nome completo: ");
    scanf(" %[^\n]", novoEleitor.nome);
    
    printf("CPF (somente numeros): ");
    scanf("%11s", novoEleitor.cpf); 
    //chama funçao pra verifificar se ja existe o cpf cadastrado
    if (cpfJaCadastrado(novoEleitor.cpf)) {
        printf("\nErro: CPF ja cadastrado no sistema.\n");
        pausarTelaInt();
        return;
    }
    
    printf("Idade: ");
    if (scanf("%d", &novoEleitor.idade) != 1) {
        printf("Entrada inválida! Tente novamente.\n");
        pausarTelaInt();
        return;
    }
    
    if (novoEleitor.idade < 16) {
        printf("\nErro: Eleitor deve ter pelo menos 16 anos para se cadastrar.\n");
        pausarTelaInt();
        return;
    }
    
    printf("Numero do Titulo de Eleitor: ");
    scanf("%11s", novoEleitor.tituloEleitor);
    
    FILE* arquivo = fopen(ARQUIVO_ELEITORES, "a");
    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo de eleitores!\n");
        pausarTelaInt();
        return;
    }
    
    fprintf(arquivo, "%s|%s|%d|%s\n", 
            novoEleitor.nome, 
            novoEleitor.cpf, 
            novoEleitor.idade, 
            novoEleitor.tituloEleitor);
            fclose(arquivo); // Fechar o arquivo antes de retornar
    
    printf("\nEleitor cadastrado com sucesso!\n");
    printf("Nome: %s\n", novoEleitor.nome);
    printf("CPF: %s\n", novoEleitor.cpf);
    printf("Idade: %d\n", novoEleitor.idade);
    printf("Titulo de Eleitor: %s\n", novoEleitor.tituloEleitor);
    
    
    pausarTelaInt();
    menuPrincipal();

}
