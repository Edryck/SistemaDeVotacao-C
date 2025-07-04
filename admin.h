/**
 * @file admin.
 * @brief Funções das opções do admin.
 * 
 * Neste Módulo contém a lógica das opções do administrador do sistema
 * apresentadas no menu do administrador na biblioteca "menu.h".
 */
#ifndef ADMIN_H
#define ADMIN_H
#include "votacao.h"

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
void listaCandidatos(Candidato candidatos[], int quantCandidatos);

/**
 * @brief Função para excluir (logicamente) um candidato do sistema.
 *
 * Solicita o número do candidato ao administrador, busca-o na estrutura
 * e, se encontrado e ativo, o marca como inativo (exclusão lógica),
 * impedindo que ele receba mais votos ou apareça em listagens ativas.
 * @param candidatos Array de structs Candidato onde o candidato será buscado e modificado.
 * @param totalCandidatos Ponteiro para o contador de candidatos (não é decrementado,
 * apenas o status 'ativo' é alterado).
 */
void excluirCandidato(Candidato candidatos[], int *totalCandidatos); 

/**
 * @brief Verifica se um número de candidato já existe entre os candidatos ativos.
 *
 * Utilizada para garantir a unicidade dos números de votação durante o cadastro de candidatos.
 * @param candidatos Array de structs Candidato a ser pesquisado.
 * @param totalCandidatos Número total de candidatos no array.
 * @param numero O número a ser verificado.
 * @return Retorna 1 se o número já existe e o candidato está ativo, 0 caso contrário.
 */
int numeroExiste(Candidato candidatos[], int totalCandidatos, int numero); 

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

/**
 * @brief Exibe o log de atividades do sistema.
 *
 * Abre o arquivo de log ("votacao.log") em modo de leitura e imprime todo
 * o seu conteúdo na tela, permitindo ao administrador revisar os eventos.
 * @param candidatos Array de structs Candidato (não utilizado nesta função, mantido para consistência de interface se necessário).
 * @param totalCandidatos Número total de candidatos (não utilizado nesta função).
 * @param votosNulos Quantidade de votos nulos (não utilizado nesta função).
 * @param votosBrancos Quantidade de votos em branco (não utilizado nesta função).
 */
void relatorio(Candidato candidatos[], int totalCandidatos, int votosNulos, int votosBrancos); 

void gerenciarFase(EstadoUrna *fase_ptr);

#endif