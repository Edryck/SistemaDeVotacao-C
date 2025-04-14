#include <stdio.h>
#include <stdlib.h>
#include "telas.h"

// Tela de Inicial
void telaInicial() {
    // Variaveis
    int opcao;
    // Limpa a tela
    system("cls");
    // Exibição do menu
    printf("==================================================\n\n");
    printf("                   TELA INICIAL\n\n");
    printf("==================================================\n\n");
    printf("1 - Login\n");
    printf("2 - Sair\n\n");
    printf("==================================================");
    printf("Digite a opção desejada: ");
    scanf("%d", &opcao);
    switch(opcao){
        case 1:
            system("cls");
            telaLogin();
            break;
        case 2:
            system("cls");
            printf("Saindo do sistema...\nTecle ENTER para continuar...");
            getchar();
            exit(0);
            break;
        default:
            system("cls");
            printf("Opção inválida! Tente novamente.\n");
            telaInicial();
            break;
    }
}

// Tela de Login
void telaLogin() {
    // Variaveis
    char usuario[25], senha[15];
    // Limpa a tela
    system("cls");
    // Exibição do menu
    printf("==================================================\n\n");
    printf("                      LOGIN\n\n");
    printf("==================================================\n\n");
    printf("Digite seu nome de usuário: ");
    fgets(usuario, sizeof(usuario), stdin);
    printf("Digite sua senha: ");
    fgets(senha, sizeof(senha), stdin);
    // Verifica se o usuário e senha estão corretos
    // Provisório para teste
    if (strcmp(usuario, "admin\n") == 0 && strcmp(senha, "12345\n") == 0) {
        system("cls");
        printf("Login realizado com sucesso!\n");
        printf("Tecle ENTER para continuar...");
        getchar();
        // Chamar a função do menu principal aqui!
    } else {
        system("cls");
        printf("Usuário ou senha incorretos! Tente novamente.\n");
        printf("Tecle ENTER para continuar...");
        getchar();
        telaLogin();
    }
}