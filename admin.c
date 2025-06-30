#include "admin.h"
#include "dados.h"
#include "utils.h"
#include <time.h>
//eu ACHO que ta funfando
const char* NOME_ARQUIVO = "urna.txt";

int numeroExisteNoArquivo(int numero) {
    FILE *f = fopen(NOME_ARQUIVO, "r");
    if (f == NULL) {
        registrarLog("ERRO: Falha ao abrir o arquivo da urna para verificar numero de candidato.");
        return 0;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), f) != NULL) {
        int numArquivo;
        sscanf(linha, "%d,", &numArquivo);
        if (numArquivo == numero) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void criarCandidato(Candidato candidato[], int *totalCandidatos) {
    limparTela();
    cabecalho("CRIAR CANDIDATOS");
    printf("\n");

    int numero;
    do {
        printf("Digite o numero do candidato (deve ser maior que 0): ");
        scanf("%d", &numero);
        while(getchar() != '\n');

        if (numero <= 0) {    
            printf("ERRO: Numero invalido! Tente novamente.\n");    
            registrarLog("ERRO: Tentativa de criar candidato com numero invalido (menor ou igual a 0).");
        } else if (numeroExisteNoArquivo(numero)) {    
            printf("ERRO: Esse numero ja pertence a outro candidato! Tente novamente\n");    
            registrarLog("ERRO: Tentativa de criar candidato com numero ja existente.");
            numero = 0;    
        }

    } while(numero <= 0);

    char nome[45];
    printf("Informe o nome do candidato: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    FILE *f = fopen(NOME_ARQUIVO, "a");
    if (f == NULL) {
        printf("ERRO: Nao foi possivel abrir o banco de dados de candidatos.\n");
        registrarLog("ERRO: Nao foi possivel abrir o banco de dados de candidatos para criacao.");
        pausarTela();
        return;
    }

    fprintf(f, "%d,%d,%d,%s\n", numero, 0, 1, nome);
    fclose(f);

    printf("\nCandidato '%s' cadastrado com sucesso!\n", nome);
    char logMensagem[100];
    sprintf(logMensagem, "Candidato '%s' (Numero: %d) cadastrado com sucesso.", nome, numero);
    registrarLog(logMensagem);
    pausarTela();
}

void listaCandidatos(Candidato candidatos[], int *totalCandidatos) {
    limparTela();
    cabecalho("LISTA DE CANDIDATOS");

    FILE *f = fopen(NOME_ARQUIVO, "r");
    if (f == NULL) {
        printf("\nNenhum candidato cadastrado no sistema.\n");
        registrarLog("INFO: Nao ha candidatos cadastrados no sistema para listar.");
        pausarTela();
        return;
    }

    printf("\n%-10s | %-30s\n", "Numero", "Nome do Candidato");

    char linha[256];
    int contador = 0;
    while(fgets(linha, sizeof(linha), f) != NULL) {
        Candidato temp;
        sscanf(linha, "%d,%d,%d,%[^\n]", &temp.numero, &temp.votos, &temp.ativo, temp.nome);

        if (temp.ativo == 1) {    
            printf("%-10d | %-30s\n", temp.numero, temp.nome);    
            contador++;    
        }
    }
    fclose(f);

    if (contador == 0) {
        printf("\nNenhum candidato ativo no sistema.\n");
        registrarLog("INFO: Nao ha candidatos ativos para listar.");
    }

    pausarTela();
}

void excluirCandidato(Candidato candidatos[], int *totalCandidatos) {
    limparTela();
    cabecalho("EXCLUIR CANDIDATO");

    int numeroParaExcluir;
    printf("\nDigite o numero do candidato que deseja excluir: ");
    scanf("%d", &numeroParaExcluir);

    if (!numeroExisteNoArquivo(numeroParaExcluir)) {
        printf("\nERRO: Candidato com o numero %d nao encontrado.\n", numeroParaExcluir);
        char logMensagem[100];
        sprintf(logMensagem, "ERRO: Tentativa de excluir candidato com o numero %d nao encontrado.", numeroParaExcluir);
        registrarLog(logMensagem);
        pausarTela();
        return;
    }

    FILE *original = fopen(NOME_ARQUIVO, "r");
    FILE *temporario = fopen("temp.txt", "w");

    if (original == NULL || temporario == NULL) {
        printf("ERRO: Nao foi possivel modificar o banco de dados.\n");
        registrarLog("ERRO: Nao foi possivel abrir arquivos para exclusao de candidato (original ou temporario).");
        pausarTela();
        return;
    }

    char linha[256];
    char nomeExcluido[45] = "";
    while (fgets(linha, sizeof(linha), original) != NULL) {
        Candidato temp;
        sscanf(linha, "%d,%d,%d,%[^\n]", &temp.numero, &temp.votos, &temp.ativo, temp.nome);

        if (temp.numero == numeroParaExcluir) {    
            temp.ativo = 0;    
            strcpy(nomeExcluido, temp.nome);    
            fprintf(temporario, "%d,%d,%d,%s\n", temp.numero, temp.votos, temp.ativo, temp.nome);    
        } else {    
            fputs(linha, temporario);    
        }
    }

    fclose(original);
    fclose(temporario);

    remove(NOME_ARQUIVO);
    rename("temp.txt", NOME_ARQUIVO);

    printf("\nCandidato '%s' excluido com sucesso.\n", nomeExcluido);
    char logMensagem[100];
    sprintf(logMensagem, "Candidato '%s' (Numero: %d) excluido com sucesso.", nomeExcluido, numeroParaExcluir);
    registrarLog(logMensagem);
    pausarTela();
}
