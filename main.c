#include <stdio.h>
#include "menu.h"

// OBS.: Falta implementar funções para carregarDados e salvarDados para manter integridade de dados do sistema
// Na função criarCandidato tem que adicionar a parte de salvar no arquivo (não lembro se coloquei, mas talvez não
// precise, pq para cada nova votação a única coisa que deve ficar armazenada seria o relatório da votação, o
// resto vira armazenamento livre)
// O Admin que decide quando começa a fase de votos, então adicionar essa opção no menu do admin em menu.c
// Tem que revisar, ver se o registro de log tá para todas as cenas possiveis, depois mim fazer isso (Edryck)
// Falta a criptografia tbm, não sei onde eu coloco ela, talvez para salvar os dados dos eleitores
// Realizar os testes
// Será que alguém lê isso?

int main() {
    registrarLog("========== SISTEMA INICIADO ==========");
    registrarLog("=====   FASE ATUAL: CADASTROS    =====");

    EstadoUrna fase = FASE_CADASTRO; // Inicialmente o programa inicializa na fase de cadastros
    

    Candidato listaDeCandidatos[MAX_CANDIDATOS];
    Eleitor listaDeEleitores[MAX_ELEITORES];
    int totalCandidatos = 0;
    int totalEleitores = 0;

    // Para integridade de dados, é necessário fazer uma função carrefarDados. Tem que ficar aqui
    
    TipoUsuario tipoUsuarioLogado;
    Eleitor *eleitorLogado = NULL;

    
    tipoUsuarioLogado = menuLogin(listaDeEleitores, totalEleitores, &eleitorLogado);
    
    // Se tem um carregarDados, obviamente precisa de uma salvarDados. Na teoria ele tem que ficar aqui
    
    registrarLog("========= SISTEMA FINALIZADO =========");
    return 0;
} // Fim do código, imagina tudo isso na main