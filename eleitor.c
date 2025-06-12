#include "eleitor.h"

#include "utils.h"

int validarCpf (Eleitor eleitores[], int totalEleitores, const char* cpf) {
    FILE* arquivo = fopen(ELEITORES, "r");
    if (arquivo == NULL) {
        return 0;
    }

    char linha[tam];
    
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char* token = strtok(linha, "|");
        token = strtok(NULL, "|"); // Pega o CPF
        
        if (token != NULL && strcmp(token, cpf) == 0) {
            fclose(arquivo);
            return 1; 
        }
    }
    return 0;
}

void cadastroEleitor(Eleitor listaDeEleitores[], int *totalEleitores) {
    if(fase == FASE_CADASTRO) {
        if (*totalEleitores >= MAX_ELEITORES) {
            printf("ERRO: Limite maximo de eleitores atingido!\n");
            return;
        }

        Eleitor novoEleitor;

        printf("Informe os seguintes dados: \n");
        printf("Nome completo: ");
        scanf(" %[^\n]", novoEleitor.nome);
        printf("CPF (somente numeros): ");
        scanf("%11s", novoEleitor.cpf); 
        
        //chama funçao pra verificar se ja existe o cpf cadastrado
        if (validarCpf(listaDeEleitores, *totalEleitores, novoEleitor.cpf)) {
            printf("\nErro: CPF ja cadastrado no sistema.\n");
            pausarTelaInt();
            return;
        }
        
        printf("Idade: ");
        scanf("%d", &novoEleitor.idade);
        
        if (novoEleitor.idade < 18) {
            printf("\nErro: Eleitor deve ter no minimo 18 anos para se cadastrar.\n");
            pausarTela(3000);
            return;
        }
        
        FILE* arquivo = fopen(ELEITORES, "a");
            if (arquivo == NULL) {
                printf("\nErro ao abrir arquivo de eleitores!\n");
                pausarTela(3000);
                return;
            }
            
            novoEleitor.votou = 0;

            fprintf(arquivo, "%s|%s|%d|%d\n", 
                    novoEleitor.nome, 
                    novoEleitor.cpf, 
                    novoEleitor.idade,
                    novoEleitor.votou); // Como acabou de cadastrar o eleitor, então inicializa com 0

        fclose(arquivo);

        registrarLog("Novo eleitor cadastrado no sistema.");
    } else {
        printf("A fase de cadastro terminou! Nao sera possivel realizar nenhum cadastro.");
        pausarTelaInt();
    }
}

void votar(Candidato candidatos[], int totalCandidatos, Eleitor *eleitorLogado) {
    if (fase != FASE_VOTACAO) {
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
    printf("Digite o numero do seu candidato: ");
    scanf("%d", &numeroVoto);

    int indiceCandidato = -1;
    for (int i = 0; i < totalCandidatos; i++) {
        if (candidatos[i]->numero == numeroVoto) {
            indiceCandidato = i;
            break;
        }
    }

    if (indiceCandidato != -1) {
        candidatos[indiceCandidato]->votos++;
        eleitorLogado->votou = 1;
        printf("Voto realizado com sucesso!\n");
        registrarLog("Voto registrado com sucesso.");
    } else {
        printf("Candidato nao encontrado. Seu voto sera computado como NULO.\n");
        // Lógica do voto nulo
    }
    
    pausarTelaInt();
}