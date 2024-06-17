#include <stdio.h>
#include <string.h>
#include "calculadora.h"

#define MAX_EXPR_LEN 100

int main() {
    char expr[MAX_EXPR_LEN];       // Armazena a expressão pós-fixada
    char prefixExpr[MAX_EXPR_LEN]; // Armazena a expressão convertida para pré-fixa
    char infixExpr[MAX_EXPR_LEN];  // Armazena a expressão convertida para infixa

    printf("Digite a expressão pós-fixada: ");
    fgets(expr, MAX_EXPR_LEN, stdin); // Lê a expressão do usuário
    expr[strcspn(expr, "\n")] = 0;    // Remove o caractere de nova linha

    char postfixExpr[MAX_EXPR_LEN];
    strcpy(postfixExpr, expr);        // Faz uma cópia da expressão para avaliação
    double resultado = avaliarPosfixa(postfixExpr); // Avalia a expressão pós-fixada

    // Faz a conversão de novo pois strtok modifica a string original
    strcpy(postfixExpr, expr);
    posfixaParaPreFixa(postfixExpr, prefixExpr); // Converte para pré-fixa

    strcpy(postfixExpr, expr); // Restaura expressão pós-fixada original
    posfixaParaInfixa(postfixExpr, infixExpr); // Converte para infixa

    // Exibe os resultados
    printf("Resultado da avaliação: %.2f\n", resultado);
    printf("Expressão em notação pré-fixada: %s\n", prefixExpr);
    printf("Expressão em notação infixada: %s\n", infixExpr);

    return 0;
}
