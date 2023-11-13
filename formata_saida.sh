#!/bin/bash
log_file="dados.log"

# Inicialize os arrays
declare -a TEMPO_RET
declare -a RESULTADO_RET

PONTOS=10
DIMENSOES=2

TEMPO_2D_MONTECARLO=$(grep 'Tempo decorrido:' $log_file | head -n 1 | awk '{print $3}')
RESULTADO_2D_MONTECARLO=$(grep 'Resultado por Monte Carlo:' $log_file | head -n 1 | awk '{print $5}')

echo "Diferenças entre Monte Carlo 2D e método do retângulo"

echo "Retângulos | Monte Carlo"
# Preenche os arrays usando um loop
for i in {2..8}; do
    TEMPO_RET[$i-1]=$(grep 'Tempo decorrido:' $log_file | sed -n "${i}p" | awk '{printf $3}')
    RESULTADO_RET[$i-1]=$(grep 'Resultado por método dos retângulos:' $log_file |  sed -n "$((i-1))p" | awk '{printf $6}')

    printf "\n%d pontos:\n" "$PONTOS"
    printf "Tempo:     [%14s | %10s]\n" "${TEMPO_RET[$i-1]} ms" "${TEMPO_2D_MONTECARLO} ms"
    printf "Resultado: [%14s | %14s]\n" "${RESULTADO_RET[$i-1]}" "${RESULTADO_2D_MONTECARLO}"

    PONTOS=$((PONTOS * 10))
done

echo
echo "Diferenças entre as iterações em dimensão do método de Monte Carlo"

# Preenche os arrays usando um loop
printf "\n2D:\n"
printf "Tempo:     [%+20s]\n" "${TEMPO_2D_MONTECARLO} ms"
printf "Resultado: [%+20s]\n" "${RESULTADO_2D_MONTECARLO}"
for i in {9..10}; do
    DIMENSOES=$((DIMENSOES * 2))
    printf "\n%dD:\n" "${DIMENSOES}"
    TEMPO_MONTECARLO=$(grep 'Tempo decorrido:' $log_file | sed -n "${i}p" | awk '{printf $3}')
    RESULTADO_MONTECARLO=$(grep 'Resultado por Monte Carlo:' $log_file | sed -n "$((i-7))p"| awk '{printf $NF}')

    printf "Tempo:     [%+20s]\n" "${TEMPO_MONTECARLO} ms"
    printf "Resultado: [%+20s]\n" "${RESULTADO_MONTECARLO}"

done