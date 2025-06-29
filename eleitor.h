/**
 * @file eleitor.
 * @brief Funções das opções do eleitor
 * 
 * Este módulo fornece as funções de validação, cadastro e de voto do eleitor.
 */
#ifndef ELEITOR_H
#define ELEITOR_H

    #include <string.h>

    #include "dados.h"

    #include "votacao.h"

    #define tam 256


    /**
     * @brief Função para verificar se o eleitor já foi cadastrado
     * 
     * Esta função verifica se o eleitor já foi cadastrado percorrendo
     * um arquivo onde os dados dos eleitores já cadastrados estão
     * armazenados. 
     * 
     * @param cpf "Chave-primária" do eleitor, também o que será buscado
     * no arquivo.
     * 
     * @return Retorna 1 se o eleitor já foi cadastrado.
     * @return Retorna 0 se o eleitor não foi cadastrado.
     */
    int validarCpf (Eleitor eleitores[], int totalEleitores, const char* cpf);

    /**
     * @brief Função para cadastro de eleitores
     * 
     * Está função cadastra o eleitor no sistema 
     */
    void cadastroEleitor(Eleitor listaDeEleitores[], int *totalEleitores);
    
    /**
     * @brief Função de votar.
     * 
     * Está função realiza o voto do eleitor, ela realiza primeiramente se está na 
     * fase de votos, se estiver, ela verifica se usuário já voltou, caso não tenha
     * votado ela incrementa no contador de votos do candidato.
     * @param candidato Candidato que o eleitor escolheu votar.
     * @param eleitor Eleitor que está logado.
     */
    void votar(Candidato candidatos[], int totalCandidatos, Eleitor *eleitorLogado, int *votosNulos, int *votosBrancos); //ALTERADO: Prototipo
   

#endif