#include "utils.h"

void cabecalho(const char* texto) {
    printf("\n---------- %s ----------\n", texto);
}

void limparTelaInt() {
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear");  // Linux/MacOS
    #endif
}

void pausarTelaInt() {
    #ifdef _WIN32
        system("pause"); // Windows
    #else
        printf("\nTecle ENTER para continuar...");
        system("read -n 1 -s"); // Linux/MacOS
    #endif
}

void registrarLog(const char* mensagem) {
    FILE *log = fopen(ARQUIVO_LOG, "a");
        if(log == NULL) {
            printf("ERRO: Falha ao abrir o arquivo de log.\n");
            pausarTelaInt();
            return;
        }

        time_t tempo;
        struct tm *info;
        char dataHora[80];

        time(&tempo);
        info = localtime(&tempo);

        strftime(dataHora, sizeof(dataHora), "[%Y-%m-%d %H:%M:%S]", info);

        fprintf(log, "%s %s \n",  dataHora, mensagem);
        
    fclose(log);
}