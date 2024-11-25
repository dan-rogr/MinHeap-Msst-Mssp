#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// Clase template para representar una lista enlazada
template <typename T>
class LinkedList {
private:
    // Nodo que representa cada elemento de la lista con su valor y peso
    class Node {
    public:
        T data;    // Valor del nodo
        int weight; // Peso de la arista (en caso de ser un grafo ponderado)
        Node* next; // Apuntador al siguiente nodo en la lista

        // Constructor que inicializa el nodo con un valor y peso
        Node(T value, int w) : data(value), weight(w), next(nullptr) {}
    };

    Node* first; // Primer nodo de la lista
    unsigned int size; // Tama�o de la lista

public:
    // Constructor que inicializa la lista vac�a
    LinkedList() : first(nullptr), size(0) {}

    // M�todo para agregar un nodo al final de la lista
    void addEdge(T element, int weight) {
        Node* newNode = new Node(element, weight); // Creamos el nuevo nodo
        if (!first) {
            first = newNode; // Si la lista est� vac�a, el nuevo nodo es el primero
        } else {
            Node* temp = first;
            // Recorremos la lista hasta el final
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode; // A�adimos el nuevo nodo al final
        }
        size++; // Aumentamos el tama�o de la lista
    }

    // M�todo para obtener la lista de adyacencia de un nodo
    void getAdjacencyList(pair<int, int>* adjList, int& count) const {
        Node* temp = first;
        count = 0; // Contador de nodos vecinos
        // Recorremos la lista enlazada y llenamos el array de adyacencia
        while (temp) {
            adjList[count++] = {temp->data, temp->weight};
            temp = temp->next;
        }
    }

    // Destructor para liberar la memoria de los nodos
    ~LinkedList() {
        Node* temp;
        while (first) {
            temp = first;
            first = first->next;
            delete temp; // Eliminamos los nodos uno por uno
        }
    }
};

// Clase template para representar un grafo
template <typename T>
class Graph {
private:
    LinkedList<T>* adjLists; // Arreglo de listas enlazadas para las listas de adyacencia
    int vertices; // N�mero de v�rtices en el grafo

public:
    // Constructor que inicializa el grafo con un n�mero dado de v�rtices
    Graph(int V) : vertices(V) {
        adjLists = new LinkedList<T>[V]; // Creamos un arreglo de listas enlazadas
    }

    // M�todo para agregar una arista entre los v�rtices u y v con un peso
    void addEdge(T u, T v, int weight) {
        if (u < vertices && v < vertices) {
            adjLists[u].addEdge(v, weight); // Agregamos una arista de u a v
        }
    }

    // M�todo para imprimir el grafo como una lista de adyacencia
    void printGraph() const {
        cout << "Graph adjacency list:" << endl;
        for (int i = 0; i < vertices; ++i) {
            cout << "Node " << i << ": ";
            pair<int, int> adjList[vertices]; // Array temporal para almacenar la lista de adyacencia
            int count = 0; // Contador de los vecinos
            adjLists[i].getAdjacencyList(adjList, count);

            if (count == 0) {
                cout << "No neighbors" << endl; // Si no tiene vecinos
            } else {
                for (int j = 0; j < count; ++j) {
                    cout << "(Node: " << adjList[j].first << ", weight: " << adjList[j].second << ") ";
                }
                cout << endl;
            }
        }
    }

    // M�todo para convertir el grafo a una matriz de adyacencia
    vector<vector<int>> toAdjMatrix() const {
        const int INF = numeric_limits<int>::max(); // Usamos INF para representar la ausencia de conexi�n
        vector<vector<int>> adjMatrix(vertices, vector<int>(vertices, INF)); // Matriz de adyacencia inicializada con INF

        // Recorremos cada v�rtice y sus adyacentes para llenar la matriz
        for (int i = 0; i < vertices; ++i) {
            adjMatrix[i][i] = 0; // La distancia a s� mismo es 0
            pair<int, int> adjList[vertices];
            int count = 0;
            adjLists[i].getAdjacencyList(adjList, count);

            for (int j = 0; j < count; ++j) {
                int neighbor = adjList[j].first;
                int weight = adjList[j].second;
                adjMatrix[i][neighbor] = weight; // Establecemos el peso de la arista
            }
        }

        return adjMatrix; // Devolvemos la matriz de adyacencia
    }

    // M�todo para resolver el problema de las distancias m�s cortas desde m�ltiples fuentes usando Bellman-Ford
    void solveMSSP(const vector<int>& sources) {
        const int INF = numeric_limits<int>::max();

        // Inicializamos la matriz de distancias con infinito
        vector<vector<int>> distances(vertices, vector<int>(vertices, INF));

        // Recolectamos las aristas del grafo
        for (int source : sources) {
            distances[source][source] = 0;  // Distancia desde la fuente a s� misma es 0

            // Recolectamos las aristas del nodo 'source'
            for (int u = 0; u < vertices; ++u) {
                pair<int, int> adjList[vertices];  // Arreglo para guardar los vecinos y pesos
                int count = 0;  // Variable para contar el n�mero de vecinos
                adjLists[u].getAdjacencyList(adjList, count);  // Llamada correcta a getAdjacencyList

                //Recorrer las aristas de vecinos
                for (int i = 0; i < count; ++i) {
                    int v = adjList[i].first;  // Nodo vecino
                    int weight = adjList[i].second;  // Peso de la arista
                    // Relajamos la arista (u, v)
                    if (distances[source][u] != INF && distances[source][u] + weight < distances[source][v]) {
                        distances[source][v] = distances[source][u] + weight;
                    }
                }
            }
        }

        // Imprimimos la matriz de distancias m�s cortas
        cout << "MSSP Distance Matrix:" << endl;
        for (const auto& row : distances) {
            for (int val : row) {
                if (val == INF) cout << "INF ";
                else cout << val << " ";
            }
            cout << endl;
        }
    }

    // Destructor para liberar la memoria del grafo
    ~Graph() {
        delete[] adjLists; // Eliminamos el arreglo de listas de adyacencia
    }
};
