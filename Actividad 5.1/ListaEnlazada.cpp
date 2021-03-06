#include "ListaEnlazada.h"
#include "cassert"
using namespace std;

Nodo * ListaEnlazada::getNodo (int posicion) {
	assert(n > 0);
	assert(posicion >= 0 && posicion <= n-1);

	Nodo *resultado = NULL; // Aqu� guardaremos el puntero al nodo resultado 
	
	// Si el nodo que queremos buscar es igual que el �ltimo accedido
	if (posicion == posicionUltimoNodoAccedido && posicionUltimoNodoAccedido!=-1) 
		resultado=punteroUltimoNodoAccedido;

	// Si el nodo que queremos buscar es el siguiente al �ltimo accedido
	else if (posicion == posicionUltimoNodoAccedido+1 && posicionUltimoNodoAccedido != -1) {
		resultado = punteroUltimoNodoAccedido->siguienteNodo;
	}

	// Si el nodo que queremos buscar es el anterior al �ltimo accedido
	else if (posicion == posicionUltimoNodoAccedido - 1 && posicionUltimoNodoAccedido != -1) {
		resultado = punteroUltimoNodoAccedido->anteriorNodo;
	}

	// Si el nodo no es contiguo al ultimo accedido, y se llega antes a �l iterando hacia delante	
	else if (posicion <= n / 2) {
		resultado = lista; // Hacemos que el resultado apunte al primer nodo
		for (int i = 0; i < posicion; i++) resultado = resultado->siguienteNodo;
	}

	// Si el nodo no es contiguo al ultimo accedido, y se llega antes a �l iterando hacia atr�s	
	else {
		resultado = lista->anteriorNodo; // Hacemos que el resultado apunte al �ltimo nodo
		for (int i = n-1; i > posicion; i--) 
			resultado = resultado->anteriorNodo;
	}

	// Actualizamos los atributos del ultimo nodo accedido
	posicionUltimoNodoAccedido = posicion;
	punteroUltimoNodoAccedido = resultado;

	return (resultado);
}


void ListaEnlazada::ordenarPorMergeSortRecursivo(ListaEnlazada *lista) {
	if (lista->getN() == 1)
		return;

	ListaEnlazada *lista1 = new ListaEnlazada;
	ListaEnlazada *lista2 = new ListaEnlazada;
	repartir(lista, lista1, lista2);
	
	ordenarPorMergeSortRecursivo(lista1);
	ordenarPorMergeSortRecursivo(lista2);

	combinar(lista1, lista2, lista);

	delete lista1;
	delete lista2;
}


void ListaEnlazada::repartir(ListaEnlazada* listaCompleta, ListaEnlazada* sublista1, ListaEnlazada* sublista2) {
	assert(listaCompleta != NULL && sublista1 != NULL && sublista2 != NULL);
	assert(listaCompleta->getN() >= 2);
	assert(sublista1->getN() == 0 && sublista2->getN() == 0);
	unsigned end = listaCompleta->getN();//Guarda longitud
	unsigned half = end / 2;//Calcula mitad

	for (unsigned i = 0; i < half; ++i) {
		sublista1->insertar(i, listaCompleta->getValor(0));//Rellena sublista1 con la primera mitad
		listaCompleta->eliminar(0);
	}
	for (unsigned i = half, j = 0; i < end; ++i, ++j) {
		sublista2->insertar(j, listaCompleta->getValor(0));//Rellena sublista2 con la segunda mitad
		listaCompleta->eliminar(0);
	}
}


void ListaEnlazada::combinar(ListaEnlazada* origen1, ListaEnlazada* origen2, ListaEnlazada* destino) {
	assert(origen1 != NULL && origen2 != NULL && destino != NULL);
	assert(origen1->getN() >= 1 && origen2->getN() >= 1);
	assert(destino->getN() == 0);
	assert(isOrdenada(origen1) && isOrdenada(origen2));

	while (origen1->getN() > 0 && origen2->getN() > 0) {
		if (origen1->getValor(0) < origen2->getValor(0)) {//Si el valor en origen1 < valor en origen2
			destino->insertar(destino->getN(), origen1->getValor(0));
			origen1->eliminar(0);
		}
		else {
			destino->insertar(destino->getN(), origen2->getValor(0));
			origen2->eliminar(0);
		}
	}

	while (origen1->getN() > 0) {
		destino->insertar(destino->getN(), origen1->getValor(0));
		origen1->eliminar(0);
	}

	while (origen2->getN() > 0) {
		destino->insertar(destino->getN(), origen2->getValor(0));
		origen2->eliminar(0);
	}
}


bool ListaEnlazada::isOrdenada(ListaEnlazada* lista) {
	assert(lista != NULL);
	
	if (lista->getN() <= 1)
		return true;

	int anterior = lista->getValor(0);
	for (unsigned i = 1; i < lista->getN(); ++i) {
		if (anterior > lista->getValor(i))//Si no est� ordenada
			return false;
		anterior = lista->getValor(i);
	}

	return true;
}


ListaEnlazada::ListaEnlazada() {
	lista = NULL; 
	n=0;
	posicionUltimoNodoAccedido = -1; // -1 significa que no se ha accedido aun a ninguno
	punteroUltimoNodoAccedido = NULL; // NULL significa que no se ha accedido aun a ninguno
}

int ListaEnlazada::getValor(int posicion) {
	assert(n > 0);
	assert (posicion >= 0 && posicion <= n-1); 
	// Obtenemos el nodo que contiene el elemento
	Nodo *nodoQueContieneResultado = getNodo (posicion);
	return (nodoQueContieneResultado->elemento);
}

void ListaEnlazada::setValor(int posicion, int nuevoValor) {
	assert(n > 0);
	assert (posicion >= 0 && posicion <= n-1); 
	getNodo(posicion)->elemento = nuevoValor;
}

int ListaEnlazada::getN() {
	return (n);
}

void ListaEnlazada::insertar (int posicion, int nuevoValor) {
	assert (posicion >= 0 && posicion <= n); 

	// Creamos el nuevo nodo con el nuevo valor
	Nodo *nuevoNodo = new Nodo;
	nuevoNodo->elemento = nuevoValor;

	// Si la lista estaba vacia...
	if (n==0) {
		nuevoNodo->siguienteNodo = nuevoNodo;
		nuevoNodo->anteriorNodo = nuevoNodo;
	}

	// Si la lista no est� vac�a
	else {
		// Primero obtenemos el nodo que est� a continuaci�n del que queremos insertar
		// Nota que, si queremos insertar al final, su siguiente es el primero
		Nodo *nodoSiguiente; // Nodo a continuaci�n del que queremos insertar
		if (posicion == n) nodoSiguiente = lista;
		else nodoSiguiente = getNodo(posicion);

		// Obtenemos el nodo anterior al que queremos insertar
		// Tengamos cuidado en hacerlo en O(1)
		Nodo *nodoAnterior = nodoSiguiente->anteriorNodo;

		// Actualizamos los punteros del nuevo nodo
		nuevoNodo->anteriorNodo=nodoAnterior;
		nuevoNodo->siguienteNodo=nodoSiguiente;

		// Actualizamos los punteros de los dos nodos que rodean al nuevo nodo
		// El puntero siguiente del anterior y el puntero anterior del siguiente apuntar�n ambos al nuevo nodo
		nodoSiguiente->anteriorNodo=nuevoNodo;
		nodoAnterior->siguienteNodo=nuevoNodo;
	} // Fin else
	
	// Si estamos insertando al principio de la lista, hay que modificar el puntero a la lista
	if (posicion == 0) lista = nuevoNodo;

	// Incrementamos el numero de elementos
	n++;

	// Como hemos cambiado la configuracion de la lista, reseteamos el ultimo nodo accedido
	posicionUltimoNodoAccedido = -1; // -1 significa que no se ha accedido aun a ninguno
	punteroUltimoNodoAccedido = NULL; // NULL significa que no se ha accedido aun a ninguno
}


void ListaEnlazada::eliminar (int posicion) {
	assert(n > 0);
	assert (posicion >= 0 && posicion <= n-1); 

	// Obtenemos el nodo que queremos eliminar
	Nodo *nodoAEliminar = getNodo(posicion);

	// Si la lista s�lo tiene un elemento, actualizamos el atributo lista pues la lista se queda vacia
	if (n == 1) lista = NULL;

	// Si la lista tiene m�s de un elemento, hacemos el caso general
	else {

		// Obtenemos los dos nodos que le rodean
		Nodo *nodoAnterior = nodoAEliminar->anteriorNodo;
		Nodo *nodoSiguiente = nodoAEliminar->siguienteNodo;
		
		// Modificamos los punteros de cada uno de los dos nodos que rodean al que queremos eliminar
		nodoAnterior->siguienteNodo=nodoSiguiente;
		nodoSiguiente->anteriorNodo=nodoAnterior;
		
		// Si el nodo a eliminar era el 0, tenemos que actualizar el atributo lista
		if (posicion == 0) lista = nodoSiguiente;
	} // Fin else

	// Liberamos la memoria del nodo
	delete nodoAEliminar;

	// Actualizamos n
	n--;

	// Como hemos cambiado la configuracion de la lista, reseteamos el ultimo nodo accedido
	posicionUltimoNodoAccedido = -1; // -1 significa que no se ha accedido aun a ninguno
	punteroUltimoNodoAccedido = NULL; // NULL significa que no se ha accedido aun a ninguno
}

void ListaEnlazada::concatenar(ListaEnlazada *listaAConcatenar) {
	assert(listaAConcatenar != NULL);

	// Tama�o de la lista a concatenar. Por convenci�n, cuando tenemos
	// dos listas, el tama�o de una es "n" y el de la otra es "m"
	int m = listaAConcatenar->getN();

	// Vamos insertando al final elemento a elemento. F�jate en que insertar un elemento al final
	// es O(1) porque la lista es circular, y por lo tanto podemos acceder al ultimo nodo en O(1)
	// si hemos hecho bien getNodo()
	// - Complejidad temporal O(m). Las sucesivas llamadas a listaAConcatenar->getValor(i) son O(1)
	//   porque getNodo() recuerda el �ltimo nodo accedido
	// - Complejidad espacial O(m), porque creamos m nodos nuevos
	for (int i = 0; i < m; i++) {
		int elementoACopiar = listaAConcatenar->getValor(i);
		insertar(n, elementoACopiar);
	}
}

int ListaEnlazada::buscar(int elementoABuscar) {
	int posicion = 0; // Posici�n actual en donde buscamos
	bool encontrado = false; // Nos indica si hemos encontrado o no el elemento

	// Buscamos el elemento hasta que lo encontremos o hasta que lleguemos al final
	while (!encontrado && posicion < n) {
		// Cada llamada a getValor() es O(1) porque getNodo() recuerda el �ltimo nodo accedido
		if (getValor(posicion) == elementoABuscar) encontrado = true;
		posicion++;
	}

	// Devolvemos la posici�n si lo hemos encontrado, o -1 en caso contrario
	if (encontrado) return (posicion - 1);
	else return (-1);
}


void ListaEnlazada::ordenar() {
	ordenarPorMergeSortRecursivo((this));
}


ListaEnlazada::~ListaEnlazada() {
	// Eliminamos el primer elemento de la lista. Esta operaci�n la repetimos n veces
	// Eliminar el primer elemento de la lista es O(1)
	while (n>0) eliminar(0);
}



