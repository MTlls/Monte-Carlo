#!/bin/bash

PONTOS=10
DIMENSOES=2
# executa 10⁷ para monte carlo e 10 pontos pelos retangulos
make -s purge
echo
echo "Fazendo o caso 10⁷ para o método de Monte Carlo em 2 dimensões"
make -s mc
echo
./monteCarlo -4 4 ${PONTOS} ${DIMENSOES}

# apenas executa pelos retangulos agora
make purge

echo
printf '%75s\n' | tr ' ' '-'
echo
echo "Fazendo os casos de 10 até 10⁷ para o método dos retângulos em 2 dimensões"
make -s ret
echo

for i in {1..7}
do
    ./monteCarlo -4 4 ${PONTOS} 2
    PONTOS=$((PONTOS * 10))
    echo
done
echo
make purge
printf '%75s\n' | tr ' ' '-'
echo
echo "Fazendo os casos de 2, 4 e 8 dimensões de Monte Carlo."
make -s mc
for i in {1..2}
do
    DIMENSOES=$((DIMENSOES * 2))
    ./monteCarlo -4 4 ${PONTOS} ${DIMENSOES}
    echo
done
