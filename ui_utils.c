#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "ui_utils.h"
#include "utils.h"

int obterLarguraTerminal() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int largura = 80; // fallback

    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        largura = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    return largura;
}

void mostrarTextoCentralizado(const char* texto) {
    int largura = obterLarguraTerminal();
    int len = strlen(texto);
    int espacos = (largura - len) / 2;

    
    desenharLinhaHorizontal('=');
    quebrarLinha();
    for (int i = 0; i < espacos; i++) printf(" ");
    printf("%s\n", texto);
    quebrarLinha();
    desenharLinhaHorizontal('=');
    
}

void desenharLinhaHorizontal(char c) {
    int largura = obterLarguraTerminal();
    for (int i = 0; i < largura; i++) printf("%c", c);
    printf("\n");
}

void animarCarregamento(const char* mensagem, int delay_ms) {
    int j;

    while (!kbhit()) { // Enquanto nenhuma tecla for pressionada
        for (j = 0; j <= 3; j++) {
            if (kbhit()) break; // Verifica a cada ciclo
            printf("\r%s", mensagem);
            for (int k = 0; k < j; k++) {
                printf(".");
            }
            printf("   "); // limpa os pontos antigos caso vá de ... para vazio
            fflush(stdout);
            Sleep(delay_ms);
        }
    }
}
