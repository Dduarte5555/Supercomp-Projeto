# Supercomp-Projeto
Análise de Redes Sociais: encontrando a clique máxima em um grafo.

## Objetivo: 
  O objetivo principal deste trabalho é desenvolver implementações que consigam encontrar a clique máxima em um grafo em tempo hábil.

## Primeira Implementação: 
Para a primeira implementação, foi adotada a Abordagem Exaustiva.

Para esta parte, há a pasta Heurística, em que nela existem dois arquivos principais:

* 1 - AbordagemExaustiva.cpp

* 2 - AbordagemExaustiva-BronKerbosch.cpp

Sobre o primeiro, foi a implementação do pseudocódigo passado em aula para a tentativa do começo do trabalho. 
Para números pequenos, ele funciona, porém para números medianos, código não funciona adequadamente, ou seja, não encontra a clique máxima.
Em tese, este código tem o objetivo de ser o ponto de partida para podermos explorar novas heurísticas e buscarmos um algoritmo que nos ajude a resolver o problema. 

Para o segundo arquivo, foi levado em conta o primeiro, e houve a implementação da abordagem do algoritmo de Bron-Kerbosch com pivot.
A ideia principal é escolher um vértice de "pivô" apropriado (com base na estratégia de seleção de pivô) e, em seguida, explorar todas as possibilidades de formar uma clique máxima usando esse vértice de pivô.
Essa abordagem garante que você obtenha a clique máxima no grafo fornecido. O algoritmo explora recursivamente todas as possibilidades e usa a estratégia de seleção de pivô para otimizar o processo de busca.

## Segunda Implementação:
 Para a segunda implementação, foi adotada a Abordagem com Threads OpenMP

 Esta implementação está presente na pasta: OpenMP

 Para a sua compilação:
 ```g++ -o <output_file> -fopenmp AbordagemOpenMP.cpp ```

 Para que haja uma comparação entre a heurística implementada e o OpenMP, foi pego como arquivo base, AbordagemExaustiva.cpp, fazendo assim uma melhor análise entre um arquivo com e sem paralelização com OpenMP.
 Explicando em suma o arquivo, a partir do arquivo base, foi feito implementações que mudassem e permitiam a paralelização do programa.
 Estas modificaçãos estão presentes principalmente em "for"s que possam ser paralelizados e possam acelerar a velocidade de execução do código.

 ## Terceira Implementação:
 Para a terceira implementação, foi adotada a Abordagem com MPI

 Esta implementação está presente na pasta: MPI
 
 Para a sua compilação:
 ```mpic++ -o <output_file> AbordagemMPI.cpp ```
 
 Para a sua execução:
 ```mpirun -np <número de processadores> ./output_file ```

 Neste módulo, foi utilizado os arquivos presentes na pasta heurística para, a partir deles, desenvolver o código com MPI, em que tinha como objetivo separar o programa em partes e distrubuir para os diferentes processadores, presentes na arquitetura de um cluster. Quero deixar ressaltado que o job do MPI não executou porque teve erro na hora de submeter o job. Sendo assim, utilizarei valores médios que eram para ter dado utilizando o MPI.


## Análises:
 Para análise de das implementações, foi procurado quantificar a velocidade, então, foi pego o tempo de execução de cada arquivo sob cada cenário.
 
 Para melhot ver o desempenho, foi selecionado três cenários:
 
* 1 - Criação de um grafo com 20 nós e uma probabilidade de haver uma aresta entre dois vértices de 0.7
* 2 - Criação de um grafo com 40 nós e uma probabilidade de haver uma aresta entre dois vértices de 0.7
* 3 - Criação de um grafo com 60 nós e uma probabilidade de haver uma aresta entre dois vértices de 0.7

  #TODO: COLOCAR GRAFICO

 Ao observar a imagem, vemos que quanto maior o número de nós, mais nítido fica que a paralelização feita pelo openmp é mais rápido que a heurística.
 Enquanto no primeiro cenário, a primeira abordagem teve um tempo de 37ms, e outro foi 15ms. No cenário 2, a diferença aumentou, em que o primero demorou aproximadamente 1934ms e o outro demorou 1329ms.
 Por fim no terceiro cenário, o primeiro demorou aproximadamente 13507ms e o outro demorou 4796ms.
    
