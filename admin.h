/**
 * @file admin.
 * @brief Funções das opções do admin.
 * 
 * Neste Módulo contém a lógica das opções do administrador do sistema
 * apresentadas no menu do administrador na biblioteca "menu.h".
 */
#ifndef ADMIN_H
#define ADMIN_H

#include <string.h>

#include "utils.h"
#include "dados.h"

/**
 * @brief Função para cadastrar os candidatos no sistema.
 * 
 * Armazena o novo candidato cadastrado na estrutura de candidatos.
 * @param candidato Estrutura que armazenas os candidatos.
 * @note Existe um máximo de candidatos que podem ser cadastrados, no final da votação os candidatos serão apagados.
 */
void criarCandidato(Candidato candidatos[], int *totalCandidatos);

/**
 * @brief Exibe uma lista de candidatos que já estão cadastrados no sistema.
 */
void listaCandidatos(Candidato candidatos[]);

/**
 * @brief Função para excluir um candidato do sistema.
 * 
 * É buscado na estrutura de candidatos o que o admin deseja excluir e remove do sistema.
 */
void excluirCandidato(Candidato candidatos[], int *totalCandidatos);

/**
 * @brief Disponibiliza a leitura dos resultados da votação.
 * 
 * Abre o arquivo na qual o relatório foi escrito para leitura e mostra na tela,
 * disponível apenas para o admin.
 */
void resultados(Candidato candidatos[], int totalCandidatos, int votosNulos, int votosBrancos);

void relatorio(Candidato candidatos[], int totalCandidatos, int votosNulos, int votosBrancos);

void criarUrna();

#endif
