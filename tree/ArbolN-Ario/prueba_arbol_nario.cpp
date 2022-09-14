#include <iostream>
#include "ArbolNario.h"
#include <list>

using namespace std;

template <class tipo>
void imprimir_lista( list<tipo> lista )
{

	while( !lista.empty() )
	{
		cout<<lista.front()<<endl;

		lista.pop_front();
	}
}

int main()
{
	
	ArbolNario<string> *a = new ArbolNario<string>( "AAAAA" );

	cout <<"es vacia: ";

	if ( a->esVacia() )
	{
		cout<<"es vacia"<<endl;
	}
	else
	{
		cout<<"no es vacia"<<endl;
	}

	cout<<"es hoja: ";

	if ( a->esHoja() )
	{
		cout<<"es hoja"<<endl;
	}
	else
	{
		cout<<"no es hoja"<<endl;
	}

	cout<<"obtener raiz: "<<a->obtenerRaiz()<<endl;

	cout<<"prueba insertar hijo izquierdo"<<endl;

	a->insertarHijoIzquierdo( "AAAAA", "BBBBB" );

	cout<<"insertar hermano derecho"<<endl;

	a->insertarHermanoDerecho( "AAAAA", "CCCCC" );

	list<string> lista;

	cout<<"prueba preorden"<<endl;

	a->preorden( &lista );

	imprimir_lista( lista );

	lista.clear();

	cout<<"prueba postorden"<<endl;

	a->postorden( &lista );

	imprimir_lista( lista );

	lista.clear();

	cout<<"prueba inorden"<<endl;

	a->inorden( &lista );

	imprimir_lista( lista );

	lista.clear();

	cout<<"prueba diametro: "<<a->diametro()<<endl;

	cout<<"prueba copear: "<<endl;

	ArbolNario<string>* a2 = new ArbolNario<string>();

	a2->copiar( a );

	cout<<"----------------------todo bien hasta ahora-------------------"<<endl;

	return 0;
}