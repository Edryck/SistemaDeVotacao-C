#include "utils.h"
#include "ui_utils.h"
#include <stdlib.h>
#include <stdio.h>

// Cabeçalhos
void quebrarLinha() {
    printf("\n");
}

void limparTela() {
    system("cls");
}

void pausarTela() {
    animarCarregamento("Pressione ENTER para continuar", 500);
    getchar();
}