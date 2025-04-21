#include <stdlib.h>
#include <stdio.h>
#include "menu.h"
#include "admin.h"
#include "ui_utils.h"
#include "utils.h"


void menuPrincipal() {
    limparTela();
    mostrarTextoCentralizado("SISTEMA DE VOTACAO");
    quebrarLinha();

    printf("1 - Entrar como Administrador\n");
    printf("2 - Entrar como Eleitor\n");
    printf("3 - Cadastrar Eleitor\n");
    printf("4 - Sair\n");
    quebrarLinha();
    desenharLinhaHorizontal('=');
    printf("Escolha uma opcao: ");
    
    int opcao;
    scanf("%d", &opcao);
    getchar(); // Limpa o buffer

    switch(opcao) {
        case 1:
            // Chamar função para adminitrador
            menuAdmin();
            pausarTela();
            break;
        case 2:
            // Chamar função para eleitor
            printf("Em desenvolvimento!\n");
            pausarTela();
            break;
        case 3:
            // Chamar função para cadastrar eleitor
            printf("Em desenvolvimento!\n");
            pausarTela();
            break;
        case 4:
            printf("Saindo...\n");
            pausarTela();
            exit(0);
            break;
        default:
            printf("Opcao invalida! Tente novamente.");
            pausarTela();
            menuPrincipal(); // Chama o menu novamente
            break;
    }
}
