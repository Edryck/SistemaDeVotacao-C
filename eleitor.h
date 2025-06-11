#ifndef ELEITOR_H  
#define ELEITOR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "menu.h"
#include "log.h"
#include "utils.h"

#define ARQUIVO_ELEITORES "eleitores.txt"

typedef struct {
    char nome[100];
    char cpf[15];
    int idade;
    char tituloEleitor[20];
} Eleitor;

// Cabeçalhos
void menuEleitor();
int cpfJaCadastrado( char* cpf);

#endif