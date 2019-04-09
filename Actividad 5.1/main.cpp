#include "iostream"
#include "ListaEnlazada.h"
#include "cstdlib" // Para srand y rand
#include "ctime" // Para time()
#include "impresionListasEnlazadas.h"

using namespace std;


void main() {

	ListaEnlazada lista; // Lista con la que haremos las pruebas
	int n; // Tamaño de la lista

	srand(time(NULL));

	cout << "Introduce el numero de elementos de la lista: ";
	cin >> n;

	// Llenamos la lista con numeros aleatorios entre 20 y 40
	for (int i = 0; i < n; i++) {
		int numeroAleatorio = rand() % 21 + 20;
		lista.insertar(lista.getN(), numeroAleatorio); // Insertamos al final el número aleatorio
	}

	// Imprimimos la lista sin ordenar
	cout << "Lista sin ordenar: ";
	imprimirListaEnlazada(&lista);

	// Ordenamos e imprimimos
	lista.ordenar();
	cout << "Lista ordenada con MergeSort: ";
	imprimirListaEnlazada(&lista);
}


