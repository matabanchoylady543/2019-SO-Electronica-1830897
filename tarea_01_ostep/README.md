#Reporte acerca de lo realizado en cada item.

*[mem.c](mem.c):

*En mem.c se tienen dos procesos pero cada vez que se ejecutan, surge
una dirección de memoria distinta, por lo tanto, se necesitaba
deshabilitar ASLR y obtener una dirección estatica, asi que se usa el
comando echo 0 > /proc/sys/kernel/randomize_va_space, pero no se logro
deshabilitar la aleatoriedad debido a que no se tenian permisos de
superusuario, por medio del comando sudo se logro entrar a la interfaz
de superusuario y modificar el ASLR desde su interior, al realizarlo, se
vuelve a ejecutar nuevamente mem.c y se logra obtener los dos procesos
pero ambos en la misma dirección.


*[threads.c](threads.c):

*Se crea un nuevo archivo llamado mycommon.h, el cual alberga las funciones
donde se detiene temporalmente uno de los hilos y el otro se modifica,
este contendra las siguientes funciones: generar_puerta, abrir_puerta,
cerrar_puerta, destruir_puerta.


*[io.c](io.c):

*El programa recibe el nombre del fichero a procesar en la posición 1 del arreglo *argv[ ].
-Se crea un apuntador de tipo FILE * y se utiliza la función fopen() para abrir el fichero, haciendo uso del
parámetro rb (lectura en binario).
-Se valida la existencia del fichero.
-Se ubica el apuntador en la posición 0 al comienzo del fichero.

Más importante:

-Se emplea la función feof() en un bucle while que recorrerá todas las posiciones (bytes) hasta llegar al final
del fichero, la variable cont incrementará su valor en uno por cada repetición del bucle y de esta manera
guardará el numéro total de posiciones del fichero.

-Se ubica al apuntador en la penúltima posición del fichero y se hace uso de otro bucle while condicionado
por la función ftell() &gt;=0, la variable de control n decrementará su valor en 1 por cada repetición del bucle y
se utilizará ese valor para posicionar el puntero e imprimir los carácteres, esto con el fin de mostrar el texto
de manera inversa hasta llegar a la posición inicial del fichero.
-
Si el valor de la posición actual es igual al número total de posiciones (cont) se finalizará el programa.
