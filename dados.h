/**
 * @file dados.h
 * @brief Módulo das estruturas e enumerados
 * 
 * Neste módulo está localizado todas as estruturas (structs) e os
 * enumerados (enum).
 */
#ifndef DADOS_H
#define DADOS_H

#include "utils.h"

#define MAX_CANDIDATOS 5
#define MAX_ELEITORES 500
#define ADMIN_USER "admin"
#define ADMIN_PASS "senha123"
#define ARQUIVO_LOG "votacao.log"
#define ARQUIVO_ELEITORES_TXT "eleitores.txt"

// Enumerados

typedef enum {
    FASE_CADASTRO,
    FASE_VOTACAO,
    FASE_APURACAO
} EstadoUrna;

typedef enum {
    TIPO_INVALIDO, // Para login falho
    TIPO_ELEITOR,
    TIPO_ADMIN
} TipoUsuario;


// Estruturas

typedef struct {
    char nome[45];
    int numero;
    int votos; // Quantidade de votos
    int ativo;
} Candidato;

/**
 * @brief Estrutura de dados do eleitor
 * 
 * Estrutura básica dos dados requeridos para cadastrar o eleitor.
 * @param nome Nome do eleitor
 * @param cpf CPF do eleitor e o que vai garantir que não haverá o mesmo eleitor cadastrado
 * @param idade Idade do eleitor, para evitar que menores de idade possam votar
 * @param votou 0 para caso não tenha votado ainda e 1 para quando votou
 */
typedef struct {
    char nome[46];
    char cpf[12]; //
    int idade; // Garante que menores de idade não vote
    int votou; // 0 caso não tenha votado, 1 para quando já votou
} Eleitor;


#endif