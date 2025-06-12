/**
 * @file menu.h
 * @brief Funções dos menus interativos
 * 
 * Este módulo fornece os menus que serão utilizados no sistema.
 * Deve ser usado para armazenar apenas os menus, não deve ter a lógica do sistema aqui.
 */
#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "dados.h"
#include "admin.h"
#include "eleitor.h"

/**
 * @brief Menu de login que representará a primeira tela do sistema
 * 
 */
TipoUsuario menuLogin(Eleitor listaDeEleitores[], int totalEleitores, Eleitor **eleitorLogado);

/**
 * @brief Menu de Cadastro 
 */
void menuCadastro();

void menuInicial(Candidato candidatos[], int* totalCandidatos, Eleitor eleitores[], int* totalEleitores, EstadoUrna *fase);

void menuAdmin(Candidato candidatos[], int* totalCandidatos, Eleitor eleitores[], int* totalEleitores, EstadoUrna *fase);

void menuEleitor(Candidato candidatos[], int totalC, Eleitor* usuario_logado, EstadoUrna *fase);

void menuCandidatos(Candidato listaDeCandidatos[], int* totalCandidatos);


#endif