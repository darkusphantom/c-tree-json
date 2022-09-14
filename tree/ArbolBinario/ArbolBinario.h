#ifndef ARBOLBINARIO_H
#define ARBOLBINARIO_H

#include "NodoA.h"
#include <list>
#include <cmath>

template <class type>
class BinaryTree
{
	protected:
		NodoA<type>* root;

		// Metodos
		void preorden( NodoA<type> *nodoActual, list<type> &listaRecorrido );//inserta el recorrido en una lista
		void postorden( NodoA<type> *nodoActual, list<type> &listaRecorrido );//inserta el recorrido en una lista
		void inorden( NodoA<type> *nodoActual, list<type> &listaRecorrido );//inserta el recorrido en una lista
		void vaciar( NodoA<type>* nodoActual );//vacia el arbol
		NodoA<type>* copy( NodoA<type>* nodoActual );//copia nodo a nodo los nodos del arbol existente
		void getHeight( NodoA<type>* nodoActual, int alturaActual, int &alturaMayor );//recorre el arbol buscando la mayor altura
		void diametro( NodoA<type>* nodoActual, int &diametroMayor );//recorre los nodos buacando los diametros
		NodoA<type>* crearPreordenInorden( list<type> &preorden, list<type> &inorden );//constructor del arbol preorden inorden
		NodoA<type>* crearPostordenInorden( list<type> &postorden, list<type> &inorden );//constructor del arbol postorden inorden
		void insertarIzquierdo( NodoA<type>* nodoActual, type newData, type padre, bool &insertado );//busca al nodo padre y le inserta un hijo izquierdo
		void insertarDerecho( NodoA<type>* nodoActual, type newData, type padre, bool &insertado );//busca al nodo padre y le inserta un hijo derecho
		int peso( NodoA<type>* nodoActual );//calcula el peso de un arbol
		void isComplete( NodoA<type>* nodoActual, bool &completo );//se corre el arbol y busca los nodos no terminales y los comprueba
		void isFully( NodoA<type>*nodoActual, int alturaActual, int altura, bool &lleno );//recorre el arbol e indica si el arbol esta lleno
		void iguales( NodoA<type>* nodo1, NodoA<type>* nodo2, bool &iguales );//recorre el arbo comparando cada uno de los nodos
		void isomorfo( NodoA<type>* nodo1, NodoA<type>* nodo2, bool &isomorfo );//recorre el arbol comprobando si son isomorfos
		bool compararRecorrido( list<type> recorrido1, list<type> recorrido2 );//ordena y compara todos los elementos de los arboles
		double resolverArbolSintaxis( NodoA<type>* nodoActual );//resuelve un arbol de sintaxis
		double operador( double valor1, double valor2, type signo );//toma un operador char y realiza la operacion
		void surdo( NodoA<type>* nodoActual, bool &esSurdo );//recorre y compara la altura de las ramas para saber si el arbol es surdo
		void searchLeaves(NodoA<type>* root, list<type> &items);
		int _findDistance(NodoA<type>* root, int n1, int n2, int &maxDistance);

	public:
		BinaryTree();
		BinaryTree( type newData );
		BinaryTree( type newData, const BinaryTree<type>* nuevoIzquierda, const BinaryTree<type>* nuevoDerecha );
		BinaryTree( const BinaryTree<type> &arbolOriginal );
		~BinaryTree();
		
		//metodos
		bool isEmpty();//indica si el arbol es nulo
		type getRoot();//devuelve el dato del nodo root
		void copy( const BinaryTree<type> &arbolOriginal );//copia un arbol existente en la instancia
		void preorden( list<type> &listaRecorrido );//crea un recorrido en preorden
		void postorden( list<type> &listaRecorrido );//crea un recorrido en postorden
		void inorden( list<type> &listaRecorrido );//crea un recorrido en inorden
		void niveles( list<type> &listaRecorrido );//crea un recorrido por niveles
		void vaciar();//vacia el arbol
		int getHeight();//retorna la altura de un arbol
		int diametro();//retorna el diametro de un arbol
		int findDistance(int a, int b);
		int findLevel(NodoA<type>* root, int k, int level);
		int getMaxDistance();
		void setMaxDistance(int value);
		void preordenInorden( list<type> preorden, list<type> inorden );//construye um arbol con el recorrido en preorden e inorden
		void postordenInorden( list<type> postorden, list<type> inorden );//construye um arbol con el recorrido en postorden e inorden
		bool isLeaf();//indica si la root del arbol es una hoja
		void insertarHijoIzquierdo( type newData, type padre );//inserta un nuevo dato como hijo izquierdo al nodo padre
		void insertarHijoDerecho( type newData, type padre );//inserta un nuevo dato como hijo derecho al nodo padre
		int peso();//devuelve el peso dl arbol
		bool isComplete();//indica si un arbol es completo
		bool isFully();//indica si el arbol esta lleno
		bool iguales( const BinaryTree<type> &arbol2 );//indica si dos arboles son iguales
		bool isomorfo( const BinaryTree<type> &arbol2 );//indica si dos arboles son isomorfos
		bool semejantes( const BinaryTree<type> &arbol2 );//indica si dos arboles son semejantes
		bool surdo();//indica si un arbol es surdo
		list<type> getLeaves();
};

template <class type>
BinaryTree<type>::BinaryTree()
{
	this->root = NULL;
}

template <class type>
BinaryTree<type>::BinaryTree( type newData )
{
	this->root = new NodoA<type>( newData );
}

template <class type>
BinaryTree<type>::BinaryTree( type newData, const BinaryTree<type>* nuevoIzquierda, const BinaryTree<type>* nuevoDerecha )
{
	 this->root = new NodoA<type>( newData, this->copy( nuevoIzquierda->root ), this->copy( nuevoDerecha->root ));
}

template <class type>
BinaryTree<type>::BinaryTree( const BinaryTree<type> &arbolOriginal )
{
	this->root = this->copy( arbolOriginal.root );
}

template <class type>
BinaryTree<type>::~BinaryTree() {
	if ( this->root != NULL )
		this->vaciar( this->root );
}

template <class type>
bool BinaryTree<type>::isEmpty() {
	return( this->root == NULL );
}

template <class type>
type BinaryTree<type>::getRoot() {
	return( this->root->obtenerDato() );
}

template <class type>
void BinaryTree<type>::copy( const BinaryTree<type> &arbolOriginal ) {
	this->root = this->copy( arbolOriginal.root );
}

template <class type>
void BinaryTree<type>::preorden( list<type> &listaRecorrido ) {
	this->preorden( this->root, listaRecorrido );
}

template <class type>
void BinaryTree<type>::postorden( list<type> &listaRecorrido ) {
	this->postorden( this->root, listaRecorrido );
}

template <class type>
void BinaryTree<type>::inorden( list<type> &listaRecorrido ) {
	this->inorden( this->root, listaRecorrido );
}

template <class type>
void BinaryTree<type>::niveles( list<type> &listaRecorrido ) {
	list<NodoA<type>*> listaNodos;
	NodoA<type>* nodoPadre;

	//insertamos el primer nodo en la lista de nodos
	listaNodos.push_back( this->root );

	//insertamos el primer elemento del recorrido
	listaRecorrido.push_back( this->root->obtenerDato() );

	//iniciamos el nodo padre para obtener los hijos por niveles
	nodoPadre = this->root;

	//ciclo que obtiene los hijos de los nodos padres e inserta el la lista recorrido
	while ( !listaNodos.empty() )
	{
		//obtenemos el hijo izquierdo del nodo padre
		if ( nodoPadre->obtenerHijoIzquierdo() != NULL )
		{
			listaNodos.push_back( nodoPadre->obtenerHijoIzquierdo() );
		}
		
		//obtenemos el hijo derecho del nodo padre
		if ( nodoPadre->obtenerHijoDerecho() != NULL )
		{
			listaNodos.push_back( nodoPadre->obtenerHijoDerecho() );
		}

		//eliminamos el primer nodo de la lista de nodos
		listaNodos.pop_front();

		//obtenemos el siguiente nodo padre y lo insertamos en la lista de recorrido
		if ( !listaNodos.empty() )
		{
			nodoPadre = listaNodos.front();
			listaRecorrido.push_back( nodoPadre->obtenerDato() );
		}
		
	}
}

template <class type>
void BinaryTree<type>::vaciar(){
	if ( this->root != NULL )	{
		this->vaciar( this->root );
		this->root = NULL;
	}
}

template <class type>
int BinaryTree<type>::getHeight() {
	int alturaMayor = -1;
	this->getHeight( this->root, 0, alturaMayor );

	return( alturaMayor );
}

template <class type>
int BinaryTree<type>::diametro() {
	int diametroMayor = -1;

	this->diametro(this->root, diametroMayor);
	return(diametroMayor);
}

/*template <class type>
int BinaryTree<type>::getMaxDistance() {
	return (this->maxDistance);
}

template <class type>
void BinaryTree<type>::setMaxDistance(int value) {
	this->maxDistance = value;
}*/


template <class type>
int BinaryTree<type>::findDistance(int a, int b) {
	//NodoA<type>* lca = LCA(this->root, a, b);
//	this->setMaxDistance(0);
	int maxDistance = 0;
	this->_findDistance(this->root, a, b, maxDistance);

	return maxDistance;

	//int distance1 = findLevel(lca, a, 0);
	//int distance2 = findLevel(lca, b, 0);

	//return distance1 + distance2;
}

template<class type>
int BinaryTree<type>::_findDistance(NodoA<type>* root, int n1, int n2, int &maxDistance) {
	if (!root) return 0;

	int left = _findDistance(root->obtenerHijoIzquierdo(), n1, n2, maxDistance);
  int right = _findDistance(root->obtenerHijoDerecho(), n1, n2, maxDistance);
  
  if (root->obtenerDato() == n1 || root->obtenerDato() == n2) {
		if (left || right) {
			int value = max(left, right);
      maxDistance = value;
      return 0;
    }
		else
			return 1;
  }
  else if (left && right) {
		maxDistance = left+right;
    //this->setMaxDistance(left + right);
    return 0;
  }
  else if (left || right)
    return max(left, right) + 1;

  return 0;
}

template <class type>
int BinaryTree<type>::findLevel(NodoA<type>* root, int k, int level) {
	if (root == NULL) return -1;
  if (root->obtenerDato() == k) return level;
 
  int left = findLevel(root->obtenerHijoIzquierdo(), k, level + 1);
  if (left == -1)
    return findLevel(root->obtenerHijoDerecho(), k, level + 1);
  
	return left;
}

template <class type>
void BinaryTree<type>::preordenInorden( list<type> preorden, list<type> inorden )
{
	this->root = this->crearPreordenInorden( preorden, inorden );
}

template <class type>
void BinaryTree<type>::postordenInorden( list<type> postorden, list<type> inorden )
{
	this->root = this->crearPostordenInorden( postorden, inorden );
}

template <class type>
bool BinaryTree<type>::isLeaf()
{
	//se comprueba si ambos hijos apuntan a null
	return( this->root->isLeaf() );
}

template <class type>
void BinaryTree<type>::insertarHijoIzquierdo( type newData, type padre )
{
	bool insertado = false;

	this->insertarIzquierdo( this->root, newData, padre, insertado );
}

template <class type>
void BinaryTree<type>::insertarHijoDerecho( type newData, type padre )
{
	bool insertado = false;

	this->insertarDerecho( this->root, newData, padre, insertado );
}

template <class type>
int BinaryTree<type>::peso()
{
	return( this->peso( this->root ) );
}

template <class type>
bool BinaryTree<type>::isComplete()
{
	bool completo = true;

	this->isComplete( this->root, completo );

	return( completo );
}

template <class type>
bool BinaryTree<type>::isFully()
{
	int altura;

	bool lleno = true;

	//obtenoms la altur del arbol
	altura = this->getHeight();

	//verificamos si el arbol esta lleno
	this->isFully( this->root, 0, altura, lleno );

	return( lleno );
}

template <class type>
bool BinaryTree<type>::iguales( const BinaryTree<type> &arbol2 )
{
	bool iguales = true;

	this->iguales( this->root, arbol2.root, iguales );

	return( iguales );
}

template <class type>
bool BinaryTree<type>::isomorfo( const BinaryTree<type> &arbol2 )
{
	bool isomorfo = true;

	this->isomorfo( this->root, arbol2.root, isomorfo );

	return( isomorfo );
}

template <class type>
bool BinaryTree<type>::semejantes( const BinaryTree<type> &arbol2 )
{
	list<type> recorrido1, recorrido2;

	//se obtiene el recorrido del arbol instancia
	this->preorden( this->root, recorrido1 );

	//se obtiene el recorrido del arbol parametro
	this->preorden( arbol2.root, recorrido2 );

	//se procede a compara ambos recorridos
	return( this->compararRecorrido( recorrido1, recorrido2 ) );
}

template <class type>
bool BinaryTree<type>::surdo()
{
	bool esSurdo = true;

	this->surdo( this->root, esSurdo );

	return( esSurdo );
}

/*****************************************************************************************************************
***********************************************PROTECTED**********************************************************
*****************************************************************************************************************/

template <class type>
void BinaryTree<type>::preorden( NodoA<type>* nodoActual, list<type> &listaRecorrido )
{
	//colocamos el dato actual en la lista
	listaRecorrido.push_back( nodoActual->obtenerDato() );
	
	//buscamos en el hijo izquierdo
	if ( nodoActual->obtenerHijoIzquierdo() != NULL )
	{
		this->preorden( nodoActual->obtenerHijoIzquierdo(), listaRecorrido );
	}

	//buscamos en el hijo derecho
	if ( nodoActual->obtenerHijoDerecho() != NULL )
	{
		this->preorden( nodoActual->obtenerHijoDerecho(), listaRecorrido );
	}
}

template <class type>
void BinaryTree<type>::postorden( NodoA<type>* nodoActual, list<type> &listaRecorrido )
{
	//buscamos en el hijo izquierdo
	if ( nodoActual->obtenerHijoIzquierdo() != NULL )
	{
		this->postorden( nodoActual->obtenerHijoIzquierdo(), listaRecorrido );
	}

	//buscamos en el hijo derecho
	if ( nodoActual->obtenerHijoDerecho() != NULL )
	{
		this->postorden( nodoActual->obtenerHijoDerecho(), listaRecorrido );
	}
	
	//colocamos el dato actual en la lista
	listaRecorrido.push_back( nodoActual->obtenerDato() );
}

template <class type>
void BinaryTree<type>::inorden( NodoA<type>* nodoActual, list<type> &listaRecorrido )
{
	//buscamos en el hijo izquierdo
	if ( nodoActual->obtenerHijoIzquierdo() != NULL )
	{
		this->inorden( nodoActual->obtenerHijoIzquierdo(), listaRecorrido );
	}

	//colocamos el dato actual en la lista
	listaRecorrido.push_back( nodoActual->obtenerDato() );

	//buscamos en el hijo derecho
	if ( nodoActual->obtenerHijoDerecho() != NULL )
	{
		this->inorden( nodoActual->obtenerHijoDerecho(), listaRecorrido );
	}
}

template <class type>
void BinaryTree<type>::vaciar( NodoA<type>* nodoActual )
{
	//se eliminan los nodos izquierdos
	if ( nodoActual->obtenerHijoIzquierdo() != NULL )
	{
		this->vaciar( nodoActual->obtenerHijoIzquierdo() );
	}

	//se eliminan los nodos derechos
	if ( nodoActual->obtenerHijoDerecho() != NULL )
	{
		this->vaciar( nodoActual->obtenerHijoDerecho() );
	}

	//se elimina el nodo actual
	delete nodoActual;
}

template <class type>
NodoA<type>* BinaryTree<type>::copy( NodoA<type>* nodoActual )
{
	NodoA<type>* instanciaroot;

	//inicializamos el nodo en nulo
	instanciaroot = NULL;

	//si el nodo no es nulo lo copiamos
	if ( nodoActual != NULL )
	{
		//se reserva memoria y se copian los nodos hijos
		instanciaroot = new NodoA<type>( nodoActual->obtenerDato(), this->copy( nodoActual->obtenerHijoIzquierdo()), this->copy( nodoActual->obtenerHijoDerecho() ) );
	}
	
	//se retorna el resultados de la copia
	return( instanciaroot );
}

template <class type>
void BinaryTree<type>::getHeight( NodoA<type>* nodoActual, int alturaActual, int &alturaMayor )
{
	if ( nodoActual != NULL )
	{
		//comprobamos si la altura actual es mayor a la mayor altura
		if ( alturaActual > alturaMayor )
		{
			alturaMayor = alturaActual;
		}
		
		//buscamos la altura del hijo izquierdo
		this->getHeight( nodoActual->obtenerHijoIzquierdo(), alturaActual+1, alturaMayor );

		//buscamos la altura del hijo derecho
		this->getHeight( nodoActual->obtenerHijoDerecho(), alturaActual+1, alturaMayor );
	}
} 

template <class type>
void BinaryTree<type>::diametro( NodoA<type>* nodoActual, int &diametroMayor ) {
	if ( nodoActual != NULL )	{
		int alturootquierda = -1;
		int alturaDerecha = -1;

		//buscamos la altura del lado izquierdo
		this->getHeight( nodoActual->obtenerHijoIzquierdo(), 0, alturootquierda );
		//buscamos la altura del lado derecho
		this->getHeight( nodoActual->obtenerHijoDerecho(), 0, alturaDerecha );

		//comprobamos si el diametro actual es el mayor de los diametros
		alturootquierda += alturaDerecha + 2;
		if ( alturootquierda > diametroMayor ) {
			diametroMayor = alturootquierda;
		}

		//buscamos si no hay mayores diamtros en el hijo izquierdo
		this->diametro( nodoActual->obtenerHijoIzquierdo(), diametroMayor );
		//buscamos si no hay mayores diamtros en el hijo derecho
		this->diametro( nodoActual->obtenerHijoDerecho(), diametroMayor );
	}
}

template <class type>
NodoA<type>* BinaryTree<type>::crearPreordenInorden( list<type> &preorden, list<type> &inorden )
{
	//inicializamos el nodo en nulo
	NodoA<type>* nodoroot = NULL;

	//lista que almacena el lado izquierdo del recorrido inorden
	list<type> inordenIzquierda;

	//se comprueba que las listas no esten vacias 
	if ( !preorden.empty() && !inorden.empty() )
	{
		//separamos el recorrido inorden a partir del recorrido preorden
		while ( preorden.front() != inorden.front() )
		{
			//insertamos el frente del recorrido inorden al recorrido izquierdo
			inordenIzquierda.push_back( inorden.front() );

			//eliminamos el elemento del recorrido de la derecha
			inorden.pop_front();
		}

		//creamos la root con el primer elemento deñ recorrido preorden
		nodoroot = new NodoA<type>( preorden.front() );

		//eliminamos el elemento recien creado de los recorridos
		preorden.pop_front();

		inorden.pop_front();

		//contruimos el lado izquierdo del arbol
		nodoroot->modificarHijoIzquierdo( this->crearPreordenInorden( preorden, inordenIzquierda ) );

		//construimos el lado derecho del arbol
		nodoroot->modificarHijoDerecho( this->crearPreordenInorden( preorden, inorden ) );
	}
	
	return( nodoroot );
}

template <class type>
NodoA<type>* BinaryTree<type>::crearPostordenInorden( list<type> &postorden, list<type> &inorden )
{
	//inicializamos el nodo en nulo
	NodoA<type>* nodoroot = NULL;

	//lista que almacena el lado izquierdo del recorrido inorden
	list<type> inordenIzquierda;

	//se comprueba que las listas no esten vacias 
	if ( !postorden.empty() && !inorden.empty() )
	{
		//separamos el recorrido inorden a partir del recorrido postorden
		while ( postorden.back() != inorden.front() )
		{
			//insertamos el frente del recorrido inorden al recorrido izquierdo
			inordenIzquierda.push_back( inorden.front() );

			//eliminamos el elemento del recorrido de la derecha
			inorden.pop_front();
		}

		//creamos la root con el ultimo elemento del recorrido postorden
		nodoroot = new NodoA<type>( postorden.back() );

		//eliminamos el elemento recien creado de los recorridos
		postorden.pop_back();

		inorden.pop_front();

		//contruimos el lado derecho del arbol
		nodoroot->modificarHijoDerecho( this->crearPostordenInorden( postorden, inorden ) );
		
		//construimos el lado izquierdo del arbol
		nodoroot->modificarHijoIzquierdo( this->crearPostordenInorden( postorden, inordenIzquierda ) );
	}
	
	return( nodoroot );
}

template <class type>
void BinaryTree<type>::insertarIzquierdo( NodoA<type>* nodoActual, type newData, type padre, bool &insertado )
{
	//verificamos si el dato no ha sido insertado
	if ( !insertado && nodoActual != NULL )
	{
		//verificamos si el nodo actual es el padre buscado
		if ( nodoActual->obtenerDato() == padre )
		{
			//insertamos el nuevo elemento en su hijo izquierdo
			nodoActual->modificarHijoIzquierdo( new NodoA<type>( newData ) );

			//colocamos la bandera insertado en true
			insertado = true;
		}
		else
		{
			//buscamos el padre en el hijo izquierdo
			this->insertarIzquierdo( nodoActual->obtenerHijoIzquierdo(), newData, padre, insertado );

			//buscamos el padre en el hijo derecho
			this->insertarIzquierdo( nodoActual->obtenerHijoDerecho(), newData, padre, insertado );
		}
	}
}

template <class type>
void BinaryTree<type>::insertarDerecho( NodoA<type>* nodoActual, type newData, type padre, bool &insertado )
{
	//verificamos si el dato no ha sido insertado
	if ( !insertado && nodoActual != NULL )
	{
		//verificamos si el nodo actual es el padre buscado
		if ( nodoActual->obtenerDato() == padre )
		{
			//insertamos el nuevo elemento en su hijo derecho
			nodoActual->modificarHijoDerecho( new NodoA<type>( newData ) );

			//colocamos la bandera insertado en true
			insertado = true;
		}
		else
		{
			//buscamos el padre en el hijo izquierdo
			this->insertarDerecho( nodoActual->obtenerHijoIzquierdo(), newData, padre, insertado );

			//buscamos el padre en el hijo derecho
			this->insertarDerecho( nodoActual->obtenerHijoDerecho(), newData, padre, insertado );
		}
	}
}

template <class type>
int BinaryTree<type>::peso( NodoA<type>* nodoActual )
{
	int resultado = 0;

	if ( nodoActual != NULL )
	{
		//si el nodo no es nulo colocamos el contador en 1
		resultado = 1;

		//contamos los nodos del lado izquierdo
		resultado += this->peso( nodoActual->obtenerHijoIzquierdo() );

		//contamos los nodos del lado derecho
		resultado += this->peso( nodoActual->obtenerHijoDerecho() );
	}

	return( resultado );
}

template <class type>
void BinaryTree<type>::isComplete( NodoA<type>* nodoActual, bool &completo )
{
	if ( completo && !nodoActual->isLeaf() )
	{
		//se comprueba que nodo sea competo
		if ( nodoActual->obtenerHijoIzquierdo() != NULL && nodoActual->obtenerHijoDerecho() != NULL )
		{
			//se compreuba el hijo izquierdo
			this->isComplete( nodoActual->obtenerHijoIzquierdo(), completo );

			//se comprueba el hijo derecho
			this->isComplete( nodoActual->obtenerHijoDerecho(), completo );
		}
		else
		{
			//si el nodo no es completo se coloca la bandera en falso
			completo = false;
		}
	}
}

template <class type>
void BinaryTree<type>::isFully( NodoA<type>* nodoActual, int alturaActual, int altura, bool &lleno )
{
	if ( lleno )
	{
		if ( !nodoActual->isLeaf() )
		{
			//se comprueba que nodo sea competo
			if ( nodoActual->obtenerHijoIzquierdo() != NULL && nodoActual->obtenerHijoDerecho() != NULL )
			{
				//se compreuba el hijo izquierdo
				this->isFully( nodoActual->obtenerHijoIzquierdo(), alturaActual+1, altura, lleno );

				//se comprueba el hijo derecho
				this->isFully( nodoActual->obtenerHijoDerecho(), alturaActual+1, altura, lleno );
			}
			else
			{
				//si el nodo no es completo se coloca la bandera en falso
				lleno = false;
			}
		}
		else
		{
			//si la altura es diferente se coloca la bandera en falso
			if ( alturaActual != altura )
			{
				lleno = false;
			}
		}
	}
}

template <class type>
void BinaryTree<type>::iguales( NodoA<type>* nodo1, NodoA<type>* nodo2, bool &iguales )
{
	if ( iguales )
	{
		if ( nodo1 != NULL && nodo2 != NULL )
		{
			//se compra la root
			iguales = nodo1->obtenerDato() == nodo2->obtenerDato();

			//se verifica el hijo izquierdo
			this->iguales( nodo1->obtenerHijoIzquierdo(), nodo2->obtenerHijoIzquierdo(), iguales );

			//se varifica el hijo derecho
			this->iguales( nodo1->obtenerHijoDerecho(), nodo2->obtenerHijoDerecho(), iguales );
		}
		else
		{
			//se verifica si los dos nodos son nulos
			if ( nodo1 != NULL || nodo2 != NULL )
			{
				//si algunos de los dos nodos no son nulos se coloca la bandera en falso
				iguales = false;
			}
		}
	}
}

template <class type>
void BinaryTree<type>::isomorfo( NodoA<type>* nodo1, NodoA<type>* nodo2, bool &isomorfo )
{
	if ( isomorfo )
	{
		if ( nodo1 != NULL && nodo2 != NULL )
		{
			//se verifica el hijo izquierdo
			this->isomorfo( nodo1->obtenerHijoIzquierdo(), nodo2->obtenerHijoIzquierdo(), isomorfo );

			//se varifica el hijo derecho
			this->isomorfo( nodo1->obtenerHijoDerecho(), nodo2->obtenerHijoDerecho(), isomorfo );
		}
		else
		{
			//se verifica si los dos nodos son nulos
			if ( nodo1 != NULL || nodo2 != NULL )
			{
				//si algunos de los dos nodos no son nulos se coloca la bandera en falso
				isomorfo = false;
			}
		}
	}
}

template <class type>
bool BinaryTree<type>::compararRecorrido( list<type> recorrido1, list<type> recorrido2 )
{
	bool respuesta = true;

	//se ordenan los recorridos
	recorrido1.sort();
	recorrido2.sort();

	//se verifica que tengan el mismo tamaño
	if ( recorrido1.size() == recorrido2.size() )
	{
		//se comprueba que tengan sus elemento iguales
		while( respuesta && !recorrido1.empty() && !recorrido2.empty() )
		{
			if ( recorrido1.front() != recorrido2.front() )
			{
				//si hay un elemento diferente se coloca la bandera en falso
				respuesta = false;
			}

			//nos movemos al siguiente elemento
			recorrido1.pop_front();
			recorrido2.pop_front();
		}
	}
	else
	{
		//si no tienen la misma longitud se coloca la bandera en falso
		respuesta = false;
	}
	

	return( respuesta );
}

template <class type>
double BinaryTree<type>::resolverArbolSintaxis( NodoA<type> *nodoActual )
{
	double resultado;
	if( !nodoActual->isLeaf() )
	{
		double valorIzquierdo, valorDerecho;
		//cout << nodoActual->obtenerDato()<<endl;
		valorIzquierdo = this->resolverArbolSintaxis( nodoActual->obtenerHijoIzquierdo() );
		
		valorDerecho = this->resolverArbolSintaxis( nodoActual->obtenerHijoDerecho() );
		//cout<<"-> "<<valorDerecho<<" -> "<<valorIzquierdo<<endl;
		resultado = operador( valorIzquierdo, valorDerecho, nodoActual->obtenerDato() );
		//cout<<"resultado "<<resultado<<endl;
	}
	else
	{
		char dato = nodoActual->obtenerDato();
		resultado = (int)dato - 48;
	}
	return( resultado );
}

template <class type>
double BinaryTree<type>::operador( double valor1, double valor2, type signo )
{
	double resultado;
	switch( signo )
	{
		case '+':
			resultado = valor1 + valor2;
			break;
		case '-':
			resultado = valor1 - valor2;
			break;
		case '*':
			resultado = valor1 * valor2;
			break;
		case '/':
			resultado = valor1 / valor2;
			break;
	}
	return( resultado );
}

template <class type>
void BinaryTree<type>::surdo( NodoA<type>* nodoActual, bool &esSurdo ) {
	if ( esSurdo && nodoActual != NULL ) {
		int alturootquierda = -1;
		int alturaDerecha = -1;

		//nos desplamos hata el ultimo hijo izquierdo
		this->surdo( nodoActual->obtenerHijoIzquierdo(), esSurdo );

		//nos desplazamos hasta el ultimo hijo derecho
		this->surdo( nodoActual->obtenerHijoDerecho(), esSurdo );

		//obtenos la altura izquierda
		this->getHeight( nodoActual->obtenerHijoIzquierdo(), 0, alturootquierda );

		//obtenemos la altura derecha
		this->getHeight( nodoActual->obtenerHijoDerecho(), 0, alturaDerecha );

		//si la altura derecha es mayor a la izquierda se coloca la bandera en falso
		if ( alturootquierda < alturaDerecha )
		{
			esSurdo = false; 
		}
	}
}

template <class type>
list<type> BinaryTree<type>::getLeaves() {
	list<type> items;
	this->searchLeaves(this->root, items);

	return items;
}

template <class type>
void BinaryTree<type>::searchLeaves(NodoA<type>* root, list<type> &items) {
	if (root == NULL) {
		return;
	}

	if (root->isLeaf()) {
		items.push_back(root->obtenerDato());
	}

	searchLeaves(root->obtenerHijoIzquierdo(), items);
	searchLeaves(root->obtenerHijoDerecho(), items);
}

#endif
