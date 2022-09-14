#ifndef ARBOLNARIO_H
#define ARBOLNARIO_H

#include <iostream>
#include "NodoArbol.h"
#include <list>

using namespace std;
using std::list;

template <class tipo>
class ArbolNario {
	private:
		NodoArbol<tipo> *raiz;

	public:
		ArbolNario();
		ArbolNario( tipo nuevoDato );
		ArbolNario( ArbolNario<tipo> *arbolOriginal );
		~ArbolNario();
		
		//metodos
		bool esVacia();//indica si el arbol es vacio
		bool esHoja();//indica si el arbol es una hoja
		tipo obtenerRaiz();//devuelve el dato raiz del arbol
		void insertarHijoIzquierdo( tipo padre, tipo NuevoDato );//inserta un hijo izquierdo en el arbol
		void insertarHermanoDerecho( tipo padre, tipo NuevoDato );//inserta un hermano derecho en el arbol
		void preorden( list<tipo> *listaPreorden );//genera una lista con un recorrido en preorden
		void postorden( list<tipo> *listaPostorden );//genera una lista con un recorrido postorden del arbol
		void inorden( list<tipo> *listaInorden );//genera una lista con un recorrido en inorden del arbol
		int diametro();//retorna el diametro del arbol
		void vaciar();//elimina todos los elemnetos del arbol
		void copiar( ArbolNario<tipo> *arbolOriginal );//copia un arbol existente

	private:
		NodoArbol<tipo> *buscarNodo( NodoArbol<tipo> *nodoRaiz , tipo elementoBuscado, bool *encontrado );//busca en el arbol el 'elemento' espcificado y devuelve en nodo correspondiente
		NodoArbol<tipo> *buscarUltimoHermano( NodoArbol<tipo> *nodoRaiz );//busca el ultimo hermano derecho de un nodo
		void preorden( list<tipo> *listaPreorden, NodoArbol<tipo> *nodoRaiz );
		void postorden( list<tipo> *listaPostorden, NodoArbol<tipo> *nodoRaiz );
		void inorden( list<tipo> *listaInorden, NodoArbol<tipo> *nodoRaiz );
		void diametro( NodoArbol<tipo> *nodoRaiz, int *diametro );
		void altura( NodoArbol<tipo> *nodoRaiz, int alturaActual, int *altura );//retorna la altura de un arbol
		void vaciar( NodoArbol<tipo> *nodoRaiz );
		void copiar( NodoArbol<tipo> *nodoOriginal, NodoArbol<tipo> *nodoCopia );
		NodoArbol<tipo> *obtenerNodoRaiz();//retorna  el nodo raiz del arbol
};

template <class tipo>
ArbolNario<tipo>::ArbolNario()
{
	this->raiz = new NodoArbol<tipo>();
}

template <class tipo>
ArbolNario<tipo>::ArbolNario( tipo nuevoDato )
{
	this->raiz = new NodoArbol<tipo>( nuevoDato );
}

template <class tipo>
ArbolNario<tipo>::ArbolNario( ArbolNario<tipo>* arbolOriginal )
{
	this->raiz = new NodoArbol<tipo>();

	this->copiar( arbolOriginal->raiz, this->raiz );
}

template <class tipo>
ArbolNario<tipo>::~ArbolNario()
{
	this->vaciar( this->raiz );
}

template <class tipo>
bool ArbolNario<tipo>::esVacia()
{
	return( this->raiz->esNulo() );
}

template <class tipo>
bool ArbolNario<tipo>::esHoja()
{
	bool respuesta = true;

	if ( !this->esVacia() )
	{
		NodoArbol<tipo> *hijo = this->raiz->obtenerHijoIzquierdo();

		NodoArbol<tipo> *hermano = this->raiz->obtenerHijoDerecho();

		respuesta = hijo->esNulo() && hermano->esNulo();
	}

	return( respuesta );
}

template <class tipo>
tipo ArbolNario<tipo>::obtenerRaiz()
{
	return( this->raiz->obtenerDato() );
}

template <class tipo>
void ArbolNario<tipo>::insertarHijoIzquierdo( tipo padre, tipo nuevoDato )
{
	if ( !this->esVacia() )
	{
		bool encontrado = false;

		NodoArbol<tipo> *nodo = this->buscarNodo( this->raiz, padre, &encontrado );
		
		nodo->modificarHijoIzquierdo( nuevoDato );
	}
}

template <class tipo>
void ArbolNario<tipo>::insertarHermanoDerecho( tipo padre, tipo nuevoDato )
{
	if ( !this->esVacia() )
	{
		bool encontrado = false;

		//se busca el nodo padre
		NodoArbol<tipo> *nodo = this->buscarNodo( this->raiz, padre, &encontrado );

		//sebusca el nodo vacio despues del ultimo hermano derecho
		nodo = this->buscarUltimoHermano( nodo );
		
		//se modifica el nodo vacio
		nodo->modificarDato( nuevoDato );
	}
}

template <class tipo>
void ArbolNario<tipo>::preorden( list<tipo> *listaPreorden )
{
	if ( !this->esVacia() )
	{
		this->preorden( &*listaPreorden, this->raiz );
	}
}

template <class tipo>
void ArbolNario<tipo>::postorden( list<tipo> *listaPostorden )
{
	if ( !this->esVacia() )
	{
		this->postorden( &*listaPostorden, this->raiz );
	}
}

template <class tipo>
void ArbolNario<tipo>::inorden( list<tipo> *listaInorden )
{
	if ( !this->esVacia() )
	{
		this->inorden( &*listaInorden, this->raiz );
	}
}

template <class tipo>
int ArbolNario<tipo>::diametro()
{
	int diametro = -1;

	if ( !this->esVacia() )
	{
		this->diametro( this->raiz , &diametro );
	}

	return( diametro );
}

template <class tipo>
void ArbolNario<tipo>::vaciar()
{
	if ( !this->esVacia() )
	{
		this->vaciar( this->raiz );

		this->raiz = new NodoArbol<tipo>();
	}
}

template <class tipo>
void ArbolNario<tipo>::copiar( ArbolNario<tipo> *arbolOriginal )
{
	if ( !arbolOriginal->esVacia() )
	{
		this->copiar( arbolOriginal->raiz, this->raiz );
	}
}

//****************************************************************************************
//**********************************private***********************************************
//****************************************************************************************

template <class tipo>
NodoArbol<tipo> *ArbolNario<tipo>::buscarNodo( NodoArbol<tipo> *nodoRaiz, tipo elementoBuscado, bool *encontrado )
{
	NodoArbol<tipo> *nodoBuscado;

	//se comprueba que el nodo actual no este vacio y que el elemento no halla sido encontrado
	if( !nodoRaiz->esNulo() && !*encontrado )
	{
		//se comprueba que el nodo actual no posea el elemento solicitado
		if ( nodoRaiz->obtenerDato() == elementoBuscado )
		{
			nodoBuscado = nodoRaiz;

			*encontrado = true;
		}
		else//si no lo posee se buscan en el hijo izquierdo y luego en los hermanos derechos
		{
			nodoBuscado = this->buscarNodo( nodoRaiz->obtenerHijoIzquierdo(), elementoBuscado, &*encontrado );

			nodoBuscado = this->buscarNodo( nodoRaiz->obtenerHijoDerecho(), elementoBuscado, &*encontrado );
		}
	}

	return( nodoBuscado );
}

template <class tipo>
NodoArbol<tipo>* ArbolNario<tipo>::buscarUltimoHermano( NodoArbol<tipo>* nodoRaiz )
{
	NodoArbol<tipo>* nodoBuscado = NULL;

	//se comprueba si llegamos al final de los hermanos derechos
	if( nodoRaiz->esNulo() )
	{
		nodoBuscado = nodoRaiz;
	}
	else//si no es el final de los hermanos derecho se prosigue al siguiente nodo
	{
		nodoBuscado = this->buscarUltimoHermano( nodoRaiz->obtenerHijoDerecho() );
	}

	return( nodoBuscado );
}

template <class tipo>
void ArbolNario<tipo>::preorden( list<tipo> *listaPreorden, NodoArbol<tipo> *nodoRaiz )
{
	if ( !nodoRaiz->esNulo() )
	{
		(*listaPreorden).push_back( nodoRaiz->obtenerDato() );

		this->preorden( &*listaPreorden, nodoRaiz->obtenerHijoIzquierdo() );

		this->preorden( &*listaPreorden, nodoRaiz->obtenerHijoDerecho() );
	}
}

template <class tipo>
void ArbolNario<tipo>::postorden( list<tipo> *listaPostorden, NodoArbol<tipo> *nodoRaiz )
{
	if ( !nodoRaiz->esNulo() )
	{
		this->postorden( &*listaPostorden, nodoRaiz->obtenerHijoIzquierdo() );

		this->postorden( &*listaPostorden, nodoRaiz->obtenerHijoDerecho() );

		(*listaPostorden).push_back( nodoRaiz->obtenerDato() );
	}
}

template <class tipo>
void ArbolNario<tipo>::inorden( list<tipo> *listaInorden, NodoArbol<tipo> *nodoRaiz )
{
	if ( !nodoRaiz->esNulo() )
	{
		this->inorden( &*listaInorden, nodoRaiz->obtenerHijoIzquierdo() );

		(*listaInorden).push_back( nodoRaiz->obtenerDato() );

		this->inorden( &*listaInorden, nodoRaiz->obtenerHijoDerecho() );
	}
}

template <class tipo>
void ArbolNario<tipo>::diametro( NodoArbol<tipo> *nodoRaiz, int *diametro )
{
	if ( !nodoRaiz->esNulo() )
	{
		int alturaIzquierda = 0;
		int alturaDerecha = 0;

		this->altura( nodoRaiz->obtenerHijoIzquierdo(), 1, &alturaIzquierda );

		this->altura( nodoRaiz->obtenerHijoDerecho(), 1, &alturaDerecha );

		if ( (alturaDerecha + alturaDerecha +1 ) > *diametro )
		{
			*diametro = alturaIzquierda + alturaDerecha + 1; 
		}

		this->diametro( nodoRaiz->obtenerHijoIzquierdo(), &*diametro );

		this->diametro( nodoRaiz->obtenerHijoDerecho(), &*diametro );
	}
}

template <class tipo>
void ArbolNario<tipo>::altura( NodoArbol<tipo> *nodoRaiz, int alturaActual, int *altura )
{
	if ( !nodoRaiz->esNulo() )
	{
		if ( alturaActual > *altura )
		{
			*altura = alturaActual;
		}

		this->altura( nodoRaiz->obtenerHijoIzquierdo(), alturaActual+1, &*altura );

		this->altura( nodoRaiz->obtenerHijoDerecho(), alturaActual, &*altura );
	}
}

template <class tipo>
void ArbolNario<tipo>::vaciar( NodoArbol<tipo> *nodoRaiz )
{
	if ( !nodoRaiz->esNulo() )
	{
		this->vaciar( nodoRaiz->obtenerHijoIzquierdo() );

		this->vaciar( nodoRaiz->obtenerHijoDerecho() );
	}

	delete nodoRaiz;
}

template <class tipo>
void ArbolNario<tipo>::copiar( NodoArbol<tipo> *nodoOriginal , NodoArbol<tipo> *nodoCopia )
{
	if ( !nodoOriginal->esNulo() )
	{
		nodoCopia->modificarDato( nodoOriginal->obtenerDato() );
		
		this->copiar( nodoOriginal->obtenerHijoIzquierdo(), nodoCopia->obtenerHijoIzquierdo() );

		this->copiar( nodoOriginal->obtenerHijoDerecho(), nodoCopia->obtenerHijoDerecho() );
	}
}

template <class tipo>
NodoArbol<tipo> *ArbolNario<tipo>::obtenerNodoRaiz()
{
	return( this->raiz );
}

#endif
