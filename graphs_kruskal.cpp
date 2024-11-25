#include <iostream>
using namespace std;

// Estructura para representar una arista
struct Edge {
    int u, v, weight;
};

// Clase para representar el grafo
class Graph {
private:
    int vertices, edgesCount;
    Edge* edges; // Lista de aristas
    int edgeIndex;

    int* parent; // Conjuntos disjuntos
    int* rank;   // Rango para optimizar union-find

    // Método para encontrar el representante de un conjunto
    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]); // Compresión de caminos
        }
        return parent[u];
    }

    // Método para unir dos conjuntos
    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }

public:
    // Constructor para inicializar el grafo
    Graph(int vertices, int edgesCount) : vertices(vertices), edgesCount(edgesCount) {
        edges = new Edge[edgesCount];
        edgeIndex = 0;

        parent = new int[vertices];
        rank = new int[vertices];
        for (int i = 0; i < vertices; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    // Destructor para liberar memoria
    ~Graph() {
        delete[] edges;
        delete[] parent;
        delete[] rank;
    }

    // Método para agregar una arista al grafo
    void addEdge(int u, int v, int weight) {
        edges[edgeIndex++] = {u, v, weight};
    }

    // Implementación del algoritmo de Kruskal
    void kruskalMST() {
        // Ordenar las aristas por peso usando un método manual (burbuja)
        for (int i = 0; i < edgesCount - 1; ++i) {
            for (int j = 0; j < edgesCount - i - 1; ++j) {
                if (edges[j].weight > edges[j + 1].weight) {
                    Edge temp = edges[j];
                    edges[j] = edges[j + 1];
                    edges[j + 1] = temp;
                }
            }
        }

        Edge* mst = new Edge[vertices - 1]; // Aristas del MST
        int mstIndex = 0;

        // Procesar las aristas en orden ascendente de peso
        for (int i = 0; i < edgesCount; ++i) {
            if (find(edges[i].u) != find(edges[i].v)) {
                mst[mstIndex++] = edges[i];
                unionSets(edges[i].u, edges[i].v);

                if (mstIndex == vertices - 1) {
                    break; // Se ha formado el MST
                }
            }
        }

        // Imprimir el MST
        for (int i = 0; i < mstIndex; ++i) {
            cout << "Edge: " << mst[i].u << " - " << mst[i].v << ", Weight: " << mst[i].weight << endl;
        }

        delete[] mst; // Liberar memoria
    }
};

// Programa principal para probar la clase Graph y el algoritmo de Kruskal
int main() {
    int vertices = 5;
    int edgesCount = 7;
    Graph g(vertices, edgesCount);

    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    g.kruskalMST();

    return 0;
}
