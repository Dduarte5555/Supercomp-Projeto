#include<iostream>
#include<vector>
#include<algorithm>
#include <random>
#include<fstream>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

vector<vector<int>> LerGrafo(const string& nomeArquivo, int& numVertices) {
    ifstream arquivo(nomeArquivo);
    int numArestas;
    arquivo >> numVertices >> numArestas;

    vector<vector<int>> grafo(numVertices, vector<int>(numVertices, 0));

    for (int i = 0; i < numArestas; ++i) {
        int u, v;
        arquivo >> u >> v;
        grafo[u - 1][v - 1] = 1;
        grafo[v - 1][u - 1] = 1;  // O grafo é não direcionado
    }

    arquivo.close();

    return grafo;
}

vector<int> EncontrarCliqueMaxima(vector<vector<int>> grafo, int numVertices) {

    vector<int> cliqueMaxima;
    vector<int> candidatos;

    #pragma omp parallel for
    for (int i = 0; i < numVertices - 1; i++) {
        #pragma omp critical
        candidatos.push_back(i);
    }

    while (!candidatos.empty()) {

        int v;
        #pragma omp critical
        {
            v = candidatos.back();
            candidatos.pop_back();
        }

        bool podeAdicionar = true;

        #pragma omp parallel for
        for (int u : cliqueMaxima) {
            if (grafo[u][v] == 0) {
                #pragma omp atomic write
                podeAdicionar = false;
            }
        }

        if (podeAdicionar) {
            cliqueMaxima.push_back(v);
            vector<int> novosCandidatos;

            #pragma omp parallel
            {
                vector<int> privateNovosCandidatos;

                #pragma omp for
                for (int u : candidatos) {
                    bool adjacenteATodos = true;

                    #pragma omp parallel for
                    for (int c : cliqueMaxima) {
                        if (grafo[u][c] == 0) {
                            #pragma omp atomic write
                            adjacenteATodos = false;
                        }
                    }

                    if (adjacenteATodos) {
                        privateNovosCandidatos.push_back(u);
                    }
                }

                #pragma omp critical
                {
                    novosCandidatos.insert(novosCandidatos.end(), privateNovosCandidatos.begin(), privateNovosCandidatos.end());
                }
            }

            candidatos.insert(candidatos.end(), novosCandidatos.begin(), novosCandidatos.end());
        }
    }
    return cliqueMaxima;
}


int main(){

    auto start_time = high_resolution_clock::now(); // Começa a contar o tempo para análise

    int numVertice = 200;

    vector<vector<int>> grafoAnalise = LerGrafo("grafo.txt", numVertice); // Variaveis: Nome do Arquivo, número de vértices

    vector<int> resposta = EncontrarCliqueMaxima(grafoAnalise, numVertice); // Variaveis: Retorno da função LerGrafo(), número de vértices

    auto end_time = high_resolution_clock::now(); // Guarda o tempo final

    auto duration = duration_cast<milliseconds>(end_time - start_time); // Cálculo da duração do tempo do código em ms

    cout << "Maximum Clique: ";

    for (int node : resposta) {
        cout << node << " ";
    }
    cout << endl;

    cout << "Tamanho da lista: " << resposta.size() << endl;

    cout << "Tempo de Execução: " << duration.count() << " ms" << endl;

    return 0;

}