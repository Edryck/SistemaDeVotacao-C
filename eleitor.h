#ifndef ELEITOR_H  
#define ELEITOR_H
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