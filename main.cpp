// =================================================================
//
// File: main.cpp
// Author: Ricardo Sierra Roa - A01709887
// Date: 03/11/2023
//
// =================================================================

// Librerias
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>

using namespace std;

vector<vector<int>> adj;
vector<bool> visited;

// =================================================================
// Función DFS para encontrar componentes conexas
//
// @param u vertice inicial del grafo que se va a explorar
// @return void
// @Complexity	O(V + E)
// =================================================================
void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
}

// =================================================================
// Funcion para contar arboles y bellotas en un grafo
//
// @param vector<string>, string, el vector de strings, el cual 
// contiene los pares de letras que se utilizaran para construir el 
// grafo para contar los abroles y el string contiene de manera 
// individual las letras utilizadas en el grafo para contar las bellotas
// @return pair<int, int>, numero de arboles y bellotas contadas
// @Complexity	O(E + V + V log V)
// =================================================================
pair<int, int> countTreeAcorn(const vector<string>& edges, const string& line) {
    int numTrees = 0;
    int numAcorns = 0;

    // Crear un conjunto para almacenar todos los nodos del grafo
    set<int> graphNodes;
    // Crear un conjunto para almacenar todos los nodos a partir de la variable 'line'
    set<char> allNodes;

    set<int> vertices;
    for (const string& edge : edges) {
        char u = edge[1];
        char v = edge[3];
        vertices.insert(u - 'A');
        vertices.insert(v - 'A');
    }

    int n = 26; // Suponemos que hay 26 vertices (A..Z)
    adj.resize(n);
    visited.resize(n, false);

    for (int i = 0; i < n; i++) {
        adj[i].clear();
    }

    // Construir el grafo a partir de las aristas proporcionadas
    for (const string& edge : edges) {
        char u = edge[1];
        char v = edge[3];
        int uIndex = u - 'A';
        int vIndex = v - 'A';
        graphNodes.insert(uIndex);
        graphNodes.insert(vIndex);
        adj[uIndex].push_back(vIndex);
        adj[vIndex].push_back(uIndex);
    }

    // Dividir la cadena en tokens usando comas como delimitador
    istringstream iss(line);
    string token;

    while (getline(iss, token, ',')) {
        for (char c : token) {
            if (isalpha(c)) {
                allNodes.insert(c);
            }
        }
    }

    // Encontrar componentes conexos en el grafo igual al conteo de los arboles
    for (int u : vertices) {
        if (!visited[u]) {
            dfs(u);
            numTrees++;
        }
    }

    // Iterar a traves del alfabeto y contar los vertices que no estan en 'graphNodes' pero estan en 'allNodes' igual al conteo de bellotas
    for (char c = 'A'; c <= 'Z'; c++) {
        int nodeIndex = c - 'A';
        if (graphNodes.find(nodeIndex) == graphNodes.end() && allNodes.find(c) != allNodes.end()) {
            numAcorns++;
        }
    }

    return make_pair(numTrees, numAcorns);
}

int main() {
    string line;
    vector<string> edges;
    
    while (getline(cin, line)) {
        if (line == "****") {
            // Fin de la lista de aristas
            break;
        }
        edges.push_back(line);
    }

    getline(cin, line); // Leer la linea despues de los asteriscos, lista de puntos de los arboles

    pair<int, int> results = countTreeAcorn(edges, line);

    cout << "There are " << results.first << " tree(s) and " << results.second << " acorn(s)." << endl;

    return 0;
}