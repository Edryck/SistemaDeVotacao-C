/**
 * @file votacao.h.
 * @brief Funções das opções do eleitor
 * 
 * Este módulo fornece as funções de validação, cadastro e de voto do eleitor.
 */
#ifndef VOTACAO_GERENCIAMENTO_H
#define VOTACAO_GERENCIAMENTO_H

#include "dados.h"
#include "utils.h"
#include <stdio.h>


#define ARQUIVO_CANDIDATOS_TXT "candidatos.txt"
#define ARQUIVO_ELEITORES_TXT "eleitores.txt"
#define ARQUIVO_ESTADO_VOTACAO_TXT "estado_votacao.txt"
#define ARQUIVO_RELATORIO_FINAL "relatorio.txt"

// Declaração da variável global 'fase' para que outros arquivos possam acessá-la
extern EstadoUrna fase;

/**
 * @brief Carrega todos os dados da votação (candidatos, eleitores, fase, votos nulos/brancos) dos arquivos de texto.
 * @param candidatos Array de structs Candidato a ser preenchido.
 * @param totalCandidatos Ponteiro para o contador de candidatos.
 * @param eleitores Array de structs Eleitor a ser preenchido.
 * @param totalEleitores Ponteiro para o contador de eleitores.
 * @param votosNulos Ponteiro para o contador de votos nulos.
 * @param votosBrancos Ponteiro para o contador de votos brancos.
 */
void carregarDados(Candidato candidatos[], int *totalCandidatos,
                   Eleitor eleitores[], int *totalEleitores,
                   int *votosNulos, int *votosBrancos, EstadoUrna *fase_ptr);

/**
 * @brief Salva todos os dados da votação (candidatos, eleitores, fase, votos nulos/brancos) nos arquivos de texto.
 * @param candidatos Array de structs Candidato a ser salvo.
 * @param totalCandidatos Número total de candidatos.
 * @param eleitores Array de structs Eleitor a ser salvo.
 * @param totalEleitores Número total de eleitores.
 * @param fase_atual Fase atual da urna.
 * @param votosNulos Contador de votos nulos.
 * @param votosBrancos Contador de votos brancos.
 */
void salvarDados(Candidato candidatos[], int totalCandidatos,
                 Eleitor eleitores[], int totalEleitores,
                 EstadoUrna *fase_actual, int votosNulos, int votosBrancos);

/**
 * @brief Inicializa uma nova urna, limpando todos os dados de uma votação anterior.
 * Esta função redefine os contadores, apaga arquivos de dados e define a fase como FASE_CADASTRO.
 * @param candidatos Array de structs Candidato a ser limpo.
 * @param totalCandidatos Ponteiro para o contador de candidatos (será resetado para 0).
 * @param eleitores Array de structs Eleitor a ser limpo.
 * @param totalEleitores Ponteiro para o contador de eleitores (será resetado para 0).
 * @param votosNulos Ponteiro para o contador de votos nulos (será resetado para 0).
 * @param votosBrancos Ponteiro para o contador de votos brancos (será resetado para 0).
 */
void criarUrna(Candidato candidatos[], int *totalCandidatos,Eleitor eleitores[], int *totalEleitores, int *votosNulos, int *votosBrancos, EstadoUrna *fase_ptr);

/**
 * @brief Permite ao administrador gerenciar a fase atual da votação (cadastro, votação, apuração).
 * @param fase_ptr Ponteiro para a variável que armazena a fase atual da urna.
 */

 void gerenciarFase(EstadoUrna *fase_ptr);

#endif