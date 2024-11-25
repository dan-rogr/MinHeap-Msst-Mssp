#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Clase template para un MinHeap genérico
template <typename T>
class MinHeap {
private:
    vector<T> array;  // Vector para almacenar los elementos del heap
    int size;         // Número actual de elementos en el heap
    int capacity;     // Capacidad máxima del heap

public:
    // Constructor para inicializar el MinHeap con una capacidad dada
    MinHeap(int capacity) {
        this->size = 0;          // El heap está vacío al principio
        this->capacity = capacity;  // La capacidad inicial
        this->array.resize(capacity); // Redimensiona el array a la capacidad inicial
    }
    
    // Método heapify para mantener la propiedad del MinHeap en el subárbol con raíz en i
    void heapify(int i) {
        int smallest = i;             // Asumimos que el nodo actual es el más pequeño
        int left = 2 * i + 1;         // Índice del hijo izquierdo
        int right = 2 * i + 2;        // Índice del hijo derecho
        
        // Si el hijo izquierdo existe y es más pequeño que el nodo actual, lo marcamos como el más pequeño
        if (left < size && array[left] < array[smallest])
            smallest = left;

        // Si el hijo derecho existe y es más pequeño que el nodo más pequeño encontrado, lo actualizamos
        if (right < size && array[right] < array[smallest])
            smallest = right;

        // Si el nodo más pequeño no es el nodo actual, intercambiamos y llamamos a heapify recursivamente
        if (smallest != i) {
            swap(array[i], array[smallest]);  
            heapify(smallest);                
        }
    }

    // Método para construir un MinHeap a partir de un array dado
    void buildHeap(const vector<T>& arr) {
        capacity = arr.size();  // Ajustamos la capacidad al tamaño del array
        size = capacity;        // Establecemos el tamaño
        array = arr;            // Copiamos el array al heap

        // Empezamos heapify desde el último nodo no hoja hacia la raíz
        for (int i = (size - 1) / 2; i >= 0; i--) {
            heapify(i);
        }
    }

    // Método para insertar un nuevo valor en el MinHeap
    void insertNode(T value) {
        if (size == capacity) {
            // Si el heap está lleno, duplicamos la capacidad
            capacity *= 2;
            array.resize(capacity);  // Redimensionamos el vector
        }

        size++;  // Aumentamos el tamaño
        int i = size - 1;  // La nueva posición será al final
        array[i] = value;  // Insertamos el nuevo valor

        // Ascendemos el nodo hasta mantener la propiedad del MinHeap
        while (i != 0 && array[(i - 1) / 2] > array[i]) {
            swap(array[i], array[(i - 1) / 2]);  // Intercambiamos con el padre
            i = (i - 1) / 2;  // Nos movemos hacia el padre
        }
    }

    // Método para obtener el valor mínimo (raíz) del MinHeap sin eliminarlo
    T peek() {
        if (size <= 0)
            return -1;  // Retorna -1 si el heap está vacío

        return array[0];  // Devuelve el valor mínimo (la raíz)
    }

    // Método para extraer el valor mínimo del MinHeap
    T extractMin() {
        if (size <= 0)
            return -1;  // Retorna -1 si el heap está vacío
        if (size == 1) {
            size--;  // Si solo hay un elemento, lo eliminamos
            return array[0];  // Devolvemos el único elemento
        }

        T root = array[0];  // Guardamos el valor mínimo
        array[0] = array[size - 1];  // Reemplazamos la raíz por el último nodo
        size--;  // Reducimos el tamaño

        heapify(0);  // Restauramos la propiedad del MinHeap desde la raíz
        return root;  // Devolvemos el valor mínimo extraído
    }

    // Método para eliminar un nodo con un valor específico del MinHeap
    void DeleteNode(T key) {
        int index = -1;
        // Buscamos el índice del nodo con el valor 'key'
        for (int i = 0; i < size; ++i) {
            if (array[i] == key) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Key not found" << endl;  // Si no se encuentra el nodo
            return;
        }

        // Si el nodo a eliminar está al final, solo reducimos el tamaño
        if (index == size - 1) {
            size--;
            return;
        }

        // Reemplazamos el nodo a eliminar con el último nodo y reducimos el tamaño
        array[index] = array[size - 1];
        size--;

        // Restauramos la propiedad del MinHeap desde el índice del nodo eliminado
        heapify(index);
    }

    // Método para imprimir el contenido del MinHeap
    void printHeap() const {
        for (int i = 0; i < size; ++i)
            cout << array[i] << " ";  // Imprime cada elemento del heap
        cout << endl;
    }
};
