/**
 * @file utils.h
 * @brief Funções de utilidades
 * 
 * Este módulo fornece funções de utilidades, provavelmente
 * pra economizar linhas de código.
 */
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else 
#include <unistd.h>
#endif

/**
 * @brief Cabecalho pré-definido
 * 
 * Está função desenha um cabeçalho simples e padronizado para
 * todo o sistema.
 * 
 * @param texto O texto que será usado como título
 */
void cabecalho(const char* texto);

/**
 * @brief Limpa a tela do terminal
 * 
 * Está função verifica se a macro definida é _WIN32, caso seja,
 * então ele inclui a linha "system("cls"); e descarta as linhas
 * dentro do "#else". Se a macro não for _WIN32, obviamente inclui
 * as linhas do "#else".
 */
void limparTela();

/**
 * @brief Pausa a tela por algum tempo pré-determinado
 * 
 * Está função tem a mesma verificação do função "limparTela()" e pausa
 * a tela por um tempo determinado pelo parâmetro "tempo".
 * 
 * @param tempo O tempo em milissegundos que tela ficará pausada.
 */
void pausarTela(int tempo);

/**
 * @brief Pausa a tela e espera o usuário teclar enter
 * 
 * Está função apenas mostra uma mensagem para o usuário e aguarda
 * ele teclar enter.
 */
void pausarTelaInt();

#endif