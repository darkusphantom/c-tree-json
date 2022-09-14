#ifndef NODOARBOL_H
#define NODOARBOL_H

#include <iostream>
using namespace std;

template <class tipo>
class NodoArbol {
	private:
		tipo dato;
		NodoArbol<tipo> *hijoIzquierdo;
		NodoArbol<tipo> *hijoDerecho;

	public:
		//constructores
		NodoArbol();
		NodoArbol( tipo nuevoDato );
		~NodoArbol();

		//metodos
		bool esNulo();//indica si el nodo es nulo o no
		void modificarDato( tipo nuevoDato );//modifica el dato del nodo por uno nuevo ingresado
		NodoArbol<tipo> *obtenerHijoIzquierdo();//retorna el nodo del hijo izquierdo
		NodoArbol<tipo> *obtenerHijoDerecho();//retorna el nodo del hijo derecho
		void modificarHijoIzquierdo( tipo nuevoDato );//modifica el dato del hijo izquierdo 
		void modificarHijoDerecho( tipo nuevoDato );//modifica el dato del hijo derecho
		tipo obtenerDato();//retorna el dato del nodo
};

template <class tipo>
NodoArbol<tipo>::NodoArbol() {
	this->hijoIzquierdo = NULL;
	this->hijoDerecho = NULL;
}

template <class tipo>
NodoArbol<tipo>::NodoArbol( tipo nuevoDato ) {
	this->dato = nuevoDato;
	this->hijoIzquierdo = new NodoArbol<tipo>();
	this->hijoDerecho = new NodoArbol<tipo>();
}

template <class tipo>
NodoArbol<tipo>::~NodoArbol() {
	delete this;
}

template <class tipo>
bool NodoArbol<tipo>::esNulo() {
	return( this->hijoIzquierdo == NULL && this->hijoDerecho == NULL );
}

template <class tipo>
void NodoArbol<tipo>::modificarDato( tipo nuevoDato ) {
	this->dato = nuevoDato;

	if( this->hijoIzquierdo == NULL || this->hijoDerecho == NULL ) {
		this->hijoIzquierdo = new NodoArbol<tipo>();
		this->hijoDerecho = new NodoArbol<tipo>();
	}
}

template <class tipo>
NodoArbol<tipo> *NodoArbol<tipo>::obtenerHijoIzquierdo() {
	return( this->hijoIzquierdo );
}

template <class tipo>
NodoArbol<tipo> *NodoArbol<tipo>::obtenerHijoDerecho() {
	return( this->hijoDerecho );
}

template <class tipo>
void NodoArbol<tipo>::modificarHijoIzquierdo( tipo nuevoDato ) {
	NodoArbol<tipo> *nodo = this->hijoIzquierdo;
	nodo->modificarDato( nuevoDato );
}

template <class tipo>
void NodoArbol<tipo>::modificarHijoDerecho( tipo nuevoDato ) {
	NodoArbol<tipo> *nodo = this->hijoDerecho;
	nodo->modificarDato( nuevoDato );
}

template <class tipo>
tipo NodoArbol<tipo>::obtenerDato() {
	return( this->dato );
}

//template <class tipo>
//template <class tipo>

//****************************************************************************************
//**********************************private***********************************************
//****************************************************************************************

#endif 
