#ifndef CALCULADORA_H
#define CALCULADORA_H

#define MAX_PILHA_TAM 100

typedef struct {
    double num[MAX_PILHA_TAM];
    int topo;
} ArmazenarNumeros;

typedef struct {
    char* strings[MAX_PILHA_TAM];
    int topo;
} ArmazenarStrings;

// Declarações das funções
void adicionar(ArmazenarNumeros* armazenarNumeros, double valor);
double remover(ArmazenarNumeros* armazenarNumeros);
void adicionarString(ArmazenarStrings* armazenarStrings, char* valor);
char* removerString(ArmazenarStrings* armazenarStrings);

double soma(double a, double b);
double subtracao(double a, double b);
double multiplicacao(double a, double b);
double divisao(double a, double b);
double potencia(double a, double b);
double raiz(double a, double b);
double seno(double a);
double cosseno(double a);
double tangente(double a);
double logaritmo(double a);

double avaliarPosfixa(char* expr);
void posfixaParaPreFixa(char* expr, char* resultado);
void posfixaParaInfixa(char* expr, char* resultado);

#endif
