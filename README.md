# Supercomp-Projeto
Análise de Redes Sociais: encontrando a clique máxima em um grafo.

## Objetivo: 
  O objetivo principal deste trabalho é desenvolver implementações que consigam encontrar a clique máxima em um grafo em tempo hábil.

## Primeira Implementação: 
Para a primeira implementação, foi adotada a Abordagem Exaustiva.

Para esta parte, existem dois arquivos principais:

  1 - AbordagemExaustiva.cpp

  2 - AbordagemExaustiva-BronKerbosch.cpp

Sobre o primeiro, foi a implementação do pseudocódigo passado em aula para a tentativa do começo do trabalho. 
Para números pequenos, ele funciona, porém para números medianos, código não funciona adequadamente, ou seja, não encontra a clique máxima.
Em tese, este código tem o objetivo de ser o ponto de partida para podermos explorar novas heurísticas e buscarmos um algoritmo que nos ajude a resolver o problema. 

Para o segundo arquivo, foi levado em conta o primeiro, e houve a implementação da abordagem do algoritmo de Bron-Kerbosch com pivot.
A ideia principal é escolher um vértice de "pivô" apropriado (com base na estratégia de seleção de pivô) e, em seguida, explorar todas as possibilidades de formar uma clique máxima usando esse vértice de pivô.
Essa abordagem garante que você obtenha a clique máxima no grafo fornecido. O algoritmo explora recursivamente todas as possibilidades e usa a estratégia de seleção de pivô para otimizar o processo de busca.

## Segunda Implementação:
Para a segunda implementação, foi adotada a Abordagem com Threads OpenMP

Esta implementação está presente no arquivo: AbordagemOpenMP.cpp

Para a sua compilação:
 ```g++ -o <output_file> -fopenmp AbordagemOpenMP.cpp ```

Para que haja uma comparação, foi pego o arquivo com o Bron-Kerbosch para uma melhor análise entre um arquivo com e sem paralelização com OpenMP
Explicando em suma o arquivo, a partir do arquivo base, foi feito implementações que mudassem e permitiam a paralelização do programa.
Estas modificaçãos estão presentes principalmente em "for"s que possam ser paralelizados e possam acelerar a velocidade de execução do código.

## Análises:

