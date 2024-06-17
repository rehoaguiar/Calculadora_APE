#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calculadora.h"

#define DEG_TO_RAD(deg) ((deg) * M_PI / 180.0) // Converte graus para radianos

// Função para adicionar um valor na pilha de números
void adicionar(ArmazenarNumeros* armazenarNumeros, double valor) {
    if (armazenarNumeros->topo < MAX_PILHA_TAM - 1) {
        armazenarNumeros->num[++(armazenarNumeros->topo)] = valor;
    }
}

// Função para remover um valor da pilha de números
double remover(ArmazenarNumeros* armazenarNumeros) {
    if (armazenarNumeros->topo >= 0) {
        return armazenarNumeros->num[(armazenarNumeros->topo)--];
    }
    return 0;
}

// Função para adicionar uma string na pilha de strings
void adicionarString(ArmazenarStrings* armazenarStrings, char* valor) {
    if (armazenarStrings->topo < MAX_PILHA_TAM - 1) {
        armazenarStrings->strings[++(armazenarStrings->topo)] = valor;
    }
}

// Função para remover uma string da pilha de strings
char* removerString(ArmazenarStrings* armazenarStrings) {
    if (armazenarStrings->topo >= 0) {
        return armazenarStrings->strings[(armazenarStrings->topo)--];
    }
    return NULL;
}

// Funções matemáticas básicas
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

// Função para avaliar uma expressão pós-fixada
double avaliarPosfixa(char* expr) {
    ArmazenarNumeros armazenarNumeros = {.topo = -1}; // Inicializa a pilha
    char* token = strtok(expr, " "); // Separa a expressão em tokens
    while (token != NULL) {
        // Verifica o operador e executa a operação correspondente
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
            adicionar(&armazenarNumeros, atof(token)); // Converte e adiciona o número na pilha
        }
        token = strtok(NULL, " "); // Próximo token
    }
    return remover(&armazenarNumeros); // Retorna o resultado final
}

// Função para converter expressão pós-fixada para pré-fixa
void posfixaParaPreFixa(char* expr, char* resultado) {
    ArmazenarStrings armazenarStrings = {.topo = -1}; // Inicializa a pilha
    char* token = strtok(expr, " "); // Separa a expressão em tokens
    while (token != NULL) {
        // Verifica o operador e monta a expressão correspondente
        if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
            strcmp(token, "*") == 0 || strcmp(token, "/") == 0 ||
            strcmp(token, "^") == 0 || strcmp(token, "raiz") == 0 ||
            strcmp(token, "sen") == 0 || strcmp(token, "cos") == 0 ||
            strcmp(token, "tg") == 0 || strcmp(token, "log") == 0) {
            char b[100], a[100], temp[100];
            if (strcmp(token, "raiz") == 0 || strcmp(token, "sen") == 0 ||
                strcmp(token, "cos") == 0 || strcmp(token, "tg") == 0 ||
                strcmp(token, "log") == 0) {
                strcpy(a, removerString(&armazenarStrings));
                sprintf(temp, "%s %s", token, a);
            } else {
                strcpy(b, removerString(&armazenarStrings));
                strcpy(a, removerString(&armazenarStrings));
                sprintf(temp, "%s %s %s", token, a, b);
            }
            adicionarString(&armazenarStrings, strdup(temp));
        } else {
            adicionarString(&armazenarStrings, strdup(token));
        }
        token = strtok(NULL, " "); // Próximo token
    }
    strcpy(resultado, removerString(&armazenarStrings)); // Copia o resultado para a string de saída
}

// Função para converter expressão pós-fixada para infixa
void posfixaParaInfixa(char* expr, char* resultado) {
    ArmazenarStrings armazenarStrings = {.topo = -1}; // Inicializa a pilha
    char* token = strtok(expr, " "); // Separa a expressão em tokens
    while (token != NULL) {
        // Verifica o operador e monta a expressão correspondente
        if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
            strcmp(token, "*") == 0 || strcmp(token, "/") == 0 ||
            strcmp(token, "^") == 0 || strcmp(token, "raiz") == 0 ||
            strcmp(token, "sen") == 0 || strcmp(token, "cos") == 0 ||
            strcmp(token, "tg") == 0 || strcmp(token, "log") == 0) {
            char b[100], a[100], temp[100];
            if (strcmp(token, "raiz") == 0 || strcmp(token, "sen") == 0 ||
                strcmp(token, "cos") == 0 || strcmp(token, "tg") == 0 ||
                strcmp(token, "log") == 0) {
                strcpy(a, removerString(&armazenarStrings));
                sprintf(temp, "%s(%s)", token, a);
            } else {
                strcpy(b, removerString(&armazenarStrings));
                strcpy(a, removerString(&armazenarStrings));
                sprintf(temp, "(%s %s %s)", a, token, b);
            }
            adicionarString(&armazenarStrings, strdup(temp));
        } else {
            adicionarString(&armazenarStrings, strdup(token));
        }
        token = strtok(NULL, " "); // Próximo token
    }
    strcpy(resultado, removerString(&armazenarStrings)); // Copia o resultado para a string de saída
}
