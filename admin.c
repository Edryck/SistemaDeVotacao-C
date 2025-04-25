#include <stdlib.h>
#include <stdio.h>
#include "admin.h"
#include "menu.h"
#include "log.h"
#include "ui_utils.h"
#include "utils.h"

void menuAdmin() {
    limparTela();

    mostrarTextoCentralizado("MENU ADMINISTRADOR");
    quebrarLinha();

    printf("1 - Criar Urna\n");
    printf("2 - Cadastrar Candidato\n");
    printf("3 - Conferir Resultados\n");
    printf("4 - Verificar Log\n");
    printf("5 - Sair\n");
    quebrarLinha();
    desenharLinhaHorizontal('=');
    printf("Escolha uma opcao: ");

    int opcao;
    scanf("%d", &opcao);
    desenharLinhaHorizontal('=');
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
            pausarTela();
            menuPrincipal(); // Retorna ao menu principal
            break;
        default:
            printf("Opcao invalida! Tente novamente.");
            pausarTela();
            menuAdmin(); // Chama o menu novamente
            break;
    }
}

void menuCriarUrna(){
    printf("Em desenvolvimento!\n");
    pausarTela();
    menuAdmin(); // Retorna ao menu do administrador
}

void menuCadastrarCandidato(){
    printf("Em desenvolvimento!\n");
    pausarTela();
    menuAdmin(); // Retorna ao menu do administrador
}

void conferirResultados(){
    printf("Em desenvolvimento!\n");
    pausarTela();
    menuAdmin(); // Retorna ao menu do administrador
}