#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>

using namespace std;

// Function to check if v can be added to the current clique
bool isSafeToAdd(int v, vector<int>& clique, vector<vector<int>>& graph) {
    for (int u : clique) {
        if (graph[v][u] == 0) {
            return false;
        }
    }
    return true;
}

// Bron-Kerbosch algorithm with pivot to find maximum clique
void BronKerbosch(vector<vector<int>>& graph, vector<int>& clique, vector<int>& candidates, vector<int>& result) {
    if (candidates.empty()) {
        if (clique.size() > result.size()) {
            result = clique;
        }
        return;
    }

    // Pivot vertex selection: choose the vertex with the most neighbors in candidates
    int pivot = candidates[0];
    for (int v : candidates) {
        if (graph[v].size() > graph[pivot].size()) {
            pivot = v;
        }
    }

    vector<int> candidatesCopy = candidates;
    for (int v : candidatesCopy) {
        if (graph[v][pivot] == 1) {
            continue; // Not adjacent
        }

        vector<int> newClique = clique;
        newClique.push_back(v);

        vector<int> newCandidates;
        for (int u : candidates) {
            if (graph[v][u] == 1) {
                newCandidates.push_back(u);
            }
        }

        BronKerbosch(graph, newClique, newCandidates, result);
        candidates.erase(remove(candidates.begin(), candidates.end(), v), candidates.end());
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
        grafo[v - 1][u - 1] = 1;  // O grafo é não direcionado
    }

    arquivo.close();

    return grafo;
}

int main(){

    int numVertice = 50;

    vector<int> clique;
    vector<int> candidates(numVertice);
    iota(candidates.begin(), candidates.end(), 0);
    vector<int> result;

    vector<vector<int>> grafo = LerGrafo("grafo.txt", numVertice); // Variaveis: Nome do Arquivo, número de vértices

    BronKerbosch(grafo, clique, candidates, result);

    // vector<int> resposta = EncontrarCliqueMaxima(grafoAnalise, numVertice); // Variaveis: Retorno da função LerGrafo(), número de vértices

    cout << "Maximum Clique: ";

    for (int node : result) {
        cout << node << " ";
    }
    cout << endl;

    cout << "Tamanho da lista: " << result.size() << endl;

    return 0;

}