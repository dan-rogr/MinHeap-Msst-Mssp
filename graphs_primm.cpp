#include <iostream>
using namespace std;


class Graph {
private:
    int vertices;         
    int** adjMatrix;      

public:

    Graph(int vertices) : vertices(vertices) {
        adjMatrix = new int*[vertices];
        for (int i = 0; i < vertices; ++i) {
            adjMatrix[i] = new int[vertices];
            for (int j = 0; j < vertices; ++j) {
                adjMatrix[i][j] = 0;
            }
        }
    }

    ~Graph() {
        for (int i = 0; i < vertices; ++i) {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
    }

    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight; 
    }

    void primMST() {
        int* parent = new int[vertices];      
        int* key = new int[vertices];        
        bool* inMST = new bool[vertices];    

        for (int i = 0; i < vertices; ++i) {
            key[i] = 1e9;  
            inMST[i] = false;
        }

        key[0] = 0;      
        parent[0] = -1;   

        for (int count = 0; count < vertices - 1; ++count) {
            int minKey = 1e9, u;
            for (int v = 0; v < vertices; ++v) {
                if (!inMST[v] && key[v] < minKey) {
                    minKey = key[v];
                    u = v;
                }
            }
            inMST[u] = true;
            for (int v = 0; v < vertices; ++v) {
                if (adjMatrix[u][v] && !inMST[v] && adjMatrix[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = adjMatrix[u][v];
                }
            }
        }

        for (int i = 1; i < vertices; ++i) {
            cout << "Edge: " << parent[i] << " - " << i << ", Weight: " << adjMatrix[i][parent[i]] << endl;
        }

        delete[] parent;
        delete[] key;
        delete[] inMST;
    }
};

int main() {
    int vertices = 5;
    Graph g(vertices);

    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    g.primMST();

    return 0;
}
