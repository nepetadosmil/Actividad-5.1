#include "impresionListasEnlazadas.h"
#include "cassert"
#include "iostream"
using namespace std;

void imprimirListaEnlazada(ListaEnlazada *lista) {
	assert(lista != NULL);

	int tamanio = lista->getN();

	// Imprimimos tamaño
	cout << "n=" << tamanio << "|ListaEnlazada=";

	// Si la lista está vacía, imprimimos algo especial
	if (tamanio == 0) cout << "vacia";

	// Si no está vacía, imprimimos los elementos separados por comas, siempre que no sea demasiado grande
	// Si es demasiado grande, imprimimos un mensaje especial
	else {
		if (tamanio > 20) cout << "demasiadosElementosParaMostrar";
		else {
			for (int i = 0; i < tamanio; i++) {
				cout << lista->getValor(i);
				if (i < tamanio - 1) cout << ","; // Imprimimos "," si no estamos al final
			}
		}
	}
	cout << endl;
}
