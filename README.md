# Trabajo Practico Numero 1 - Sistemas Operativos I	


### Integrantes
- Gatica, Carolina - 35.638.192
- Tarres, Martin   - 36.725.643

## Información importante

El proyecto se encuentra realizado para el sistema operativo de Linux. 
Es para una arquitectura de 64 bits.

### Guia de Instalación y Uso.


El proyecto se encuentra contenído en formato .zip. 
Luego de que descomprima se puede ejecutar el programa con los siguientes pasos:

* Para compilar el programa en terminal situarse en la carpeta donde esta el proyecto
 y poner el siguiente comando 

```sh
$ make
```
* Luego para ejecutar el programa 

```sh
$./ksamp
```
Si ejecuta el programa de la forma `$./ksamp` el programa va a obtener información sobre :

	-Tipo y modelo de su CPU
	-Versión del Kernel
	-Cantidad de tiempo transcurrido desde que se inició el sistema operativo, con el formato ddD hh:mm:ss
 	-Cantidad de sistemas de archivo soportados por el kernel

Si en terminal pone `$./ksamp-s` se obtiene la información agregando :

	-Cantidad de tiempo de CPU utilizado para usuarios, sistema y proceso idle.
	-Cantidad de cambios de contexto.
	-Fecha y hora cuando el sistema fue iniciado.
	-Número de procesos creados desde el inicio del sistema.

Si ejecuta el comando `$./ksamp-l` lo de la versión `$./ksamp-s` agregando : 
	
	-Número de peticiones a disco realizadas.
	-Cantidad de memoria configurada en el hardware.
	-Cantidad de memoria disponible.
	-Lista de los promedios de carga de 1 minuto.


