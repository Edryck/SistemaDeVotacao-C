#include "menu.h"
#include "ui_utils.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

void menuPrincipal() {
    limparTela();

    desenharLinhaHorizontal('=');
    printf("\n");
    mostrarTextoCentralizado("SISTEMA DE VOTACAO");
    printf("\n");
    desenharLinhaHorizontal('=');
    printf("\n");

    printf("1 - Entrar como Administrador\n");
    printf("2 - Entrar como Eleitor\n");
    printf("3 - Sair\n");

    printf("\n\n");
    printf("Escolha uma opcao: ");
    int opcao;
    scanf("%d", &opcao);
    getchar(); // Limpa o buffer

    switch(opcao) {
        case 1:
            // Chamar função para adminitrador
            printf("Em desenvolvimento!\n");
            pausarTela();
            break;
        case 2:
            // Chamar função para eleitor
            printf("Em desenvolvimento!\n");
            pausarTela();
            break;
        case 3:
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
