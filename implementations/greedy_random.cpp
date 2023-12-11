#include <iostream>
#include <algorithm> 
#include <numeric>
#include "./utils/read_graph.cpp"
#include <random>
#include <chrono>
#include <string>

using namespace std;

// Função auxiliar do sort para ordenar em ordem crescente por degree
bool ascending_degree(int a, int b,vector<vector<int>> graph, vector<int> vertices){
    int degree_a = 0;
    int degree_b = 0;
    for (int v: vertices){
        if (graph[a][v] == 1){
            degree_a++;
        }
        if (graph[b][v] == 1){
            degree_b++;
        }
    }
    return degree_a > degree_b;
}

// Encontra o clique máximo baseado na heurística gulosa e aleatoriedade
int find_max_clique(vector<vector<int>> graph, int numVertices){
    vector<int> vertices(numVertices);
    
    // Ordena em ordem crescente de degree os vértices
    iota(vertices.begin(), vertices.end(), 0);
    vector<int> copy_vertices(vertices);
    sort(vertices.begin(), vertices.end(), [graph, copy_vertices](int a, int b){
        return ascending_degree(a, b, graph, copy_vertices);
    });

    vector<int> max_clique;

    // Testa de maneira paralela todos os vértices verificando se pode ser acrescentado
    // no clique, sendo o primeiro e segundo vértices o que possui maior degree no grafo e 
    // os seguintes de maneira aleatória 
    for (int k = numVertices-1; k >= 0; k--){
        vector<int> local_clique;
        vector<int> candidates(vertices);

        // Coloca o k como último vértice para que o clique comece a partir dele
        int vertice_test = candidates[k];
        candidates.erase(candidates.begin()+k);
        candidates.push_back(vertice_test);
        
        while (!candidates.empty()){
            int v = candidates.back();
            candidates.pop_back();

            bool can_add = true;

            for(int u: local_clique){
                if (graph[u][v] == 0){
                    can_add = false;
                    break;
                }
            }

            if (can_add){
                local_clique.push_back(v);
                vector<int> new_candidates;

                for (int u: candidates){
                    bool adjacent_to_all = true;
                    for (int c: local_clique){
                        if (graph[u][c] == 0){
                            adjacent_to_all = false;
                            break;
                        }
                    }

                    if (adjacent_to_all){
                        new_candidates.push_back(u);
                    }
                }
                
                // Somente embaralha os vértices se o clique local tiver mais de dois vértices
                // para fazer uso da heuristica gulosa e aleatoriedade
                if (local_clique.size()>2){
                    random_device rd;
                    mt19937 gerador(rd());

                    // Embaralha os vértices para que a escolha seja aleatória
                    shuffle(new_candidates.begin(), new_candidates.end(), gerador);
                }
                candidates = new_candidates;
            }
        }
       
        // Se o clique local for maior que o clique máximo já encontrado
        // altera o clique máximo para clique local
        if (local_clique.size() > max_clique.size()){
            max_clique = local_clique;
        }
    }

    return max_clique.size();
}

int main(){
    int num_vertices;
    for (int i = 25; i <= 150; i+=25){
        string name_file = "./graphs/graph_" + to_string(i) + ".txt";
        vector<vector<int>> graph = LerGrafo(name_file, num_vertices);
        auto start_time = chrono::high_resolution_clock::now();
        int size_max_clique = find_max_clique(graph, num_vertices);
        auto end_time = chrono::high_resolution_clock::now();
        auto time = end_time - start_time;
        cout << "Para um clique de tamanho " << i << endl;
        cout << "Tempo de execução: " << chrono::duration_cast<chrono::milliseconds>(time).count() << "ms" << endl;
        cout << "Tamanho do Clique Máximo: " << size_max_clique << endl << endl;
    }
    return 0;
}