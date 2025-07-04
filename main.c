#include <stdio.h>
#include "menu.h"
#include "votacao.h"

int main() {
    registrarLog("========== SISTEMA INICIADO ==========");
    registrarLog("=====   FASE ATUAL: CADASTROS    =====");

    EstadoUrna fase = FASE_CADASTRO; 
    
    Candidato listaDeCandidatos[MAX_CANDIDATOS];
    Eleitor listaDeEleitores[MAX_ELEITORES];
    int totalCandidatos = 0;
    int totalEleitores = 0;
    int votosNulos = 0;
    int votosBrancos = 0;

    TipoUsuario tipoUsuarioLogado;
    Eleitor *eleitorLogado = NULL;
    
    menuInicial(listaDeCandidatos, &totalCandidatos,listaDeEleitores, &totalEleitores,&fase, &votosNulos, &votosBrancos);

    // Salvar dados ao finalizar o programa
    salvarDados(listaDeCandidatos, totalCandidatos,listaDeEleitores, totalEleitores, &fase, votosNulos, votosBrancos);
 
    registrarLog("========= SISTEMA FINALIZADO =========");
    return 0;
} 