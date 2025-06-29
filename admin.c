#include "admin.h"
#include "votacao.h"
#include <ctype.h> // <--- Inclui para toupper


void criarCandidato(Candidato candidato[], int *quantCandidatos) {
    
=======
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
    int i = *quantCandidatos;
    strcpy(candidato[i].nome, nome);
    candidato[i].numero = numero;
    candidato[i].votos = 0;
    candidato[i].ativo = 1;
    (*quantCandidatos)++;
    registrarLog("Novo candidato cadastrado no sistema!");
}

void listaCandidatos(Candidato candidato[]) {
    for(int i = 0; i < MAX_CANDIDATOS; i++) {
        if (candidato[i].ativo == 1)
        printf("%-5d %-30s %-10d %-5s\n", candidato[i].numero, candidato[i].nome, candidato[i].votos, "Ativo");
    }
    pausarTela();
}


void resultados(Candidato candidatos[], int totalCandidatos, int votosNulos, int votosBrancos) {
    (void)candidatos;
    (void)totalCandidatos;
    (void)votosNulos;
    (void)votosBrancos;

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

// Auxiliar para verificar se o número do candidato já existe
int numeroExiste(Candidato candidatos[], int totalCandidatos, int numero) {
    for (int i = 0; i < totalCandidatos; i++) {
        if (candidatos[i].numero == numero && candidatos[i].ativo == 1) { // Verifica ativos
            return 1; // Número já existe
        }
    }
    return 0; // Número não existe
}

//Excluir candidato (na lógica)
void excluirCandidato(Candidato candidatos[], int *totalCandidatos) {
    limparTela();
    cabecalho("EXCLUIR CANDIDATO");
    printf("\n");

    if (*totalCandidatos == 0) {
        printf("Nenhum candidato para excluir.\n");
        pausarTelaInt();
        return;
    }

    listaCandidatos(candidatos); // Mostra os candidatos existentes
    printf("\n");

    int numeroExcluir;
    printf("Digite o numero do candidato a ser excluido: ");
    scanf("%d", &numeroExcluir);

    int encontrado = 0;
    for (int i = 0; i < *totalCandidatos; i++) { // Itera sobre o totalCandidatos
        if (candidatos[i].numero == numeroExcluir && candidatos[i].ativo == 1) { // Verifica se está ativo
            candidatos[i].ativo = 0;
            printf("Candidato %s (Numero: %d) excluido com sucesso (logicamente).\n", candidatos[i].nome, candidatos[i].numero);
            char log_msg[100];
            sprintf(log_msg, "Candidato excluido (logicamente): Numero %d", numeroExcluir);
            registrarLog(log_msg);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Candidato com numero %d nao encontrado ou ja esta inativo.\n", numeroExcluir);
        char log_msg[100];
        sprintf(log_msg, "Tentativa de excluir candidato nao encontrado: Numero %d", numeroExcluir);
        registrarLog(log_msg);
    }
    pausarTelaInt();
}

void relatorio(Candidato candidatos[], int totalCandidatos, int votosNulos, int votosBrancos) { 
    (void)candidatos;
    (void)totalCandidatos;
    (void)votosNulos;
    (void)votosBrancos;
        FILE *f = fopen(ARQUIVO_LOG, "r");
        if (f == NULL) {
            printf("ERRO: Nao foi possivel abrir o arquivo de relatorio.\n");
            pausarTelaInt();
            return;
        }
        
        char ch;
    while ((ch = getc(f)) != EOF) {
        putchar(ch);
    }
    printf("\n");


    fclose(f);
    pausarTelaInt();
}
