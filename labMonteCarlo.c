#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

#define DIFF 0.0

#define NRAND ((double)rand() / RAND_MAX)  // drand48()
#define SRAND(a) srand(a)                  // srand48(a)

/**
 * Função que faz a resolução da equação que será futuramente somada no numerador da função de styblinskiTang.
 *
 * f(x)=x⁴-16x²+5x
 * @param x valor da variável aleatória
 */
inline double f(double x) {
	return ((x * x * x * x) + (-16 * (x * x)) + (5 * x));
}

// Integral Monte Carlo da função Styblinski-Tang de 2 variáveis
double styblinskiTang(double a, double b, int namostras, int dimensoes) {
	double resultado = 0.0, soma = 0.0, h = b - a, x = 0.0;
	double t_inicial, t_final;  // tempo que será cronometrado.

	printf("Metodo de Monte Carlo (x, y).\n");
	printf("a = (%f), b = (%f), n = (%d), variaveis = 2\n", a, b, namostras);

	t_inicial = timestamp();

	// feito o cálculo para cada amostra de ponto
	for(int i = 0; i < namostras; i++) {
		// Dita quantas dimensões tem, executa para n-1 dimensoes
		/* até tentamos dar unroll, mas parece que o NRAND impossibilita o compilador de otimizar */
		for(int j = 0; j < dimensoes; j++) {
			// Aqui é setado a variável aleatória entre b e a, uma para cada
			// dimensão
			x = (NRAND * (h)) + a;
			soma += f(x);
		}

		// a divisão é feita somente após ser calculado o somatório.
		resultado += soma * 0.5;
		soma = 0;
	}

	// É feita a divisão e para cada dimensão, se multiplica por (b-a), logo, temos ((b-a)^dimensoes) * resultado / amostras.
	resultado = pow(h, dimensoes) * (resultado / namostras);

	t_final = timestamp();
	printf("Tempo decorrido: %f ms.\n", t_final - t_inicial);

	return resultado;
}

// double retangulos_xy(double a, double b, int npontos) {
//     double h;
//     double resultado;
//     double soma = 0;

//     printf("Metodo dos Retangulos (x, y).\n");
//     printf("a = (%f), b = (%f), n = (%d), h = (%lg)\n", a, b, npontos, h);

//     double t_inicial = timestamp();

//     /*

//       AQUI IMPLEMENTE O CÁLCULO DA INTEGRAL PELO
//       MÉTODO DOS RETÂNGULOS

//     */

//     double t_final = timestamp();
//     printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);

//     return resultado;
// }

int main(int argc, char **argv) {
	if(argc < 5) {
		printf("Utilização: %s inicial final n_amostras n_variaveis\n",
		       argv[0]);
		return 1;
	}

	SRAND(20232);

	// INICIAR VALOR DA SEMENTE
	// CHAMAR FUNÇÕES DE INTEGRAÇÃO E EXIBIR RESULTADOS
	printf("resultado por Monte Carlo: %lf\n", styblinskiTang(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4])));
	return 0;
}
