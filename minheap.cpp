#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Clase template para un MinHeap gen�rico
template <typename T>
class MinHeap {
private:
    vector<T> array;  // Vector para almacenar los elementos del heap
    int size;         // N�mero actual de elementos en el heap
    int capacity;     // Capacidad m�xima del heap

public:
    // Constructor para inicializar el MinHeap con una capacidad dada
    MinHeap(int capacity) {
        this->size = 0;          // El heap est� vac�o al principio
        this->capacity = capacity;  // La capacidad inicial
        this->array.resize(capacity); // Redimensiona el array a la capacidad inicial
    }
    
    // M�todo heapify para mantener la propiedad del MinHeap en el sub�rbol con ra�z en i
    void heapify(int i) {
        int smallest = i;             // Asumimos que el nodo actual es el m�s peque�o
        int left = 2 * i + 1;         // �ndice del hijo izquierdo
        int right = 2 * i + 2;        // �ndice del hijo derecho
        
        // Si el hijo izquierdo existe y es m�s peque�o que el nodo actual, lo marcamos como el m�s peque�o
        if (left < size && array[left] < array[smallest])
            smallest = left;

        // Si el hijo derecho existe y es m�s peque�o que el nodo m�s peque�o encontrado, lo actualizamos
        if (right < size && array[right] < array[smallest])
            smallest = right;

        // Si el nodo m�s peque�o no es el nodo actual, intercambiamos y llamamos a heapify recursivamente
        if (smallest != i) {
            swap(array[i], array[smallest]);  
            heapify(smallest);                
        }
    }

    // M�todo para construir un MinHeap a partir de un array dado
    void buildHeap(const vector<T>& arr) {
        capacity = arr.size();  // Ajustamos la capacidad al tama�o del array
        size = capacity;        // Establecemos el tama�o
        array = arr;            // Copiamos el array al heap

        // Empezamos heapify desde el �ltimo nodo no hoja hacia la ra�z
        for (int i = (size - 1) / 2; i >= 0; i--) {
            heapify(i);
        }
    }

    // M�todo para insertar un nuevo valor en el MinHeap
    void insertNode(T value) {
        if (size == capacity) {
            // Si el heap est� lleno, duplicamos la capacidad
            capacity *= 2;
            array.resize(capacity);  // Redimensionamos el vector
        }

        size++;  // Aumentamos el tama�o
        int i = size - 1;  // La nueva posici�n ser� al final
        array[i] = value;  // Insertamos el nuevo valor

        // Ascendemos el nodo hasta mantener la propiedad del MinHeap
        while (i != 0 && array[(i - 1) / 2] > array[i]) {
            swap(array[i], array[(i - 1) / 2]);  // Intercambiamos con el padre
            i = (i - 1) / 2;  // Nos movemos hacia el padre
        }
    }

    // M�todo para obtener el valor m�nimo (ra�z) del MinHeap sin eliminarlo
    T peek() {
        if (size <= 0)
            return -1;  // Retorna -1 si el heap est� vac�o

        return array[0];  // Devuelve el valor m�nimo (la ra�z)
    }

    // M�todo para extraer el valor m�nimo del MinHeap
    T extractMin() {
        if (size <= 0)
            return -1;  // Retorna -1 si el heap est� vac�o
        if (size == 1) {
            size--;  // Si solo hay un elemento, lo eliminamos
            return array[0];  // Devolvemos el �nico elemento
        }

        T root = array[0];  // Guardamos el valor m�nimo
        array[0] = array[size - 1];  // Reemplazamos la ra�z por el �ltimo nodo
        size--;  // Reducimos el tama�o

        heapify(0);  // Restauramos la propiedad del MinHeap desde la ra�z
        return root;  // Devolvemos el valor m�nimo extra�do
    }

    // M�todo para eliminar un nodo con un valor espec�fico del MinHeap
    void DeleteNode(T key) {
        int index = -1;
        // Buscamos el �ndice del nodo con el valor 'key'
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

        // Si el nodo a eliminar est� al final, solo reducimos el tama�o
        if (index == size - 1) {
            size--;
            return;
        }

        // Reemplazamos el nodo a eliminar con el �ltimo nodo y reducimos el tama�o
        array[index] = array[size - 1];
        size--;

        // Restauramos la propiedad del MinHeap desde el �ndice del nodo eliminado
        heapify(index);
    }

    // M�todo para imprimir el contenido del MinHeap
    void printHeap() const {
        for (int i = 0; i < size; ++i)
            cout << array[i] << " ";  // Imprime cada elemento del heap
        cout << endl;
    }
};
