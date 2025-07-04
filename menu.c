#include "menu.h"
#include "dados.h"
#include "votacao.h"

#define tam 256
#define ADMIN_USER "admin"
#define ADMIN_PASS "senha123"

void menuInicial(Candidato candidatos[], int *totalCandidatos, Eleitor eleitores[], int *totalEleitores, EstadoUrna *fase_ptr, int *votosNulos, int *votosBrancos) { //ALTERADO: Parâmetros
    int opcao;
    TipoUsuario tipo_logado;
    Eleitor* eleitor_logado = NULL;

    do {
        limparTelaInt();

        cabecalho("SISTEMA DE VOTACAO");
        printf("\n");

        printf("\t1 - Login\n");
        printf("\t2 - Cadastrar-se\n");
        printf("\t0 - Sair\n");
        printf("\n");
    
        printf("Escolha uma das opcoes acima: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                tipo_logado = menuLogin(eleitores, *totalEleitores, &eleitor_logado);

                if (tipo_logado == TIPO_ADMIN) {
                    // Passei todos os parâmetros para menuAdmin
                    menuAdmin(candidatos, totalCandidatos, eleitores, totalEleitores, fase_ptr, votosNulos, votosBrancos);
                } else if (tipo_logado == TIPO_ELEITOR) {
                    // Passei todos os parâmetros para menuEleitor
                    menuEleitor(candidatos, *totalCandidatos, eleitor_logado, votosNulos, votosBrancos, fase_ptr);
                }
                break;
            }
            case 2: 
                menuCadastro(eleitores, totalEleitores, fase_ptr);
                break;
            case 0: // Não lembro com faz para voltar para a main, acho que se deixar sem nada aqui, ele volta pra main
                break;
            default:
                printf("\nOpcao Invalida!\n");
                printf("\nExistem apenas aquelas 3 opcoes!\n");
                break;
        }
    } while (opcao != 0);
}

void menuCadastro(Eleitor listaDeEleitores[], int* totalEleitores, EstadoUrna* fase_ptr) {
    limparTelaInt();
     if (*fase_ptr == FASE_CADASTRO) {
        cabecalho("CADASTRO DE ELEITOR");

        cadastroEleitor(listaDeEleitores, totalEleitores, fase_ptr);
        registrarLog("Novo eleitor cadastrado no sistema!");
        pausarTelaInt();
    } else {
        cabecalho("Fase de cadastro encerrada!");
        pausarTelaInt();
    }
}

void menuEleitor(Candidato candidatos[], int totalC, Eleitor* usuario_logado, int *votosNulos, int *votosBrancos, EstadoUrna *fase_ptr) { // ALTERADO: Parâmetros
    int opcao;
    do {
        limparTelaInt();

        cabecalho("MENU DO ELEITOR");
        printf("\n");
        listaCandidatos(candidatos, totalC);
        printf("\n");

        printf("\t1 - Votar\n");
        printf("\t0 - Sair\n");
        printf("\n");

        printf("Escolha uma das opcoes acima: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: 
                // Chamar a função votar com os novos parâmetros
                votar(candidatos, totalC, usuario_logado, votosNulos, votosBrancos, fase_ptr); // Implementar o menu de voto e chamar a função votar nele
                break;                                                              // ALTERADO: Chamada e parâmetros
            case 0: 
                break;
            default: 
                printf("Opcao invalida!");
                pausarTelaInt();
                break;
        }
    } while (opcao != 0);
}

void menuAdmin(Candidato candidatos[], int *totalCandidatos, Eleitor eleitores[], int *totalEleitores, EstadoUrna *fase_ptr, int *votosNulos, int *votosBrancos) { //ALTERADO: Parâmetros
    int opcao;


    do {
        limparTelaInt();
    
        cabecalho("MENU DO ADMINISTRADOR");
        printf("\n");

        printf("\t1 - Criar Urna\n"); 
        printf("\t2 - Gerenciar fases da votacaoo\n"); 
        printf("\t3 - Gerenciar Candidatos\n");
        printf("\t4 - Resultados\n");
        printf("\t5 - Log - Relatorio\n");
        printf("\t6 - Salvar Dados (Estado Atual da Urna)\n");
        printf("\t7 - Carregar Dados (Estado de Urna Salva)\n");
        printf("\t0 - Sair\n");
        printf("\n");

        printf("Escolha uma das opcoes acima: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: // Chamar a função criarUrna
                criarUrna(candidatos, totalCandidatos, eleitores, totalEleitores, votosNulos, votosBrancos, fase_ptr);
                break;
            case 2:// Chamar a função gerenciarFase
                gerenciarFase(fase_ptr);
                break;
            case 3:
                menuCandidatos(candidatos, totalCandidatos);
                break;
            case 4:// Passa os votos nulos/brancos para resultados
                resultados(candidatos, *totalCandidatos, *votosNulos, *votosBrancos, fase_ptr);
                break;
            case 5:// Passa os votos nulos/brancos para relatorio (se for usar lá)
                relatorio(candidatos, *totalCandidatos, *votosNulos, *votosBrancos);
                break;
            case 6: //Salva os dados manualmente
                salvarDados(candidatos, *totalCandidatos, eleitores, *totalEleitores, fase_ptr, *votosNulos, *votosBrancos); // <--- NOVO: Chamada
                break;
            case 7: //Carregar os dados manualmente
                carregarDados(candidatos, totalCandidatos, eleitores, totalEleitores, votosNulos, votosBrancos, fase_ptr); // <--- NOVO: Chamada
                break;
            case 0:
                return;
                break;
            default:
                printf("\nOpcao invalida!\n");
                break;
        }
    } while (opcao != 0);
}

void menuCandidatos(Candidato listaDeCandidatos[], int *totalCandidatos) {
    int opcao;
    do {
        limparTelaInt();
        
        cabecalho("GERENCIAR CANDIDATOS");
        printf("\n");

        listaCandidatos(listaDeCandidatos, *totalCandidatos);
        

        printf("1 - Criar novo candidato.\n");
        printf("2 - Excluir candidato.\n");
        printf("0 - Voltar\n");

        printf("\n");
        printf("Escolha uma das opções acima: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: 
                criarCandidato(listaDeCandidatos, totalCandidatos);
                break;
            case 2:
                excluirCandidato(listaDeCandidatos, totalCandidatos);
                break;
            case 0:
                break;
            default: 
                printf("\nOpcao Invalida!\n");
                break;
        }
    } while (opcao != 0);
}

TipoUsuario menuLogin(Eleitor listaDeEleitores[], int totalEleitores, Eleitor **eleitorLogado) {
    char identificador[50];
    
    limparTelaInt();
    cabecalho("LOGIN NO SISTEMA");
    printf("\nDigite seu CPF (apenas numeros): ");
    scanf("%49s", &identificador);

    // Verificação para caso seja admin
    if (strcmp(identificador, ADMIN_USER) == 0) {
        char senha_digitada[50];
        printf("Digite a senha: ");
        scanf("%49s", senha_digitada);

        if (strcmp(senha_digitada, ADMIN_PASS) == 0) {
            printf("\nLogado com sucesso!\n");
            registrarLog("LOGIN: Administrador fez login.");
            pausarTelaInt();
            return TIPO_ADMIN;
        } else {
            printf("\nERRO: Senha de administrador incorreta.\n");
            registrarLog("FALHA DE LOGIN: Tentativa de login de admin com senha incorreta.");
            pausarTelaInt();
            return TIPO_INVALIDO;
        }
    }

    FILE *f = fopen(ARQUIVO_ELEITORES_TXT, "r");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo de eleitores cadastrados.\n");
        registrarLog("ERRO: Falha ao abrir o arquivo de eleitores");
        pausarTelaInt();
        return TIPO_INVALIDO; 
    }

    char linha[256];
    int encontrado = 0;
    char nomeEleitor[45];

    while (fgets(linha, sizeof(linha), f) != NULL) {
        char linhaCopia[256];
        strcpy(linhaCopia, linha);

        char* nome = strtok(linhaCopia, "|");
        char* cpf = strtok(NULL, "|");

        if (cpf != NULL) {
            cpf[strcspn(cpf, "\n")] = 0;
            cpf[strcspn(cpf, "\r")] = 0;
        }
        
        if (cpf != NULL && strcmp(identificador, cpf) == 0) {
            if (nome != NULL) {
                strcpy(nomeEleitor, nome);
            }
            encontrado = 1;
            break;
        }
    }
    fclose(f);

    if (encontrado) {
        for (int i = 0; i < totalEleitores; i++) {
            if (strcmp(identificador, listaDeEleitores[i].cpf) == 0) {
                *eleitorLogado = &listaDeEleitores[i];
                
                printf("\nLogin de eleitor bem-sucedido! Bem-vindo(a), %s.\n", nomeEleitor);
                registrarLog("LOGIN: Eleitor fez login.");
                pausarTelaInt();
                return TIPO_ELEITOR;
            }
        }
        printf("\nERRO: Inconsistencia de dados. Eleitor existe no arquivo mas nao esta carregado no sistema.\n");
        registrarLog("FALHA DE LOGIN: Inconsistencia de dados entre arquivo e memoria.");
        pausarTelaInt();
        return TIPO_INVALIDO;
    }

    printf("\nERRO: Identificador (CPF ou admin) nao encontrado.\n");
    registrarLog("FALHA DE LOGIN: Identificador nao encontrado.");
    pausarTelaInt();
    return TIPO_INVALIDO;
}