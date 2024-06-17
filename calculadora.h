#ifndef CALCULADORA_H
#define CALCULADORA_H

#include <math.h>

#define MAX_EXPR_LEN 100
#define MAX_PILHA_TAM 100
#define DEG_TO_RAD(deg) ((deg) * M_PI / 180.0)

typedef struct {
    double num[MAX_PILHA_TAM];
    int topo;
} ArmazenarNumeros;

typedef struct {
    char* strings[MAX_PILHA_TAM];
    int topo;
} ArmazenarStrings;

typedef struct {
    char posFixa[512];     // Expressão na forma pós-fixada, como 3 12 4 + *
    char inFixa[512];      // Expressão na forma infixada, como 3 * (12 + 4)
    float Valor;           // Valor numérico da expressão  
} Expressao;

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

char* getFormaInFixa(char* Str);    // Retorna a forma infixada de Str (pós-fixada)
float getValor(char* Str);          // Calcula o valor de Str (na forma pós-fixada)

#endif // CALCULADORA_H
