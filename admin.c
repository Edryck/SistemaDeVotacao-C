#include "admin.h"

void criarCandidato(Candidato candidato[], int *totalCandidatos) {
    limparTela();

    if (*totalCandidatos >= MAX_CANDIDATOS) {
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
        } else if (numeroExiste(candidato, *totalCandidatos, numero)) {
            printf("ERRO: Esse numero ja pertence a outro candidato! Tente novamente\n");
            numero = 0;
        }
    } while(numero <= 0);

    // Recebe o nome do candidato
    char nome[45];
    printf("Informe o nome do candidato: ");
    scanf(" %[^\n]s", nome);
    
    // Copia os dados do novo candidato para a struct
    int i = *totalCandidatos;
    strcpy(candidato[i].nome, nome); //fix:
    candidato[i].numero = numero;
    candidato[i].votos = 0;
    (*totalCandidatos)++;
   printf("\nCandidato '%s' cadastrado com sucesso!\n", nome);
     pausarTela();
}

void listaCandidatos(Candidato candidatos[], int totalCandidatos) {
    limparTela();
    cabecalho("LISTA DE CANDIDATOS");

    if (totalCandidatos == 0) {
        printf("\nNenhum candidato cadastrado no sistema.\n");
    } else {
        printf("\n%-10s | %-30s\n", "Numero", "Nome do Candidato");
        for(int i = 0; i < totalCandidatos; i++) {
            printf("%-10d | %-30s\n", candidatos[i].numero, candidatos[i].nome);
        }
    }
    pausarTela();
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

// corrigi as classes anteiroes, e terminei a classe relatorio
void relatorio(Candidato candidatos[], int totalCandidatos, int votosNulos, int votosBrancos) {
    limparTela();
    cabecalho("RELATORIO DE LOGS DO SISTEMA");

    FILE *f = fopen("relatorio.log", "r");
    if (f == NULL) {
        printf("\nERRO: Nao foi possivel abrir o arquivo de relatorio (log).\n");
        pausarTela();
        return;
    }

    // usei esse tipo de leitura de arquivo porque eh mais simples, mais economico em memoria, menos probelmas de formatacao e vai suprir bem a necessidade
    printf("\n");
    char ch;
    // fgetc vai ler e retornar EOF quando acabar o que puder ler ou der erro
    while((ch = fgetc(f)) != EOF) {
        putchar(ch);
    }

    fclose(f);
    printf("\n");
    pausarTela();
}
