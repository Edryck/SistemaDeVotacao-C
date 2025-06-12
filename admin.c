#include "admin.h"

void criarcandidato(Candidato candidato[], int *quantCandidatos) {
    limparTela();

    if (*quantCandidatos >= MAX_CANDIDATOS) {
        printf("Numero max de candidatos ja atingido! Nao sera possivel cadastrar novo candidato.\n");
        registrarLog("Tentativa de cadastrar candidato com o limite maximo atingido");
        return;
    }

    cabecalho("CRIAR CANDIDATOS");
    printf("\n");

    // Recebe o numero do candidato e faz a validação para que seja
    // maior que 0 e que seja único
    int numero;
    do {
        printf("Digite o numero do candidato (deve ser maior que 0): ");
        scanf("%d", &numero);

        if (numero <= 0) {
            printf("ERRO: Numero invalido! Tente novamente.\n");
        } else if (numeroExiste(candidato, *quantCandidatos, numero)) {
            printf("ERRO: Esse numero ja pertence a outro candidato! Tente novamente\n");
            numero = 0;
        }
    } while(numero <= 0);

    // Recebe o nome do candidato
    char nome[45];
    printf("Informe o nome do candidato: ");
    scanf(" %[^\n]s", nome);
    
    // Copia os dados do novo candidato para a struct
    int i = *quantCandidatos;
    strcpy(candidato[i]->nome, nome);
    candidato[i]->numero = numero;
    candidato[i]->votos = 0;
    (*quantCandidatos)++;
    registrarLog("Novo candidato cadastrado no sistema!");
}

void listaCandidatos(Candidato candidato[]) {
    for(int i = 0; i < MAX_CANDIDATOS; i++) {
        printf("%d - %s\n", i + 1, candidato[i]);
    }
}

void resultados(Candidato candidatos[], int totalCandidatos, int votosNulos, int votosBrancos) {
    if (fase == FASE_APURACAO) {
        FILE *resultados = fopen("relatorio.txt", "r");
            if (resultados == NULL) {
                printf("ERRO: Nao foi possivel abrir o resultado da votacao.");
                pausarTelaInt();
                return;
            }

            char ch;
            ch = getc(resultados);
            while(ch != EOF) {
                putchar(ch);
                ch = getc(resultados);
            }

        fclose(resultados);
        pausarTelaInt();
    } else {
        printf("A votacao ainda nao terminou!\n Aguarde terminar para ver os resultados.\n");
        pausarTelaInt();
    }
}

void relatorio(Candidato candidatos[], int totalCandidatos, int votosNulos, int votosBrancos) {
    FILE *f = fopen("relatorio.log", "r");
        if (f == NULL) {
            printf("ERRO: Nao foi possivel abrir o arquivo de relatorio.\n");
            pausarTelaInt();
            return;
        }
        
        char ch;
        ch = 
    fclose(f);
}