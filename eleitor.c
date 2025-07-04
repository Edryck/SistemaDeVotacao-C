#include "eleitor.h"

int validarCpf (Eleitor eleitores[], int totalEleitores, const char* cpf) {
    FILE* arquivo = fopen(ARQUIVO_ELEITORES_TXT, "r"); 
    if (arquivo == NULL) {
        return 0;
    }

    char linha[tam];
    
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char temp_linha[tam];
        strcpy(temp_linha, linha); // Cópia para strtok, pois strtok modifica a string

        char* token = strtok(temp_linha, "|");
        token = strtok(NULL, "|"); // Pega o CPF

        
        if (token != NULL && strcmp(token, cpf) == 0) {
            fclose(arquivo);
            return 1; 
        }
    }
    fclose(arquivo);
    return 0;
}

void cadastroEleitor(Eleitor listaDeEleitores[], int *totalEleitores, EstadoUrna *fase_ptr) {
    // Usa a variável global 'fase'
    if(*fase_ptr == FASE_CADASTRO) {
        if (*totalEleitores >= MAX_ELEITORES) {
            printf("ERRO: Limite maximo de eleitores atingido!\n");
            pausarTelaInt();
            return;
        }

        Eleitor novoEleitor;

        printf("Informe os seguintes dados: \n");
        printf("Nome completo: ");
        while (getchar() != '\n' && getchar() != EOF);
        fgets(novoEleitor.nome, sizeof(novoEleitor.nome), stdin);
        novoEleitor.nome[strcspn(novoEleitor.nome, "\n")] = '\0';
        // Validação para garantir que o cpf tenha 11 digitos
        do {
            printf("CPF (somente numeros): ");
            fgets(novoEleitor.cpf, sizeof(novoEleitor.cpf), stdin);
            novoEleitor.cpf[strcspn(novoEleitor.cpf, "\n")] = '\0';
            if (strlen(novoEleitor.cpf) != 11) {
                printf("Erro: O CPF deve conter exatamente 11 digitos.\n");
    	    }
        } while (strlen(novoEleitor.cpf) != 11);

        //chama funçao pra verificar se ja existe o cpf cadastrado
        if (validarCpf(listaDeEleitores, *totalEleitores, novoEleitor.cpf)) {
            printf("\nErro: CPF ja cadastrado no sistema.\n");
            pausarTelaInt();
            return;
        }
        
        printf("Idade: ");
        scanf("%d", &novoEleitor.idade);

        char bufVazio[4]; 
       	fgets(bufVazio, sizeof(bufVazio), stdin);  
        
        if (novoEleitor.idade < 18) {
            printf("\nErro: Eleitor deve ter no minimo 18 anos para se cadastrar.\n");
            pausarTelaInt();
            return;
        }

        // Adiciona o novo eleitor à lista em memória
        listaDeEleitores[*totalEleitores] = novoEleitor;
        listaDeEleitores[*totalEleitores].votou = 0; // Inicializa votou em 0
        (*totalEleitores)++;

        printf("\nEleitor cadastrado com sucesso!\n\n");
        printf("Nome: %s\n", novoEleitor.nome);
        printf("CPF: %s\n", novoEleitor.cpf);
        printf("Idade: %d\n", novoEleitor.idade);
        registrarLog("Novo eleitor cadastrado no sistema.");
        pausarTelaInt();
    } else {
        printf("A fase de cadastro terminou! Nao sera possivel realizar nenhum cadastro.");
        pausarTelaInt();
    }
}

void votar(Candidato candidatos[], int totalCandidatos, Eleitor *eleitorLogado, int *votosNulos, int *votosBrancos, EstadoUrna *fase_ptr) {
    if (*fase_ptr != FASE_VOTACAO) {
        printf("A fase de votacao nao esta ativa!\n");
        pausarTelaInt();
        return;
    }
    
    if (eleitorLogado->votou == 1) {
        printf("Voce ja votou! Nao pode votar novamente!\n");
        registrarLog("Tentativa de realizar mais de um voto!");
        pausarTelaInt();
        return;
    }

    int numeroVoto;
    printf("Digite o numero do seu candidato (0 para BRANCO): "); // Adiciona opção para branco
    scanf("%d", &numeroVoto);

    int indiceCandidato = -1;
    for (int i = 0; i < totalCandidatos; i++) {
        if (candidatos[i].numero == numeroVoto && candidatos[i].ativo == 1) { // <--- ALTERADO DE '->' PARA '.' e adicionado 'ativo'
            indiceCandidato = i;
            break;
        }
    }

   if (numeroVoto == 0) { // Voto em Branco
        (*votosBrancos)++;
        eleitorLogado->votou = 1;
        printf("Voto em BRANCO registrado com sucesso!\n");
        registrarLog("Voto em BRANCO registrado.");
    } else if (indiceCandidato != -1) {
        candidatos[indiceCandidato].votos++; // <--- ALTERADO DE '->' PARA '.'
        eleitorLogado->votou = 1;
        printf("Voto realizado com sucesso em %s!\n", candidatos[indiceCandidato].nome); // <--- ALTERADO DE '->' PARA '.'
        char log_msg[100];
        sprintf(log_msg, "Voto registrado com sucesso para candidato Numero: %d", numeroVoto);
        registrarLog(log_msg);
    } else {
        (*votosNulos)++; // Voto Nulo
        eleitorLogado->votou = 1;
        printf("Candidato nao encontrado. Seu voto sera computado como NULO.\n");
        registrarLog("Voto NULO registrado.");
    }
    pausarTelaInt();
}