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

A seguir uma instância de log formatado:

```Diferenças entre Monte Carlo 2D e método do retângulo
Retângulos | Monte Carlo

10 pontos:
Tempo:     [   0.000135 ms | 2685.430526 ms]
Resultado: [-2204.18048000 | -2184.44076682]

100 pontos:
Tempo:     [   0.000209 ms | 2685.430526 ms]
Resultado: [-2196.24115405 | -2184.44076682]

1000 pontos:
Tempo:     [   0.001118 ms | 2685.430526 ms]
Resultado: [-2185.80241068 | -2184.44076682]

10000 pontos:
Tempo:     [   0.010404 ms | 2685.430526 ms]
Resultado: [-2184.66122411 | -2184.44076682]

100000 pontos:
Tempo:     [   0.101223 ms | 2685.430526 ms]
Resultado: [-2184.54613224 | -2184.44076682]

1000000 pontos:
Tempo:     [   1.333846 ms | 2685.430526 ms]
Resultado: [-2184.53461332 | -2184.44076682]

10000000 pontos:
Tempo:     [  10.274587 ms | 2685.430526 ms]
Resultado: [-2184.53346133 | -2184.44076682]

Diferenças entre as iterações em dimensão do método de Monte Carlo

2D:
Tempo:     [2685.430526 ms]
Resultado: [-2184.44076682]

4D:
Tempo:     [5399.730683 ms]
Resultado: [-279623.48422305]

8D:
Tempo:     [10597.398606 ms]
Resultado: [-2290631857.37847185]
```

A seguir a tabela correspondente
|Pontos|Tempo Retângulos (ms)|Resultado Retângulos|Tempo Monte Carlo p/ 10⁷ amostras(ms)|Resultado Monte Carlo p/ 10⁷ amostras|
|:----:|:-------------------:|:------------------:|:--------------------:|:-------------------:|
| 10   | 0.000135            | 2204.18048000     | 2685.430526          | 2184.44076682      | 
| 10²  | 0.000209            | 2196.24115405     | 2685.430526          | 2184.44076682      |
| 10³  | 0.001118            | 2185.80241068     | 2685.430526          | 2184.44076682      |
| 10⁴  | 0.010404            | 2184.66122411     | 2685.430526          | 2184.44076682      |
| 10⁵  | 0.101223            | 2184.54613224     | 2685.430526          | 2184.44076682      |
| 10⁶  | 1.333846            | 2184.53461332     | 2685.430526          | 2184.44076682      |
| 10⁷  | 10.274587           | 2184.53346133     | 2685.430526          | 2184.44076682      |

### Entrada aceitável

É visível que a partir de 10³ pontos, temos uma diferença de uma unidade entre o método de integração dos retângulos e do método de integração por Monte Carlo. Com um tempo uma diferença de tempo discrepante de 2685,429408 ms (2,6 segundos). Caso se deseja uma exatidão, é recomenado 10⁴ ou mais pontos.

### Otimizações
Devido às otimizações feitas nos loops dentro da função de cálculo dos retângulos, a mesma se tornou extremamente mais rápida. Melhorado apenas com detalhes algébricos, aparenta ser mais rápido que o método de Monte Carlo (apenas em instâncias de duas dimensões, pois o problema aumenta exponencialmente com mais passos).

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