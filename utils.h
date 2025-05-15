#ifndef UTILS_H
#define UTILS_H

// Cabeçalhos

/**
 * @brief Cria uma quebra de linha no terminal.
 */
void quebrarLinha();

/**
 * @brief Limpa a tela do terminal.
 */
void limparTela();

/**
 * @brief Pausa a tela até que o usuário pressione Enter.
 */
void pausarTela();

/**
 * @brief Imprime uma linha horizontal com o caractere especificado.
 * @param caractere Caractere a ser repetido.
 */
void desenharLinhaHorizotal(char caractere);

/**
 * @brief Centraliza e exibe um texto no terminal.
 * @param texto Ponteiro para string a ser exibida.
 */
void mostrarTextoCentralizado(const char *texto);

#endif