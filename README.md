# Supercomp-Projeto
Análise de Redes Sociais: encontrando a clique máxima em um grafo.

## Objetivo: 
  O objetivo principal deste trabalho é desenvolver implementações que consigam encontrar a clique máxima em um grafo em tempo hábil.

## Primeira Implementação: 
Para a primeira implementação, foi adotado a Abordagem Exaustiva.

Para esta parte, existem dois arquivos principais:

  1 - AbordagemExaustiva.cpp

  2 - AbordagemExaustiva-V2.cpp

Sobre o primeiro, foi a implementação do pseudocódigo passado em aula para a tentativa do começo do trabalho. 
Para números pequenos, ele funciona, porém para números medianos, código não funciona adequadamente, ou seja, não encontra a clique máxima.

Sobre a versão 2, foi levado em conta o primeiro arquivo e houve a implementação da abordagem do algoritmo de Bron-Kerbosch com pivot.
A ideia principal é escolher um vértice de "pivô" apropriado (com base na estratégia de seleção de pivô) e, em seguida, explorar todas as possibilidades de formar uma clique máxima usando esse vértice de pivô.
Essa abordagem garante que você obtenha a clique máxima no grafo fornecido. O algoritmo explora recursivamente todas as possibilidades e usa a estratégia de seleção de pivô para otimizar o processo de busca.
