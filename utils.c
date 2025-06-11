#include "utils.h"

void cabecalho(const char* texto) {
    printf("\n---------- %s ----------\n", texto);
}

void limparTela() {
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear");  // Linux/MacOS
    #endif
}

void pausarTela(int tempo) {
    #ifdef _WIN32
        Sleep(tempo); // Windows
    #else 
        sleep(tempo * 1000); // Linux/MacOS
    #endif
}

void pausarTelaInt() {
    #ifdef _WIN32
        printf("\nTecle ENTER para continuar...");
        system("pause"); // Windows
    #else
        printf("\nTecle ENTER para continuar...");
        system("read -n 1 -s"); // Linux/MacOS
    #endif
}