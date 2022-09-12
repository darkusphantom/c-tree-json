# JSON en C++

## Introducción

Este proyecto de la universidad que consiste en aplicar la lógica de arboles utilizando una librería JSON en C++.

## Instrucciones

- El ejercicio requiere la lectura de datos **utilizando archivos**.
- El proyecto se debe realizar con C++, utilizando sus librerías estándar.
- La compilación de sus códigos fuentes se realizará por un archivo **makefile**.
- Puede usarse Estructuras Lineales, Jerárquicas o Multienlazadas para resolver el problema.
- El makefile debe generar un ejecutable
- Utilizar la librería [simpleson](https://github.com/gregjesl/simpleson) para resolver el problema

## ¿Qué es un JSON?

- Definición: [JSON by wikipedia](es.wikipedia.org/wiki.JSON)

- Ejemplo de JSON:

  ```json
  {
  	"departamento":8,
  	"nombredepto":"Ventas",
  	"director": "Juan Rodríguez",
  	"empleados":[
  		{
  			"nombre":"Pedro",
  			"apellido":"Fernández"
  		},
          {
  			"nombre":"Jacinto",
  			"apellido":"Benavente"
  		}
  	]
  }
  ```

  

## ¿Cómo importar la librería simpleson?

Copias los archivos` json.cpp` y `json.h` y lo mueves a tu proyecto.

```c++
#include <iostream>
#include "json.h"
using namespace std;

int main() {
 	// variables declaration
 	string input = "{ \"hello\": \"world\" }";
	json::jobject result = json::jobject::parse(input);
    
 	//code
 	string value = result.get("hello");
    cout << value;
}
```

## ¿Qué se pide en este proyecto?

Para esta práctica del uso de JSON, se pide leer un archivo `.json` jerárquico y realizar los recorridos **preorden**, **postorden**, **inorden** y por **niveles del árbol** asociado a la estructura JSON jerárquica.

### Formato de entrada

Se requiere dos archivos:

- `entrada.json`: Este contiene un JSON jerárquico en donde obtendrás los datos de personas.
- `entrada.in`: Contiene unicamente las palabras nombre o cédula. Si la palabra es nombre, por cada nodo se imprime la concatenación sin despacio del campo “nombre” y “apellido”. Ejemplo: “PedroFernandez”. Si la palabra es cédula, se imprime el valor de la “cédula”.

```json
{
    "nombre": "Alvaro",
    "apellido": "Espinoza",
    "cedula": "24500719",
    "subordinados": [
        {
            "nombre": "Giuliana",
            "apellido": "Belli",
            "cedula": "5468339912",
            "subordinados": []
        },
        {
            "nombre": "Martin",
            "apellido": "Rodriguez",
            "cedula": "1698972",
            "subordinados": [
                {
                    "nombre": "Juan",
                    "apellido": "Cano",
                    "cedula": "16989723",
                    "subordinados": []
                }
            ]
        },
        {
            "nombre": "Angel",
            "apellido": "Oropeza",
            "cedula": "78982",
            "subordinados": []
        }
    ]
}
```



### Formato de salida

La salida será cuatro líneas con cada recorrido del árbol descrito en `entrada.json`, mostrando el campo escrito en “salida.out” para cada nodo, seguido por el nombre del recorrido en mayúscula y dos puntos, cada palabra entre comillas, separadas por coma y espacio. El recorrido en sí debe estar entre corchetes.
Por ejemplo, en el caso del JSON anterior con la palabra NOMBRE:

```
PREORDEN: [“AlvaroEspinoza”, “GiulianaBelli”, “MartinRodriguez”, “JuanCano”, “AngelOropeza”]
INORDEN: [“GiulianaBelli”, “AlvaroEspinoza”, “JuanCano”, “MartinRodriguez”, “AngelOropeza”]
POSTORDEN: [“GiulianaBelli”, “JuanCano”, “AngelOropeza”, “MartinRodriguez”, “AlvaroEspinoza”]
NIVELES: [“AlvaroEspinoza”, “GiulianaBelli”, “MartinRodriguez”, “AngelOropeza”, “JuanCano”]
```

