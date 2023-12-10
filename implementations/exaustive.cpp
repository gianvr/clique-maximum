#include <iostream>
#include <vector>
#include <string>
#include "./utils/read_graph.cpp"
#include <chrono>

using namespace std;

//Verifica se o vertice pode ser adicionado ao clique
bool is_clique(const vector<vector<int>>& graph, const vector<int>& current_clique, int vertex) {
    for (int v : current_clique) {
        if (graph[vertex][v] == 0) {
            return false;
        }
    }
    return true;
}

// De maneira recursiva explora os cliques de um vértice no grafo para encontrar o clique máximo
// faz uso da característica de que o clique dos vértices anteriores já foram calculado para não 
// ter que calcular de novo
void explore_clique(const vector<vector<int>>& graph, int vertex, vector<int>& current_clique, vector<int>& clique) {
    for (int i = vertex + 1; i < graph.size(); ++i) {
        if (graph[vertex][i] == 1 && is_clique(graph, current_clique, i)) {
            current_clique.push_back(i);
            explore_clique(graph, i, current_clique, clique);
            current_clique.pop_back();
        }
    }

    if (current_clique.size() > clique.size()) {
        clique = current_clique;
    }
}

// Itera sobre todos os vértices para encontrar o clique máximo,
// chamando a função explore_clique para encontrar o clique máximo desse vértice
int find_max_clique(const vector<vector<int>>& graph, int &num_vertices) {
    vector<int> clique;
    vector<int> current_clique;

    for (int i = 0; i < num_vertices; ++i) {
        current_clique.push_back(i);
        explore_clique(graph, i, current_clique, clique);
        current_clique.pop_back();
    }

    return clique.size(); 
}

int main() {
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
