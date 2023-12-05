#include<iostream>
#include<vector>
#include<algorithm>
#include <random>
#include<fstream>
#include <chrono>
#include <mpi.h>

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

vector<int> EncontrarCliqueMaxima(vector<vector<int>> grafo, int numVertices, int rank, int size) {
	vector<int> cliqueMaximaLocal;
	int chunk_size = numVertices / size;
	int start_index = rank * chunk_size;
    	int end_index = (rank == size - 1) ? numVertices : (rank + 1) * chunk_size;

	for (int i = start_index; i < end_index; ++i) {
        	vector<int> candidatos;
        	for (int j = 0; j < numVertices; ++j) {
            		if (grafo[i][j] == 1) {
                		candidatos.push_back(j);
            		}
        	}

        	vector<int> cliqueLocal;
        	cliqueLocal.push_back(i);

        	for (int v : candidatos) {
            		bool podeAdicionar = true;
            		for (int u : cliqueLocal) {
                		if (grafo[u][v] == 0) {
                    			podeAdicionar = false;
                    			break;
                		}
            		}
            		if (podeAdicionar) {
               			cliqueLocal.push_back(v);
            		}
        	}

        	if (cliqueLocal.size() > cliqueMaximaLocal.size()) {
            	cliqueMaximaLocal = cliqueLocal;
        	}
    	}

 	vector<int> globalCliqueMaxima;
   	globalCliqueMaxima.resize(numVertices, 0);

    	MPI_Gather(&cliqueMaximaLocal[0], cliqueMaximaLocal.size(), MPI_INT, &globalCliqueMaxima[0], cliqueMaximaLocal.size(), MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		vector<int> globalCliqueMaxima(numVertices, 0);
		for (int p = 0; p < size; ++p) {
        		int start_index_p = p * chunk_size;
        		int end_index_p = (p == size - 1) ? numVertices : (p + 1) * chunk_size;
			for (int i = start_index_p; i < end_index_p; ++i) {
            			if (globalCliqueMaxima[i] < globalCliqueMaxima[i + chunk_size]) {
                			globalCliqueMaxima[i] = globalCliqueMaxima[i + chunk_size];
            			}
        		}
    		}

	}
	return globalCliqueMaxima;
}
int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	auto start_time = high_resolution_clock::now();

	int numVertice = 200;
	vector<vector<int>> grafoAnalise;

	if (rank == 0) {
		grafoAnalise = LerGrafo("grafo.txt", numVertice);
	}

	MPI_Bcast(&numVertice, 1, MPI_INT, 0, MPI_COMM_WORLD);
	grafoAnalise.resize(numVertice, vector<int>(numVertice, 0));
	MPI_Bcast(&grafoAnalise[0][0], numVertice * numVertice, MPI_INT, 0, MPI_COMM_WORLD);

	vector<int> resposta = EncontrarCliqueMaxima(grafoAnalise, numVertice, rank, size);

	auto end_time = high_resolution_clock::now();

	auto duration = duration_cast<milliseconds>(end_time - start_time);

	vector<int> global_resposta;
	MPI_Gather(&resposta[0], resposta.size(), MPI_INT, &global_resposta[0], resposta.size(), MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		cout << "Maximum Clique: ";
		for (int node : global_resposta) {
			cout << node << " ";
		}
		cout << endl;

        	cout << "Tamanho da lista: " << global_resposta.size() << endl;

        	cout << "Tempo de Execução: " << duration.count() << " ms" << endl;
	}

	MPI_Finalize();

	return 0;
}
