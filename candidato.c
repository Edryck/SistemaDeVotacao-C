#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Para toupper, se necessário para ordenação insensível a maiúsculas/minúsculas

// --- Constantes ---
#define NOME_ARQUIVO_CANDIDATOS "candidatos.dat"
#define MAX_NOME 100
#define MAX_NOME_CARGO 50

// --- Estruturas ---

// Struct para o Cargo
typedef struct {
    char nome[MAX_NOME_CARGO];
} Cargo;

// Struct para o Candidato
typedef struct {
    int id;                         // Chave primária
    char nome[MAX_NOME];
    Cargo cargo;
    int numero_votacao;
    int votos;                      // Para armazenar os votos do candidato
    int ativo;                      // 1 para ativo, 0 para excluído/inativo
} Candidato;

// --- Protótipos das Funções ---
int obterProximoId();
void cadastrarCandidato();
long buscarPosicaoCandidatoPorId(int id); // Retorna a posição do registro no arquivo ou -1
void editarCandidato();
void excluirCandidato(); // Logicamente, marcando como inativo
void visualizarCandidatos();
void mostrarResultadosVotacao();
int compararCandidatosPorNome(const void *a, const void *b);
int compararCandidatosPorVotos(const void *a, const void *b);

// --- Função Principal (Menu Simples) ---
int main() {
    int opcao;
    do {
        printf("\n--- Sistema de Gerenciamento de Candidatos ---\n");
        printf("1. Cadastrar Candidato\n");
        printf("2. Editar Candidato\n");
        printf("3. Excluir Candidato\n");
        printf("4. Visualizar Candidatos\n");
        printf("5. Mostrar Resultados da Votacao\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do newline

        switch (opcao) {
            case 1:
                cadastrarCandidato();
                break;
            case 2:
                editarCandidato();
                break;
            case 3:
                excluirCandidato();
                break;
            case 4:
                visualizarCandidatos();
                break;
            case 5:
                mostrarResultadosVotacao();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

// --- Implementação das Funções ---

/**
 * @brief Obtém o próximo ID disponível para um novo candidato.
 * Lê o arquivo de candidatos, encontra o maior ID existente e retorna o maior ID + 1.
 * Se o arquivo não existir ou estiver vazio, retorna 1.
 * @return O próximo ID a ser usado.
 */
int obterProximoId() {
    FILE *arquivo = fopen(NOME_ARQUIVO_CANDIDATOS, "rb");
    Candidato tempCandidato;
    int maxId = 0;

    if (arquivo != NULL) {
        while (fread(&tempCandidato, sizeof(Candidato), 1, arquivo) == 1) {
            if (tempCandidato.id > maxId) {
                maxId = tempCandidato.id;
            }
        }
        fclose(arquivo);
    }
    return maxId + 1;
}

/**
 * @brief Cadastra um novo candidato no sistema.
 * Solicita os dados do candidato ao usuário e salva em um arquivo binário.
 * Cada novo candidato é adicionado ao final do arquivo.
 */
void cadastrarCandidato() {
    Candidato novoCandidato;
    FILE *arquivo;

    novoCandidato.id = obterProximoId();
    novoCandidato.ativo = 1; // Novo candidato sempre ativo
    novoCandidato.votos = 0; // Inicializa votos com 0

    printf("\n--- Cadastro de Novo Candidato (ID: %d) ---\n", novoCandidato.id);
    printf("Nome completo: ");
    fgets(novoCandidato.nome, MAX_NOME, stdin);
    novoCandidato.nome[strcspn(novoCandidato.nome, "\n")] = 0; // Remove o newline

    printf("Cargo (Ex: Presidente, Governador, Deputado): ");
    fgets(novoCandidato.cargo.nome, MAX_NOME_CARGO, stdin);
    novoCandidato.cargo.nome[strcspn(novoCandidato.cargo.nome, "\n")] = 0;

    printf("Numero para votacao: ");
    scanf("%d", &novoCandidato.numero_votacao);
    getchar(); // Limpar o buffer

    arquivo = fopen(NOME_ARQUIVO_CANDIDATOS, "ab"); // "ab" - append binary
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para cadastro");
        return;
    }

    fwrite(&novoCandidato, sizeof(Candidato), 1, arquivo);
    fclose(arquivo);

    printf("Candidato '%s' cadastrado com sucesso com ID %d!\n", novoCandidato.nome, novoCandidato.id);
}

/**
 * @brief Busca a posição (índice do registro) de um candidato pelo ID no arquivo.
 * @param id O ID do candidato a ser buscado.
 * @return A posição (base 0) do registro do candidato no arquivo se encontrado e ativo,
 * -1 se não encontrado ou inativo, -2 se erro ao abrir arquivo.
 */
long buscarPosicaoCandidatoPorId(int id) {
    FILE *arquivo = fopen(NOME_ARQUIVO_CANDIDATOS, "rb");
    Candidato tempCandidato;
    long posicao = 0;

    if (arquivo == NULL) {
        // perror("Arquivo de candidatos nao encontrado ou vazio na busca");
        return -2; // Indica erro ao abrir ou arquivo não existe
    }

    while (fread(&tempCandidato, sizeof(Candidato), 1, arquivo) == 1) {
        if (tempCandidato.id == id && tempCandidato.ativo == 1) {
            fclose(arquivo);
            return posicao; // Retorna o número do registro (0-indexed)
        }
        posicao++;
    }

    fclose(arquivo);
    return -1; // Não encontrado ou inativo
}

/**
 * @brief Permite editar os dados de um candidato existente.
 * O usuário informa o ID do candidato, o sistema o busca e, se encontrado,
 * permite a alteração dos dados, gravando-os na mesma posição no arquivo.
 */
void editarCandidato() {
    int idBusca;
    long posicaoRegistro; // Posição em termos de número de registros
    Candidato candidatoEditado;
    FILE *arquivo;

    printf("\n--- Editar Candidato ---\n");
    printf("Digite o ID do candidato que deseja editar: ");
    scanf("%d", &idBusca);
    getchar(); // Limpar buffer

    posicaoRegistro = buscarPosicaoCandidatoPorId(idBusca);

    if (posicaoRegistro == -2) {
        printf("Erro: Nao foi possivel abrir o arquivo de candidatos ou ele nao existe.\n");
        return;
    }
    if (posicaoRegistro == -1) {
        printf("Candidato com ID %d nao encontrado ou inativo.\n", idBusca);
        return;
    }

    // Abre o arquivo para leitura e escrita binária ("rb+")
    arquivo = fopen(NOME_ARQUIVO_CANDIDATOS, "rb+");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo para edicao");
        return;
    }

    // Posiciona o ponteiro do arquivo no início do registro correto
    fseek(arquivo, posicaoRegistro * sizeof(Candidato), SEEK_SET);

    // Lê o candidato existente para mostrar os dados atuais (opcional) ou para pegar o ID original
    if (fread(&candidatoEditado, sizeof(Candidato), 1, arquivo) != 1) {
        printf("Erro ao ler dados do candidato para edicao.\n");
        fclose(arquivo);
        return;
    }
    // Garante que o ID e o status de ativo não sejam alterados acidentalmente aqui
    // Os votos também devem ser preservados, a menos que a edição inclua isso.

    printf("Editando candidato: %s (ID: %d)\n", candidatoEditado.nome, candidatoEditado.id);
    printf("Novo nome (atual: %s): ", candidatoEditado.nome);
    fgets(candidatoEditado.nome, MAX_NOME, stdin);
    candidatoEditado.nome[strcspn(candidatoEditado.nome, "\n")] = 0;

    printf("Novo cargo (atual: %s): ", candidatoEditado.cargo.nome);
    fgets(candidatoEditado.cargo.nome, MAX_NOME_CARGO, stdin);
    candidatoEditado.cargo.nome[strcspn(candidatoEditado.cargo.nome, "\n")] = 0;

    printf("Novo numero para votacao (atual: %d): ", candidatoEditado.numero_votacao);
    scanf("%d", &candidatoEditado.numero_votacao);
    getchar(); // Limpar buffer

    // Volta para a posição correta para sobrescrever
    fseek(arquivo, posicaoRegistro * sizeof(Candidato), SEEK_SET);
    fwrite(&candidatoEditado, sizeof(Candidato), 1, arquivo);

    fclose(arquivo);
    printf("Candidato com ID %d atualizado com sucesso!\n", idBusca);
}

/**
 * @brief Exclui (logicamente) um candidato, marcando-o como inativo.
 * O usuário informa o ID, o sistema busca e, se encontrado, marca o campo 'ativo' como 0.
 */
void excluirCandidato() {
    int idBusca;
    long posicaoRegistro;
    Candidato candidatoParaExcluir;
    FILE *arquivo;

    printf("\n--- Excluir Candidato ---\n");
    printf("Digite o ID do candidato que deseja excluir: ");
    scanf("%d", &idBusca);
    getchar();

    posicaoRegistro = buscarPosicaoCandidatoPorId(idBusca); // Busca apenas ativos

    if (posicaoRegistro == -2) {
        printf("Erro: Nao foi possivel abrir o arquivo de candidatos ou ele nao existe.\n");
        return;
    }
    if (posicaoRegistro == -1) {
        printf("Candidato com ID %d nao encontrado ou ja esta inativo.\n", idBusca);
        return;
    }

    arquivo = fopen(NOME_ARQUIVO_CANDIDATOS, "rb+");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo para exclusao");
        return;
    }

    fseek(arquivo, posicaoRegistro * sizeof(Candidato), SEEK_SET);
    if (fread(&candidatoParaExcluir, sizeof(Candidato), 1, arquivo) != 1) {
        printf("Erro ao ler candidato para exclusao.\n");
        fclose(arquivo);
        return;
    }

    candidatoParaExcluir.ativo = 0; // Marca como inativo

    fseek(arquivo, posicaoRegistro * sizeof(Candidato), SEEK_SET); // Volta para sobrescrever
    fwrite(&candidatoParaExcluir, sizeof(Candidato), 1, arquivo);

    fclose(arquivo);
    printf("Candidato '%s' (ID: %d) marcado como excluido.\n", candidatoParaExcluir.nome, idBusca);
}


/**
 * @brief Função de comparação para qsort, para ordenar candidatos por nome.
 */
int compararCandidatosPorNome(const void *a, const void *b) {
    Candidato *cA = (Candidato *)a;
    Candidato *cB = (Candidato *)b;
    // Para ordenação case-insensitive, poderia usar strcasecmp (POSIX) ou converter para maiúsculas/minúsculas antes de strcmp.
    // Aqui, faremos uma comparação simples case-sensitive.
    return strcmp(cA->nome, cB->nome);
}

/**
 * @brief Visualiza todos os candidatos ativos registrados no sistema, ordenados alfabeticamente pelo nome.
 */
void visualizarCandidatos() {
    FILE *arquivo = fopen(NOME_ARQUIVO_CANDIDATOS, "rb");
    Candidato tempCandidato;
    Candidato *listaCandidatos = NULL;
    int contador = 0;
    int capacidade = 10; // Capacidade inicial do array dinâmico

    printf("\n--- Lista de Candidatos Ativos (Ordem Alfabetica) ---\n");

    if (arquivo == NULL) {
        printf("Nenhum candidato cadastrado ou arquivo nao encontrado.\n");
        return;
    }

    listaCandidatos = (Candidato *)malloc(capacidade * sizeof(Candidato));
    if (listaCandidatos == NULL) {
        perror("Erro de alocacao de memoria para listar candidatos");
        fclose(arquivo);
        return;
    }

    while (fread(&tempCandidato, sizeof(Candidato), 1, arquivo) == 1) {
        if (tempCandidato.ativo == 1) { // Processa apenas candidatos ativos
            if (contador == capacidade) {
                capacidade *= 2;
                Candidato *temp = (Candidato *)realloc(listaCandidatos, capacidade * sizeof(Candidato));
                if (temp == NULL) {
                    perror("Erro ao realocar memoria");
                    free(listaCandidatos);
                    fclose(arquivo);
                    return;
                }
                listaCandidatos = temp;
            }
            listaCandidatos[contador++] = tempCandidato;
        }
    }
    fclose(arquivo);

    if (contador == 0) {
        printf("Nenhum candidato ativo encontrado.\n");
    } else {
        qsort(listaCandidatos, contador, sizeof(Candidato), compararCandidatosPorNome);

        printf("%-5s %-30s %-20s %-10s\n", "ID", "Nome", "Cargo", "Numero");
        printf("---------------------------------------------------------------------\n");
        for (int i = 0; i < contador; i++) {
            printf("%-5d %-30s %-20s %-10d\n",
                   listaCandidatos[i].id,
                   listaCandidatos[i].nome,
                   listaCandidatos[i].cargo.nome,
                   listaCandidatos[i].numero_votacao);
        }
    }
    free(listaCandidatos);
}

/**
 * @brief Função de comparação para qsort, para ordenar candidatos por votos (decrescente).
 */
int compararCandidatosPorVotos(const void *a, const void *b) {
    Candidato *cA = (Candidato *)a;
    Candidato *cB = (Candidato *)b;
    return (cB->votos - cA->votos); // Decrescente
}

/**
 * @brief Exibe os resultados da votação.
 * Procura pelos cargos e imprime os votos de cada candidato por cargo, em ordem decrescente de votos.
 * (Nota: A lógica de registrar votos não está neste escopo, assume-se que `candidato.votos` está preenchido).
 */
void mostrarResultadosVotacao() {
    FILE *arquivo = fopen(NOME_ARQUIVO_CANDIDATOS, "rb");
    Candidato tempCandidato;
    Candidato *todosCandidatos = NULL;
    int numTodosCandidatos = 0;
    int capacidadeTodos = 10;

    printf("\n--- Resultados da Votacao ---\n");

    if (arquivo == NULL) {
        printf("Nenhum dado de candidato encontrado para mostrar resultados.\n");
        // Exemplo: Para simular, vamos pedir para cadastrar e votar (votos são 0 por padrão)
        // Para um sistema real, os votos seriam incrementados em outra parte do sistema.
        // Para este exemplo, você pode manualmente editar o arquivo .dat ou adicionar
        // uma função para "simular votos" se quiser ver resultados diferentes de 0.
        printf("Os votos sao inicializados com 0. Para testes, considere uma funcao para simular votos.\n");
        //return; // Comentado para permitir a listagem mesmo com 0 votos
    }

    // 1. Ler todos os candidatos ativos para a memória
    if (arquivo != NULL) {
        todosCandidatos = (Candidato *)malloc(capacidadeTodos * sizeof(Candidato));
        if (todosCandidatos == NULL) {
            perror("Erro de alocacao de memoria para resultados");
            fclose(arquivo);
            return;
        }
        while (fread(&tempCandidato, sizeof(Candidato), 1, arquivo) == 1) {
            if (tempCandidato.ativo == 1) {
                if (numTodosCandidatos == capacidadeTodos) {
                    capacidadeTodos *= 2;
                    Candidato *temp = (Candidato *)realloc(todosCandidatos, capacidadeTodos * sizeof(Candidato));
                    if (temp == NULL) {
                        perror("Erro ao realocar memoria para resultados");
                        free(todosCandidatos);
                        fclose(arquivo);
                        return;
                    }
                    todosCandidatos = temp;
                }
                todosCandidatos[numTodosCandidatos++] = tempCandidato;
            }
        }
        fclose(arquivo);
    }


    if (numTodosCandidatos == 0) {
        printf("Nenhum candidato ativo para mostrar resultados.\n");
        if (todosCandidatos) free(todosCandidatos);
        return;
    }

    // 2. Identificar cargos únicos
    char cargosUnicos[numTodosCandidatos][MAX_NOME_CARGO]; // Superestima, mas simples
    int numCargosUnicos = 0;
    for (int i = 0; i < numTodosCandidatos; i++) {
        int encontrado = 0;
        for (int j = 0; j < numCargosUnicos; j++) {
            if (strcmp(todosCandidatos[i].cargo.nome, cargosUnicos[j]) == 0) {
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            strcpy(cargosUnicos[numCargosUnicos++], todosCandidatos[i].cargo.nome);
        }
    }

    if (numCargosUnicos == 0) {
         printf("Nenhum cargo encontrado entre os candidatos ativos.\n");
    }

    // 3. Para cada cargo único, filtrar candidatos, ordenar por votos e imprimir
    for (int i = 0; i < numCargosUnicos; i++) {
        printf("\n--- Cargo: %s ---\n", cargosUnicos[i]);
        Candidato *candidatosDoCargo = (Candidato *)malloc(numTodosCandidatos * sizeof(Candidato)); // Max possível
        if (candidatosDoCargo == NULL) {
            perror("Erro de alocacao para candidatos do cargo");
            continue; // Pula para o próximo cargo
        }
        int numCandidatosCargo = 0;

        for (int j = 0; j < numTodosCandidatos; j++) {
            if (strcmp(todosCandidatos[j].cargo.nome, cargosUnicos[i]) == 0) {
                candidatosDoCargo[numCandidatosCargo++] = todosCandidatos[j];
            }
        }

        if (numCandidatosCargo > 0) {
            qsort(candidatosDoCargo, numCandidatosCargo, sizeof(Candidato), compararCandidatosPorVotos);

            printf("%-30s %-10s %-5s\n", "Nome do Candidato", "Numero", "Votos");
            printf("-------------------------------------------------------\n");
            for (int k = 0; k < numCandidatosCargo; k++) {
                printf("%-30s %-10d %-5d\n",
                       candidatosDoCargo[k].nome,
                       candidatosDoCargo[k].numero_votacao,
                       candidatosDoCargo[k].votos);
            }
        } else {
            printf("Nenhum candidato ativo para este cargo.\n");
        }
        free(candidatosDoCargo);
    }

    if (todosCandidatos) free(todosCandidatos);
}
