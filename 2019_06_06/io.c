#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]) {
    //open es una funcion usada para apuntar a una ruta su primer parametro
   //es una ruta, su segundo parametro es los permisos que utiliza
    //su tercere parametro son los permisos que tendra el archivo
    int fd = open("/tmp/file", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    //assert es una funcion que retorna true o false dependiendo de la condicion
    //que reciba como primer parametro
    assert(fd >= 0);
    //se declara una variable char en el buffer con espacio para 20 bytes
    char buffer[20];
    //sprintf imprime una cadena la cual no saldra en el output sino que se guardara en el buffer
    //en este caso hello world
    sprintf(buffer, "%s", argv[1]);
    //write escribe en un archivo, el primer parametro recibe un descriptor de archivo
    //el segundo parametro recibe el buffer el cual contiene impreso el mensaje
    //el tercer parametro recibe el tamaño de la cadena a escribir 
    //strlen es una funcion que recibe una cadena en este caso la del buffer y retorna el tamaño de esta
    int rc = write(fd, buffer, strlen(buffer));
    assert(rc == (strlen(buffer)));
    //fsync descarga en el archivo las intrucciones propuestas anteriormente usando la propia referencia
    //en este caso fd
    fsync(fd);
    //cierra el archivo, recibe la referencia para cerrarlo
    close(fd);
    return 0;
}

