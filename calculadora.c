#include "calculadora.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void adicionar(ArmazenarNumeros *armazenarNumeros, double valor) {
  if (armazenarNumeros->topo < MAX_PILHA_TAM) {
    armazenarNumeros->num[++(armazenarNumeros->topo)] = valor;
  }
}

double remover(ArmazenarNumeros *armazenarNumeros) {
  if (armazenarNumeros->topo >= 0) {
    return armazenarNumeros->num[(armazenarNumeros->topo)--];
  }
  return 0;
}

void adicionarString(ArmazenarStrings *armazenarStrings, char *valor) {
  if (armazenarStrings->topo < MAX_PILHA_TAM) {
    armazenarStrings->strings[++(armazenarStrings->topo)] = valor;
  }
}

char *removerString(ArmazenarStrings *armazenarStrings) {
  if (armazenarStrings->topo >= 0) {
    return armazenarStrings->strings[(armazenarStrings->topo)--];
  }
  return NULL;
}

double soma(double a, double b) { return a + b; }
double subtracao(double a, double b) { return a - b; }
double multiplicacao(double a, double b) { return a * b; }
double divisao(double a, double b) { return a / b; }
double potencia(double a, double b) { return pow(a, b); }
double raiz(double a, double b) { return sqrt(a); }
double seno(double a) { return sin(DEG_TO_RAD(a)); }
double cosseno(double a) { return cos(DEG_TO_RAD(a)); }
double tangente(double a) { return tan(DEG_TO_RAD(a)); }
double logaritmo(double a) { return log10(a); }

double avaliarPosfixa(char *expr) {
  ArmazenarNumeros armazenarNumeros = {.topo = -1};
  char *token = strtok(expr, " ");
  while (token != NULL) {
    if (strcmp(token, "+") == 0) {
      double b = remover(&armazenarNumeros);
      double a = remover(&armazenarNumeros);
      adicionar(&armazenarNumeros, soma(a, b));
    } else if (strcmp(token, "-") == 0) {
      double b = remover(&armazenarNumeros);
      double a = remover(&armazenarNumeros);
      adicionar(&armazenarNumeros, subtracao(a, b));
    } else if (strcmp(token, "*") == 0) {
      double b = remover(&armazenarNumeros);
      double a = remover(&armazenarNumeros);
      adicionar(&armazenarNumeros, multiplicacao(a, b));
    } else if (strcmp(token, "/") == 0) {
      double b = remover(&armazenarNumeros);
      double a = remover(&armazenarNumeros);
      adicionar(&armazenarNumeros, divisao(a, b));
    } else if (strcmp(token, "^") == 0) {
      double b = remover(&armazenarNumeros);
      double a = remover(&armazenarNumeros);
      adicionar(&armazenarNumeros, potencia(a, b));
    } else if (strcmp(token, "raiz") == 0) {
      double a = remover(&armazenarNumeros);
      adicionar(&armazenarNumeros, raiz(a, 0));
    } else if (strcmp(token, "sen") == 0) {
      double a = remover(&armazenarNumeros);
      adicionar(&armazenarNumeros, seno(a));
    } else if (strcmp(token, "cos") == 0) {
      double a = remover(&armazenarNumeros);
      adicionar(&armazenarNumeros, cosseno(a));
    } else if (strcmp(token, "tg") == 0) {
      double a = remover(&armazenarNumeros);
      adicionar(&armazenarNumeros, tangente(a));
    } else if (strcmp(token, "log") == 0) {
      double a = remover(&armazenarNumeros);
      adicionar(&armazenarNumeros, logaritmo(a));
    } else {
      adicionar(&armazenarNumeros, atof(token));
    }
    token = strtok(NULL, " ");
  }
  return remover(&armazenarNumeros);
}

void posfixaParaPreFixa(char *expr, char *resultado) {
    ArmazenarStrings pilha = {.topo = -1};
    char *token = strtok(expr, " ");

    while (token != NULL) {
        if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
            strcmp(token, "*") == 0 || strcmp(token, "/") == 0 ||
            strcmp(token, "^") == 0 || strcmp(token, "raiz") == 0 ||
            strcmp(token, "sen") == 0 || strcmp(token, "cos") == 0 ||
            strcmp(token, "tg") == 0 || strcmp(token, "log") == 0) {

            char operando2[MAX_EXPR_LEN], operando1[MAX_EXPR_LEN], temp[MAX_EXPR_LEN];

            if (strcmp(token, "raiz") == 0 || strcmp(token, "sen") == 0 ||
                strcmp(token, "cos") == 0 || strcmp(token, "tg") == 0 ||
                strcmp(token, "log") == 0) {

                strcpy(operando1, removerString(&pilha));
                sprintf(temp, "%s(%s)", token, operando1);
            } else {
                strcpy(operando2, removerString(&pilha));
                strcpy(operando1, removerString(&pilha));
                sprintf(temp, "%s %s %s", token, operando1, operando2);
            }

            adicionarString(&pilha, strdup(temp));
        } else {
            adicionarString(&pilha, strdup(token));
        }

        token = strtok(NULL, " ");
    }

    strcpy(resultado, removerString(&pilha));
}


/* void posfixaParaInfixa(char *expr, char *resultado) {
    ArmazenarStrings pilha = {.topo = -1};
    char *token = strtok(expr, " ");

    while (token != NULL) {
        if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
            strcmp(token, "*") == 0 || strcmp(token, "/") == 0 ||
            strcmp(token, "^") == 0 || strcmp(token, "raiz") == 0 ||
            strcmp(token, "sen") == 0 || strcmp(token, "cos") == 0 ||
            strcmp(token, "tg") == 0 || strcmp(token, "log") == 0) {

            char operando2[MAX_EXPR_LEN], operando1[MAX_EXPR_LEN],
temp[MAX_EXPR_LEN];

            if (strcmp(token, "raiz") == 0 || strcmp(token, "sen") == 0 ||
                strcmp(token, "cos") == 0 || strcmp(token, "tg") == 0 ||
                strcmp(token, "log") == 0) {

                strcpy(operando1, removerString(&pilha));
                sprintf(temp, "%s(%s)", token, operando1);
            } else {
                strcpy(operando2, removerString(&pilha));
                strcpy(operando1, removerString(&pilha));
                sprintf(temp, "(%s %s %s)", operando1, token, operando2);
            }

            adicionarString(&pilha, strdup(temp));
        } else {
            adicionarString(&pilha, strdup(token));
        }

        token = strtok(NULL, " ");
    }

    strcpy(resultado, removerString(&pilha));
} */

float getValor(char *Str) {
  char expr[MAX_EXPR_LEN];
  strcpy(expr, Str);
  return (float)avaliarPosfixa(expr);
}
