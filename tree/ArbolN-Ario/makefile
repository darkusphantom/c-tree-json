#variables-INICIO

#almacena los nombres de todas las librerias .h
Puntos_h = *.h

#almacena el nombre del archivo .cpp
Programa = *.c*

#almacena el nombre del ejecutable
Ejecutable = salida

#almacena el comando del compilador
CC = g++

#variables-FIN

#compila y ejecuta el achivo .cpp
all: principal

principal: 
	$(CC) $(Programa) -o $(Ejecutable) && ./$(Ejecutable) 

#compila las librerias
librerias: 
	$(CC) $(Puntos_h)

#borra el archivo ejecutable y los archivos .gch
clean: 
	rm -f $(Ejecutable) *.gch