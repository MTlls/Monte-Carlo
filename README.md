Matheus Telles Batista - GRR20211774
Wilian Pereira dos Santos - GRR20203936

# Integração e Métodos de Monte Carlo

Trabalho desenvolvido na disciplina de Introdução a Computação Científica com o objetivo de implementar o cálculo de integração por Monte Carlo.


## modo de uso
caso queira rodar apenas um comando para ver as diferenças, utilize
```bash
    source principal.sh
```

### geração de dados
```bash
    source ./gera_dados.sh
```
Esse shell script executa o programa ./monteCarlo retorna na saída especificada os dados gerados ao executar os métodos do retângulo e de Monte Carlo. Com uma diferença não tão visível

### formatação
```bash
    source ./formata_saida.sh
```
Esse shell script roda o programa e retorna na saída especificada os dados formatados para ver as diferenças nos métodos.

## erros ou problemas encontrados

Não foi encontrado algum problema visível aos alunos.

## Comparações

Primeiramente o temos abaixo o valor aproximado da integração para de -4 a 4 da equação de Styblinski-Tang para duas dimensões, para termos como o resultado real e quase-absoluto do problema.

$\displaystyle\int_{-4}^4 \int_{-4}^4 \frac{x^4 - 16 x^2 + 5x + y^4  - 16 y^2 + 5 y}{2} \mathrm{d}x \mathrm{d}y ≈ -2184.5333333...$

A seguir duas tabelas com os valores obtidos pelos logs das execuções (note que o método de Monte Carlo é constante pois estamos comparando apenas para 10⁷ amostras em duas dimensões com valores alterando apenas para o método dos retângulos)

|Pontos|Tempo Retângulos (ms)|Tempo Monte Carlo p/ 10⁷ amostras(ms)|
|:----:|:-------------------:|:------------------:|
| 10   | 0.000135            | 2685.430526      | 
| 10²  | 0.000209            | 2685.430526      |
| 10³  | 0.001118            | 2685.430526      |
| 10⁴  | 0.010404            | 2685.430526      |
| 10⁵  | 0.101223            | 2685.430526      |
| 10⁶  | 1.333846            | 2685.430526      |
| 10⁷  | 10.274587           | 2685.430526      |

|Pontos|Resultado Retângulos|Resultado Monte Carlo p/ 10⁷ amostras|
|:----:|:--------------------:|:-------------------:|
| 10   | 2204.18048000          |      2184.44076682 |
| 10²  | 2196.24115405          |      2184.44076682 |
| 10³  | 2185.80241068          |      2184.44076682 |
| 10⁴  | 2184.66122411          |      2184.44076682 |
| 10⁵  | 2184.54613224          |      2184.44076682 |
| 10⁶  | 2184.53461332          |      2184.44076682 |
| 10⁷  | 2184.53346133          |      2184.44076682 |

### Entrada aceitável

É visível que a partir de 10⁴ pontos, temos um ponto onde o valor para o metódo dos retângulos já ultrapassa o método de Monte Carlo em precisão, pois o erro absoluto é menor ($EA_{RET}$ = 0,12789081, $EA_{MC}$ = 0,220457290). Com o tempo uma diferença de tempo discrepante de 2685,429408 ms (2,6 segundos). 

Caso se deseja uma exatidão maior com menos tempo, é recomendado o método dos retângulos com 10⁴ ou mais pontos.

O porquê de ser mais rápido sendo que há mais loops no método dos retângulos do que no de Monte Carlo é explicado abaixo.

### Otimizações
Devido às otimizações feitas nos loops dentro da função de cálculo dos retângulos, a mesma se tornou extremamente mais rápida. Melhorado apenas com detalhes algébricos/analíticos, aparenta ser mais rápido que o método de Monte Carlo devido a estarmos trabalhando especificamente com a função de ``Styblinski-Tang`` (para funções genéricas, o mesmo não funcionaria).

A não-dependencia de $x$ com $y$ (tornando-os equivalentes no sentido do passo e portanto, iguais), a exclusão de $\frac{1}{2}$ dos somatórios e a manipulação algébrica dos somatórios torna que apenas é necessário calcular uma vez para $n$ pontos.

Abaixo uma demonstração, com $n$ sendo o número de dimensões e $p$ o número de pontos.

$\displaystyle h^{2}\sum_{i=1}^{p}\sum_{i=j}^{p} \frac{\displaystyle\sum_{k=1}^{n} x^4 - 16 x^2 + 5x}{2} = h^{2}  \frac{1}{2} \sum_{i=1}^{p}\sum_{j=1}^{p} {\sum_{k=1}^{n} x^4 - 16 x^2 + 5x}$

Como $x^4 - 16 x^2 + 5x = y^4 - 16 y^2 + 5y$ devido a serem equivalentes no sentido do passo e portanto, iguais. Podemos fazer isto:

$\displaystyle h^{2}  \frac{1}{2} \sum_{i=1}^{p}\sum_{j=1}^{p} {\sum_{k=1}^{n} x^4 - 16 x^2 + 5x} =
h^{2}  \frac{1}{2} \sum_{i=1}^{p}\sum_{j=1}^{p} {n (x^4 - 16 x^2 + 5x)} =$

$\displaystyle h^{2}  \frac{1}{2} \sum_{i=1}^{p}pn (x^4 - 16 x^2 + 5x) = 
\frac{1}{2} n  p h^{2} \sum_{i=1}^{p}(x^4 - 16 x^2 + 5x)$

Como $n = 2$, temos que

$ \displaystyle\frac{1}{2} 2 h^{2}p\sum_{i=1}^{p}(x^4 - 16 x^2 + 5x) =
 h^{2}p\sum_{i=1}^{p}(x^4 - 16 x^2 + 5x)$

No código está assim:
```
inline double f(double x) {
	return ((x * x * x * x) + (-16 * (x * x)) + (5 * x));
}

double retangulos_xy(double a, double b, int qntdPontos) {
    [...]
    
    for(int i = 0; i < qntdPontos; i++) {
    	soma += f(a + i * h);
    }

    // h² * somatorio * qntdPontos
    resultado = (h * h) * soma * qntdPontos;
    
    [...]
}
```
### Resultados de Monte Carlo

| Dimensões |  Resultado Monte Carlo | Tempo Monte Carlo p/ 10⁷ amostras (ms)|
|:---------:|:----------------------:|:-------------------------------------:|
|     2     |     2184.44076682     |             2685.430526                |
|     4     |     279623.48422305    |             5399.730683               |
|     8     |   2290631857.37847185  |             10597.398606              |

Sobre o método de integração por Monte Carlo, vemos que ela possa tem um caráter exponencial, devido a ser apenas para 2/4/8 dimensões, não pode-se dar uma certeza.

Em um teste qualquer, foi possível fazer um teste com 16 dimensões e foi obtido os valores

```
a = (-4.000000), b = (4.000000), n = (100000000), dimensões = 16
Tempo decorrido: 33847.010483 ms.
Resultado por Monte Carlo: -76860860886046144.00000000

```
Ficamos com a tabela assim...
| Dimensões |  Resultado Monte Carlo | Tempo Monte Carlo p/ 10⁷ amostras (ms)|
|:---------:|:----------------------:|:-------------------------------------:|
|     2     |     2184.44076682      |             2685.430526               |
|     4     |     279623.48422305    |             5399.730683               |
|     8     |   2290631857.37847185  |             10597.398606              |
|     16    |   76860860886046144.0  |             33847.010483              |

Vendo o valor altíssimo, pode se perceber o crescimento rápido dos valores.
