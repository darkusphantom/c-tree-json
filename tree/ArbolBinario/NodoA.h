#ifndef NODOA_H
#define NODOA_H

#include <iostream>

using namespace std;

template <class type>
class NodoA {
	private:
		type dato;
		NodoA<type>* hijoIzquierdo;
		NodoA<type>* hijoDerecho;

	public:
		NodoA();
		NodoA( type nuevoDato );
		NodoA( type nuevoDato, NodoA<type>* nuevoHijoIzquierdo, NodoA<type>* nuevoHijoDerecho );
		~NodoA();

		//metodos
		type obtenerDato();
		void modificarDato( type nuevoDato );
		NodoA<type>* obtenerHijoIzquierdo();
		NodoA<type>* obtenerHijoDerecho();
		void modificarHijoIzquierdo( NodoA<type>* nuevoHijoIzquierdo );
		void modificarHijoDerecho( NodoA<type>* nuevoHijoDerecho );
		bool isLeaf();//indica si el nodo es una hoja
		NodoA<type> *newNode(int dato);
};

template <class type>
NodoA<type>::NodoA() {
	this->hijoIzquierdo = NULL;
	this->hijoDerecho = NULL;
}

template <class type>
NodoA<type>::NodoA( type nuevoDato ) {
	this->dato = nuevoDato;
	this->hijoIzquierdo = NULL;
	this->hijoDerecho = NULL;
}

template <class type>
NodoA<type>::NodoA( type nuevoDato, NodoA<type>* nuevoHijoIzquierdo, NodoA<type>* nuevoHijoDerecho ) {
	this->dato = nuevoDato;
	this->hijoIzquierdo = nuevoHijoIzquierdo;
	this->hijoDerecho = nuevoHijoDerecho;
}

template <class type>
NodoA<type>::~NodoA() {
	this->hijoDerecho = NULL;
	this->hijoIzquierdo = NULL;
}

template <class type>
type NodoA<type>::obtenerDato() {
	return( this->dato );
}

template <class type>
void NodoA<type>::modificarDato( type nuevoDato ) {
	this->dato = nuevoDato;
}

template <class type>
NodoA<type>* NodoA<type>::obtenerHijoIzquierdo() {
	return( this->hijoIzquierdo );
}

template <class type>
NodoA<type>* NodoA<type>::obtenerHijoDerecho() {
	return( this->hijoDerecho );
}

template <class type>
void NodoA<type>::modificarHijoIzquierdo( NodoA<type>* nuevoHijoIzquierdo ) {
	this->hijoIzquierdo = nuevoHijoIzquierdo;
}

template <class type>
void NodoA<type>::modificarHijoDerecho( NodoA<type>* nuevoHijoDerecho ) {
	this->hijoDerecho = nuevoHijoDerecho;
}

template <class type>
bool NodoA<type>::isLeaf() {
	return( this->hijoIzquierdo == NULL && this->hijoDerecho == NULL );
}

/*template <class type>
NodoA<type>* newNode(int dato) {
	NodoA<type>* temp = new NodoA<type>();
	temp->dato = dato;
	temp->hijoIzquierdo = temp->hijoDerecho = NULL;
	return temp;
}*/

template <class type>
NodoA<type>* LCA(NodoA<type>* root, int n1, int n2) {
    if (root == NULL)
        return root;
    if (root->obtenerDato() == n1 || root->obtenerDato() == n2)
        return root;
 
    NodoA<type>* leftChildren = LCA(root->obtenerHijoDerecho(), n1, n2);
    NodoA<type>* rightChildren = LCA(root->obtenerHijoIzquierdo(), n1, n2);
 
    if (leftChildren != NULL && rightChildren != NULL)
        return root;
    if (leftChildren == NULL && rightChildren == NULL)
        return NULL;
    if (leftChildren != NULL)
        return LCA(root->obtenerHijoIzquierdo(), n1, n2);
 
    return LCA(root->obtenerHijoDerecho(), n1, n2);
}

#endif
