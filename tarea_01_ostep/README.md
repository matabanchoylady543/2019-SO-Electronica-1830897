#Reporte acerca de lo realizado en cada item.

[mem.c](mem.c):

*En mem.c se tienen dos procesos pero cada vez que se ejecutan, surge
una dirección de memoria distinta, por lo tanto, se necesitaba
deshabilitar ASLR y obtener una dirección estatica, asi que se usa el
comando echo 0 > /proc/sys/kernel/randomize_va_space, pero no se logro
deshabilitar la aleatoriedad debido a que no se tenian permisos de
superusuario, por medio del comando sudo se logro entrar a la interfaz
de superusuario y modificar el ASLR desde su interior, al realizarlo, se
vuelve a ejecutar nuevamente mem.c y se logra obtener los dos procesos
pero ambos en la misma dirección.


[threads.c](threads.c):

*En este programa, se encontraba
