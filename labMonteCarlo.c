#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

#define DIFF 0.0

#define NRAND ((double)rand() / RAND_MAX)  // drand48()
#define SRAND(a) srand(a)                  // srand48(a)
#define NPONTOS (int)10e7
/**
 * Função que faz a resolução da equação que será futuramente somada no numerador da função de styblinskiTang.
 *
 * f(x)=x⁴-16x²+5x
 * @param x valor da variável aleatória
 */
inline double f(double x) {
	return ((x * x * x * x) + (-16 * (x * x)) + (5 * x));
}

// Integral Monte Carlo da função    de 2 variáveis
double styblinskiTang(double a, double b, int dimensoes) {
	double resultado = 0.0, soma = 0.0, h = b - a, x = 0.0;
	double t_inicial, t_final;  // tempo que será cronometrado.

	printf("a = (%f), b = (%f), n = (%d), dimensões = %d\n", a, b, NPONTOS, dimensoes);

	t_inicial = timestamp();

	// feito o cálculo para cada amostra de ponto
	for(int i = 0; i < NPONTOS; i++) {
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
	resultado = pow(h, dimensoes) * (resultado / NPONTOS);

	t_final = timestamp();
	printf("Tempo decorrido: %f ms.\n", t_final - t_inicial);

    // positivo
    resultado = resultado < 0 ? resultado * -1 : resultado;
	return resultado;
}

double retangulos_xy(double a, double b, int qntdPontos) {
	double resultado = 0.0;
	double soma = 0.0, intervalo = b - a;
	double h = (intervalo) / qntdPontos;
	double t_inicial = 0, t_final = 0;
	printf("a = (%f), b = (%f), n = (%d), h = (%lg)\n", a, b, qntdPontos, h);

	t_inicial = timestamp();

	// Como x e y são repetidos npontos vezes (2*npontos) e após isso o valor é divido pela metade, acaba que é equivalente a não ter dividido e executar apenas npontos vezes.
	for(int i = 0; i < qntdPontos; i++) {
		soma += (f(a + i * h) * qntdPontos);
	}

	// h² * somatorio
	resultado = (h * h) * soma;

	t_final = timestamp();
	printf("Tempo decorrido: %f ms.\n", t_final - t_inicial);

    // positivo
    resultado = resultado < 0 ? resultado * -1 : resultado;
	return resultado;
}

int main(int argc, char **argv) {
	if(argc < 5) {
		printf("Utilização: %s inicial final n_amostras n_variaveis\n",
		       argv[0]);
		return 1;
	}

#ifdef _MC_
	SRAND(20232);
	// INICIAR VALOR DA SEMENTE
	// CHAMAR FUNÇÕES DE INTEGRAÇÃO E EXIBIR RESULTADOS
	printf("Resultado por Monte Carlo: %.8lf\n", styblinskiTang(atoi(argv[1]), atoi(argv[2]), atoi(argv[4])));
	putchar('\n');
#endif
#ifdef _RET_
	// Resetando a seed
	SRAND(20232);
	printf("Resultado por método dos retângulos: %.8lf\n", retangulos_xy(atoi(argv[1]), atoi(argv[2]), atoi(argv[3])));
	return 0;
#endif
}
