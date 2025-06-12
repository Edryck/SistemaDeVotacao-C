#include "menu.h"

#define tam 256
#define ADMIN_USER "admin"
#define ADMIN_PASS "senha123"

void menuInicial(Candidato candidatos[], int *totalCandidatos, Eleitor eleitores[], int *totalEleitores, EstadoUrna *fase) {
    int opcao;
    do {
        limparTela();
        
        cabecalho("SISTEMA DE VOTACAO");
        printf("\n");

        printf("\t1 - Login\n");
        printf("\t2 - Cadastrar-se\n");
        printf("\t0 - Sair\n");
        printf("\n");
    
        printf("Escolha uma das opcoes acima: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: 
                TipoUsuario tipo_logado;
                Eleitor* eleitor_logado = NULL;

                tipo_logado = menuLogin(eleitores, *totalEleitores, &eleitor_logado);

                if (tipo_logado == TIPO_ADMIN) {
                    menuAdmin(candidatos, totalCandidatos, eleitores, totalEleitores, fase);
                } else if (tipo_logado == TIPO_ELEITOR) {
                    menuEleitor(candidatos, *totalCandidatos, eleitor_logado, fase);
                }
                break;
            case 2: 
                menuCadastro(eleitores, totalEleitores, fase);
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

void menuCadastro(Eleitor listaDeEleitores[], int* totalEleitores, EstadoUrna* fase) {
    limparTela();
    if (fase == FASE_CADASTRO) {
        Eleitor eleitor;

        cabecalho("CADASTRO DE ELEITOR");
        
        criarEleitor(listaDeEleitores, totalEleitores);
        
        printf("\nEleitor cadastrado com sucesso!\n\n");
        printf("Nome: %s\n", eleitor.nome);
        printf("CPF: %s\n", eleitor.cpf);
        printf("Idade: %d\n", eleitor.idade);

        registrarLog("Novo eleitor cadastrado no sistema!");

        pausarTelaInt();
    } else {
        cabecalho("Fase de cadastro encerrada!");
        pausarTelaInt();
    }
}

void menuEleitor(Candidato candidatos[], int totalC, Eleitor* usuario_logado, EstadoUrna *fase) {
    int opcao;
    do {
        limparTela();

        cabecalho("MENU DO ELEITOR");
        printf("\n");
        listaCandidatos(candidatos);
        printf("\n");

        printf("\t1 - Votar\n");
        printf("\t0 - Sair\n");
        printf("\n");

        printf("Escolha uma das opcoes acima: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: 
                menuVotar(); // Implementar o menu de voto e chamar a função votar nele
                break;
            case 0: 
                break;
            default: 
                printf("Opcao invalida!");
                pausarTelaInt();
                break;
        }
    } while (opcao != 0);
}

void menuAdmin(Candidato candidatos[], int *totalCandidatos, Eleitor eleitores[], int *totalEleitores, EstadoUrna* fase) {
    int opcao;

    int votosNulos = 0;
    int votosBrancos = 0;

    do {
        limparTela();
    
        cabecalho("MENU DO ADMINISTRADOR");
        printf("\n");

        printf("\t1 - Criar Urna\n");
        printf("\t2 - Gerenciar fases da votação\n");
        printf("\t3 - Gerenciar Candidatos\n");
        printf("\t4 - Resultados\n");
        printf("\t5 - Log\n");
        printf("\t0 - Sair\n");
        printf("\n");

        printf("Escolha uma das opcoes acima: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: // Fazer a função para criar urna
            case 2: // Fazer uma função para gerenciar fases
            case 3:
                menuCandidatos(candidatos, totalCandidatos);
                break;
            case 4:
                resultados(candidatos, totalCandidatos, votosNulos, votosBrancos);
                break;
            case 5:
                relatório(candidatos, totalCandidatos, votosNulos, votosBrancos);
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

void menuCandidatos(Candidato listaDeCandidatos[], int* totalCandidatos) {
    int opcao;
    do {
        limparTela();
        
        cabecalho("GERENCIAR CANDIDATOS");
        printf("\n");

        listaCandidatos(listaDeCandidatos);
        printf("\n");

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
    
    limparTela();
    cabecalho("LOGIN NO SISTEMA");
    printf("\nDigite seu CPF (apenas numeros): ");
    scanf("%11s", identificador);

    // Verificação para caso seja admin
    if (strcmp(identificador, ADMIN_USER) == 0) {
        char senha_digitada[50];
        printf("Digite a senha: ");
        scanf("%49s", senha_digitada);

        if (strcmp(senha_digitada, ADMIN_PASS) == 0) {
            printf("\nLogado com sucesso!\n");
            registrarLog("LOGIN: Administrador fez login.");
            pausarTela_ms(1500);
            return TIPO_ADMIN;
        } else {
            printf("\nERRO: Senha de administrador incorreta.\n");
            registrarLog("FALHA DE LOGIN: Tentativa de login de admin com senha incorreta.");
            pausarTela_ms(1500);
            return TIPO_INVALIDO;
        }
    }

    // Verificação para caso seja eleitor
    for (int i = 0; i < totalEleitores; i++) {
        if (strcmp(identificador, listaDeEleitores[i].cpf) == 0) {
            printf("\nLogin de eleitor bem-sucedido! Bem-vindo(a), %s.\n", listaDeEleitores[i].nome);
            registrarLog("LOGIN: Eleitor fez login.");
            pausarTela_ms(1500);
            
            // Atualiza o pnteiro de saida para apontar para o eleitor encontrado
            *eleitorLogado = &listaDeEleitores[i];
            
            return TIPO_ELEITOR;
        }
    }

    // Se falhar ao buscar o cpf
    printf("\nERRO: Identificador (CPF ou admin) nao encontrado.\n");
    registrarLog("FALHA DE LOGIN: Identificador nao encontrado.");
    pausarTela_ms(1500);
    return TIPO_INVALIDO;
}