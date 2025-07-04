#include "votacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para strtok, strcpy
#include <ctype.h>  // Para toupper

// --- Funções Auxiliares para Carregar/Salvar ---

// Função auxiliar para carregar candidatos (formato texto: nome|numero|votos|ativo)
static void carregarCandidatosFromFile(Candidato candidatos[], int *totalCandidatos) {
    FILE *arquivo = fopen(ARQUIVO_CANDIDATOS_TXT, "r");
    if (arquivo == NULL) {
        *totalCandidatos = 0;
        return;
    }

    *totalCandidatos = 0;
    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (*totalCandidatos >= MAX_CANDIDATOS) {
            printf("Aviso: Limite maximo de candidatos atingido ao carregar dados. Alguns candidatos podem nao ter sido carregados.\n");
            break;
        }
        linha[strcspn(linha, "\n")] = 0; // Remove newline

        char *token = strtok(linha, "|");
        if (token != NULL) strcpy(candidatos[*totalCandidatos].nome, token);
        token = strtok(NULL, "|");
        if (token != NULL) candidatos[*totalCandidatos].numero = atoi(token);
        token = strtok(NULL, "|");
        if (token != NULL) candidatos[*totalCandidatos].votos = atoi(token);
        token = strtok(NULL, "|");
        if (token != NULL) candidatos[*totalCandidatos].ativo = atoi(token); // Carrega o status 'ativo'

        (*totalCandidatos)++;
    }
    fclose(arquivo);
    registrarLog("Candidatos carregados do arquivo TXT.");
}

// Função auxiliar para salvar candidatos (formato texto: nome|numero|votos|ativo)
static void salvarCandidatosToFile(Candidato candidatos[], int totalCandidatos) {
    FILE *arquivo = fopen(ARQUIVO_CANDIDATOS_TXT, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo de candidatos para salvar");
        registrarLog("ERRO: Nao foi possivel salvar os dados dos candidatos.");
        return;
    }
    for (int i = 0; i < totalCandidatos; i++) {
        fprintf(arquivo, "%s|%d|%d|%d\n", candidatos[i].nome, candidatos[i].numero, candidatos[i].votos, candidatos[i].ativo);
    }
    fclose(arquivo);
    registrarLog("Candidatos salvos no arquivo TXT.");
}

// Função auxiliar para carregar eleitores (formato texto: nome|cpf|idade|votou)
static void carregarEleitoresFromFile(Eleitor eleitores[], int *totalEleitores) {
    FILE *arquivo = fopen(ARQUIVO_ELEITORES_TXT, "r");
    if (arquivo == NULL) {
        *totalEleitores = 0;
        return;
    }

    *totalEleitores = 0;
    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (*totalEleitores >= MAX_ELEITORES) {
            printf("Aviso: Limite maximo de eleitores atingido ao carregar dados. Alguns eleitores podem nao ter sido carregados.\n");
            break;
        }
        linha[strcspn(linha, "\n")] = 0; // Remove newline

        char *token = strtok(linha, "|");
        if (token != NULL) strcpy(eleitores[*totalEleitores].nome, token);
        token = strtok(NULL, "|");
        if (token != NULL) strcpy(eleitores[*totalEleitores].cpf, token);
        token = strtok(NULL, "|");
        if (token != NULL) eleitores[*totalEleitores].idade = atoi(token);
        token = strtok(NULL, "|");
        if (token != NULL) eleitores[*totalEleitores].votou = atoi(token);

        (*totalEleitores)++;
    }
    fclose(arquivo);
    registrarLog("Eleitores carregados do arquivo TXT.");
}

// Função auxiliar para salvar eleitores (formato texto: nome|cpf|idade|votou)
static void salvarEleitoresToFile(Eleitor eleitores[], int totalEleitores) {
    FILE *arquivo = fopen(ARQUIVO_ELEITORES_TXT, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo de eleitores para salvar");
        registrarLog("ERRO: Nao foi possivel salvar os dados dos eleitores.");
        return;
    }
    for (int i = 0; i < totalEleitores; i++) {
        fprintf(arquivo, "%s|%s|%d|%d\n", eleitores[i].nome, eleitores[i].cpf, eleitores[i].idade, eleitores[i].votou);
    }
    fclose(arquivo);
    registrarLog("Eleitores salvos no arquivo TXT.");
}

// Função auxiliar para carregar o estado da votação (fase, nulos, brancos)
static void carregarEstadoVotacaoFromFile(int *fase_ptr, int *votosNulos, int *votosBrancos) {
    FILE *arquivo = fopen(ARQUIVO_ESTADO_VOTACAO_TXT, "r");
    if (arquivo == NULL) {
        *fase_ptr = FASE_CADASTRO;
        *votosNulos = 0;
        *votosBrancos = 0;
        return;
    }

    fscanf(arquivo, "Fase: %d\n", fase_ptr);
    fscanf(arquivo, "Votos Nulos: %d\n", votosNulos);
    fscanf(arquivo, "Votos Brancos: %d\n", votosBrancos);

    fclose(arquivo);
    registrarLog("Estado da votacao carregado do arquivo TXT.");
}

// Função auxiliar para salvar o estado da votação (fase, nulos, brancos)
static void salvarEstadoVotacaoToFile(EstadoUrna fase_val, int votosNulos, int votosBrancos) {
    FILE *arquivo = fopen(ARQUIVO_ESTADO_VOTACAO_TXT, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo de estado da votacao para salvar");
        registrarLog("ERRO: Nao foi possivel salvar o estado da votacao.");
        return;
    }
    fprintf(arquivo, "Fase: %d\n", (int)fase_val);
    fprintf(arquivo, "Votos Nulos: %d\n", votosNulos);
    fprintf(arquivo, "Votos Brancos: %d\n", votosBrancos);

    fclose(arquivo);
    registrarLog("Estado da votacao salvo no arquivo TXT.");
}

// --- Funções Principais de Gerenciamento ---

void carregarDados(Candidato candidatos[], int *totalCandidatos,
                   Eleitor eleitores[], int *totalEleitores,
                   int *votosNulos, int *votosBrancos, EstadoUrna *fase_ptr) {
    limparTelaInt();
    cabecalho("CARREGANDO DADOS DA VOTACAO");
    printf("\n");

    carregarCandidatosFromFile(candidatos, totalCandidatos);
    carregarEleitoresFromFile(eleitores, totalEleitores);
    carregarEstadoVotacaoFromFile((int *)&fase, votosNulos, votosBrancos); // Cast para (int*) pois 'fase' é EstadoUrna

    printf("Dados da votacao carregados com sucesso!\n");
    registrarLog("Dados da votacao carregados com sucesso.");
    pausarTelaInt();
}

void salvarDados(Candidato candidatos[], int totalCandidatos,
                 Eleitor eleitores[], int totalEleitores,
                 EstadoUrna fase_actual, int votosNulos, int votosBrancos) {
    limparTelaInt();
    cabecalho("SALVANDO DADOS DA VOTACAO");
    printf("\n");

    salvarCandidatosToFile(candidatos, totalCandidatos);
    salvarEleitoresToFile(eleitores, totalEleitores);
    salvarEstadoVotacaoToFile(fase_actual, votosNulos, votosBrancos);

    printf("Dados da votacao salvos com sucesso!\n");
    registrarLog("Dados da votacao salvos com sucesso.");
    pausarTelaInt();
}

void criarUrna(Candidato candidatos[], int *totalCandidatos,
               Eleitor eleitores[], int *totalEleitores,
               int *votosNulos, int *votosBrancos) {
    limparTelaInt();
    cabecalho("CRIAR NOVA URNA / INICIAR NOVA VOTACAO");
    printf("\n");

    printf("Esta operacao ira apagar todos os dados da votacao atual e iniciar uma nova.\n");
    printf("Tem certeza que deseja continuar? (S/N): ");
    char confirmacao;
    scanf(" %c", &confirmacao);
    confirmacao = toupper(confirmacao);

    if (confirmacao == 'S') {
        // Resetar candidatos em memória e apagar arquivo
        *totalCandidatos = 0;
        // Reinicializa todos os candidatos em memória, marcando-os como inativos e zerando votos
        for (int i = 0; i < MAX_CANDIDATOS; i++) {
            strcpy(candidatos[i].nome, "");
            candidatos[i].numero = 0;
            candidatos[i].votos = 0;
            candidatos[i].ativo = 0; // Marcar como inativo
        }
        remove(ARQUIVO_CANDIDATOS_TXT); // Apaga o arquivo físico

        // Resetar eleitores em memória e apagar arquivo
        *totalEleitores = 0;
        // Reinicializa todos os eleitores em memória (opcional, pois são carregados)
        for (int i = 0; i < MAX_ELEITORES; i++) {
            strcpy(eleitores[i].nome, "");
            strcpy(eleitores[i].cpf, "");
            eleitores[i].idade = 0;
            eleitores[i].votou = 0;
        }
        remove(ARQUIVO_ELEITORES_TXT); // Apaga o arquivo físico

        // Resetar estado da votação e apagar arquivo
        fase = FASE_CADASTRO; // Resetar a variável global 'fase'
        *votosNulos = 0;
        *votosBrancos = 0;
        remove(ARQUIVO_ESTADO_VOTACAO_TXT);

        // Opcional: remover o arquivo de relatório final se existir
        remove(ARQUIVO_RELATORIO_FINAL);

        printf("Nova urna criada! Todos os dados anteriores foram resetados.\n");
        registrarLog("Nova urna criada. Dados anteriores resetados.");
    } else {
        printf("Operacao cancelada. A urna atual nao foi modificada.\n");
        registrarLog("Criacao de nova urna cancelada pelo usuario.");
    }
    pausarTelaInt();
}

void gerenciarFase(EstadoUrna *fase_ptr) {
    limparTelaInt();
    cabecalho("GERENCIAR FASE DA VOTACAO");
    printf("\n");

    printf("Fase atual: ");
    switch (*fase_ptr) {
        case FASE_CADASTRO: printf("CADASTRO\n"); break;
        case FASE_VOTACAO: printf("VOTACAO\n"); break;
        case FASE_APURACAO: printf("APURACAO\n"); break;
    }
    printf("\n");

    printf("Selecione a proxima fase:\n");
    printf("\t1 - FASE DE CADASTRO\n");
    printf("\t2 - FASE DE VOTACAO\n");
    printf("\t3 - FASE DE APURACAO\n");
    printf("\t0 - Voltar\n");
    printf("\n");

    int opcao;
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            if (*fase_ptr == FASE_APURACAO) {
                printf("Nao e possivel voltar para a fase de CADASTRO apos a APURACAO. Crie uma nova urna.\n");
                registrarLog("ERRO: Tentativa de reverter fase para CADASTRO apos APURACAO.");
            } else {
                *fase_ptr = FASE_CADASTRO;
                printf("Fase alterada para CADASTRO.\n");
                registrarLog("Fase da votacao alterada para CADASTRO.");
            }
            break;
        case 2:
            if (*fase_ptr == FASE_CADASTRO) {
                *fase_ptr = FASE_VOTACAO;
                printf("Fase alterada para VOTACAO. Cadastros serao desabilitados.\n");
                registrarLog("Fase da votacao alterada para VOTACAO.");
            } else if (*fase_ptr == FASE_APURACAO) {
                 printf("Nao e possivel voltar para a fase de VOTACAO apos a APURACAO.\n");
                 registrarLog("ERRO: Tentativa de reverter fase para VOTACAO apos APURACAO.");
            } else {
                printf("Ja esta na fase de VOTACAO.\n");
            }
            break;
        case 3:
            if (*fase_ptr == FASE_APURACAO) {
                printf("Ja esta na fase de APURACAO.\n");
            } else {
                *fase_ptr = FASE_APURACAO;
                printf("Fase alterada para APURACAO. A votacao esta encerrada.\n");
                registrarLog("Fase da votacao alterada para APURACAO.");
            }
            break;
        case 0:
            printf("Voltando ao menu anterior.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
    }
    pausarTelaInt();
}