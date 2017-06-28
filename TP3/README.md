# Trabajo Practico 3 - Sistemas Operativos I

En este trabajo practico lo que realizamos son dos modulos que sirven 
para encriptar y desencriptar palabras.

##### Pasos a seguir para poder utilizar los modulos:

###### Modulo encriptador

  - Al descomprimir el .zip se va a encontrar con dos carpetas: TP3 y TP3-1
  - La carpeta TP3 tiene el modulo enctriptador, mientras que la TP3-1 tiene 
   el modulo desenctriptador.
  - En ambas carpetas tienen los Makefile para compilar los programas. Para poder 
  utilzarlos en la carpeta donde se encuentran los modulos abrir terminal y 
    escribir :  make

                /TP3$ make
  - Quedando algo asi como en la imagen de arriba. Al realizar esto se compila el modulo y esta listo para ser utilizado.
  - En la misma terminal escribir 
  
              $ sudo mknod /dev/char_dev c 60 0
    para crear el archivo donde se va a escribir lo que encriptemos y desencriptemos.
- Para  cambiar los permisos del archivo 

              $  sudo chmod 666 /dev/char_dev   


- Para cargar el modulo 

                $ sudo insmod TP3.ko
  ahora el modulo se encuentra listo para poder ser utilizado. 

- Ahora vamos a escribir el mensaje que queremos encriptar 

               $ echo -n "Mensaje a encriptar" > /dev/char_dev
    eso nos encripta el mensaje y lo guarda en /dev/char_dev.
- Para poder leer el mensaje 
- 
             $ cat /dev/char_dev
    y ahi en la terminal podemos ver el mensaje encriptado.
- Para descargar el modulo solo ponemos 
- 
            $ sudo rmmod TP3.ko

###### Modulo desencriptador
- Una vez descargado el modulo encriptador vamos a proceder a cargar el encriptador 
siguendo los mismos pasos que para cargar el anterior.
- Ahora nos vamos a la carpeta TP3-1
- Para compilar el modulo
- 
                /TP3-1$ make
- Para cargar el modulo 

                $ sudo insmod TP3-1.ko
  ahora el modulo se encuentra listo para poder ser utilizado. 
 Es importante recordar que debe estar descargado si o si el modulo anterior.
- Ahora vamos a escribir el mensaje que queremos desencriptar, que deberia ser una copia de la salida del modulo anterior

               $ echo -n "Mensaje a desencriptar" > /dev/char_dev
    esto al igual que antes nos desencripta y guarda en /dev/char_dev.
- Para poder leer el mensaje 
- 
             $ cat /dev/char_dev
    y ahi en la terminal podemos ver el mensaje encriptado.
- Para descargar el modulo solo ponemos 
- 
            $ sudo rmmod TP3-1.ko


