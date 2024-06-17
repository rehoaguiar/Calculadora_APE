#include <stdio.h>
#include <string.h>
#include "calculadora.h"

int main() {
  char expr[MAX_EXPR_LEN];
  char prefixExpr[MAX_EXPR_LEN];
  printf("Digite a expressão pós-fixada: ");
  fgets(expr, MAX_EXPR_LEN, stdin);
  expr[strcspn(expr, "\n")] = 0;

  char postfixExpr[MAX_EXPR_LEN];
  strcpy(postfixExpr, expr);
  double resultado = avaliarPosfixa(expr);

  posfixaParaPreFixa(postfixExpr, prefixExpr);

  printf("Resultado da avaliação: %.2f\n", resultado);
  printf("Expressão em notação pré-fixada: %s\n", prefixExpr);

  char infixExpr[MAX_EXPR_LEN];
  posfixaParaInfixa(postfixExpr, infixExpr);
  printf("Expressão em notação infixa: %s\n", infixExpr);

  return 0;
}
