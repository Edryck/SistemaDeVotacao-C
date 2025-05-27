#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "ui_utils.h"
#include <string.h>
#define LARGURA_TERMINAL 100




/**
 * @brief Limpa a tela usando comandos do sistema operacional.
 */
void limparTela() {
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear");  // Linux/macOS
    #endif
}

/**
 * @brief Pausa a execução do programa até o usuário pressionar Enter.
 */
void pausarTela() {
    animarCarregamento("Pressione ENTER para continuar", 500);
    getchar(); // limpa o buffer
    getchar(); // espera input;
}

/**
 * @brief Imprime uma linha horizontal com um caractere repetido.
 * @param caractere Caractere que será usado.
 */
void desenharLinhaHorizontal(char caractere) {
    for (int i = 0; i < LARGURA_TERMINAL; i++) {
        printf("%c", caractere);
    }
    printf("\n");
}

/**
 * @brief Imprime uma quebra de linha.
 */
void quebrarLinha() {
    printf("\n"); // Cabeçalhos
}

/**
 * @brief Exibe texto centralizado no terminal.
 * @param texto Ponteiro para a string a ser exibida.
 */
void mostrarTextoCentralizado(const char *texto) {
    int tamanhoTexto = strlen(texto);
    int espacos = (LARGURA_TERMINAL - tamanhoTexto) / 2;

    for (int i = 0; i < espacos; i++) {
        printf(" ");
    }
    printf("%s\n", texto);
}
