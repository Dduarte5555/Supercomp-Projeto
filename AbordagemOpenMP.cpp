#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <chrono>
#include <omp.h> // Include OpenMP header

using namespace std;
using namespace std::chrono;

bool isSafeToAdd(int v, vector<int>& clique, vector<vector<int>>& graph) {
    for (int u : clique) {
        if (graph[v][u] == 0) {
            return false;
        }
    }
    return true;
}

void BronKerbosch(vector<vector<int>>& graph, vector<int>& clique, vector<int>& candidates, vector<int>& result) {
    if (candidates.empty()) {
        #pragma omp critical
        {
            if (clique.size() > result.size()) {
                result = clique;
            }
        }
        return;
    }

    int pivot = candidates[0];
    #pragma omp parallel for
    for (int v : candidates) {
        if (graph[v].size() > graph[pivot].size()) {
            #pragma omp critical
            {
                if (graph[v].size() > graph[pivot].size()) {
                    pivot = v;
                }
            }
        }
    }

    vector<int> candidatesCopy = candidates;
    #pragma omp parallel for
    for (int v : candidatesCopy) {
        if (graph[v][pivot] == 1) {
            continue;
        }

        vector<int> newClique = clique;
        newClique.push_back(v);

        vector<int> newCandidates;
        #pragma omp parallel for
        for (int u : candidates) {
            if (graph[v][u] == 1) {
                newCandidates.push_back(u);
            }
        }

        BronKerbosch(graph, newClique, newCandidates, result);
        
        #pragma omp critical
        {
            candidates.erase(remove(candidates.begin(), candidates.end(), v), candidates.end());
        }
    }
}

vector<vector<int>> LerGrafo(const string& nomeArquivo, int& numVertices) {
    ifstream arquivo(nomeArquivo);
    int numArestas;
    arquivo >> numVertices >> numArestas;

    vector<vector<int>> grafo(numVertices, vector<int>(numVertices, 0));

    for (int i = 0; i < numArestas; ++i) {
        int u, v;
        arquivo >> u >> v;
        grafo[u - 1][v - 1] = 1;
        grafo[v - 1][u - 1] = 1;
    }

    arquivo.close();

    return grafo;
}

int main() {
    auto start_time = high_resolution_clock::now();

    int numVertice = 300;

    vector<int> clique;
    vector<int> candidates(numVertice);
    iota(candidates.begin(), candidates.end(), 0);
    vector<int> result;

    vector<vector<int>> grafo = LerGrafo("grafo.txt", numVertice);

    BronKerbosch(grafo, clique, candidates, result);

    auto end_time = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end_time - start_time);

    cout << "Maximum Clique: ";
    for (int node : result) {
        cout << node << " ";
    }
    cout << endl;

    cout << "Tamanho da lista: " << result.size() << endl;

    cout << "Tempo de Execução: " << duration.count() << " ms" << endl;

    return 0;
}