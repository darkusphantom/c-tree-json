#variables-INICIO------------------------------------------------------------------------------------------------------

#almacena los nombres de todas las librerias .h
Puntos_h = *.h

#almacena el nombre del archivo .cpp
Programa = *.c*

#almacena el nombre del ejecutable
Ejecutable = arboles

#almacena el nombre del archivo de entrada
Entrada = entrada.txt

#almacena el nombre del archivo de salida
Salida = salida.txt

#almacena el comando del compilador
CC = g++

#variables-FIN----------------------------------------------------------------------------------------------------------

#compila y ejecuta el achivo .cpp
all: principal

principal: 
	$(CC) $(Programa) -o $(Ejecutable) && ./$(Ejecutable)
	
#compila y ejecuta con un archivo de entrada y salida por entrada estandar
in_out :
	$(CC) $(Programa) -o $(Ejecutable) && ./$(Ejecutable) < $(Entrada) > $(Salida)
	
#compila y ejecuta solo con salida standar de archivo
out :
	$(CC) $(Programa) -o $(Ejecutable) && ./$(Ejecutable) > $(Salida)

#compila y ejecuta solo con entrada standar de un archivo
In :
	$(CC) $(Programa) -o $(Ejecutable) && ./$(Ejecutable) < $(Entrada)

#compila las librerias
librerias: 
	$(CC) $(Puntos_h)

#borra el archivo ejecutable y los archivos .gch
clean: 
	rm -f $(Ejecutable) *.gch
