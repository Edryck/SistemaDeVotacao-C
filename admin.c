
#include "admin.h"

void menuAdmin() {
    limparTela();

    cabecalho("MENU ADMINISTRADOR");

    printf("1 - Criar Urna\n");
    printf("2 - Cadastrar Candidato\n");
    printf("3 - Conferir Resultados\n");
    printf("4 - Verificar Log\n");
    printf("5 - Sair\n");
    printf("Escolha uma opcao: ");

    int opcao;
    scanf("%d", &opcao);
    switch(opcao) {
        case 1: // Chama a função para criar urna
            menuCriarUrna();
            break;
        case 2: // Chama a função para criar candidato
            menuCriarCandidato();
            break;
        case 3: // Chama a função para conferir resultados da eleição
            conferirResultados();
            break;
        case 4: // Chama a função para gerenciar logs
            menuLog();
            break;
        case 5: // Sair do menu administrador
            printf("Saindo...\n");
            pausarTelaInt();
            menuPrincipal(); // Retorna ao menu principal
            break;
        default:
            printf("Opcao invalida! Tente novamente.");
            pausarTelaInt();
            menuAdmin(); // Chama o menu novamente
            break;
    }
}

void menuCriarUrna(){
    printf("Em desenvolvimento!\n");
    pausarTelaInt();
    menuAdmin(); // Retorna ao menu do administrador
}

void menuCriarCandidato(){
    printf("Em desenvolvimento!\n");
    pausarTelaInt();
    menuAdmin(); // Retorna ao menu do administrador
}

void conferirResultados(){
    printf("Em desenvolvimento!\n");
    pausarTelaInt();
    menuAdmin(); // Retorna ao menu do administrador
}