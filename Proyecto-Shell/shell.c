#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

char *borrarespacios(char *s){
  char *start = s;
  while(*start && isspace(*start))
    ++start;
  char *contador = start;
  char *end = start;
  while(*contador){
    if(!isspace(*(contador++)))
      end = contador;
  }
  *end = 0;
  return start;
}

char *cadenasalida(char *comando){
	char *out;
  char cadena[2] = ">";
	char *tk;
	tk = strtok(comando, cadena);
	out = tk;
	tk = strtok(NULL, cadena);
	if (tk != NULL){
		tk = borrarespacios(tk);
		int file = open(tk, O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR);
		dup2(file,STDOUT_FILENO);
		close(file);
	}
	return out;
}
char *cadenaentrada(char *comando){
	char *in;
	char cadena[2] = "<";
	char *tk;
	tk = strtok(comando, cadena);
	in = tk;
	tk = strtok(NULL, cadena);
	if (tk != NULL){
		tk = borrarespacios(tk);
		int file = open(tk, O_RDONLY);
		dup2(file,STDIN_FILENO);
		close(file);
	}
	return in;
}

void argumentos(char *comando, char **args){
  char cadena[2] = " ";
  char *tk;
  tk = strtok(comando, cadena);
  tk = borrarespacios(tk);
  args[0] = tk;
  tk = strtok(NULL, cadena);
  int contador = 1;
  while( tk != NULL ) {
    tk = borrarespacios(tk);
    args[contador] = tk;
    tk = strtok(NULL, cadena);
    contador++;
  }
  args[contador] = NULL;
}
void delimitarcadena(char str[], char substr[], int p){
  int z = 0;
  while (z < strlen(str)){
    substr[z] = str[p+z];
    z++;
  }
  substr[z] = '\0';
}

void shellenviron(char* argv0){
  
  char nombre[90];
  delimitarcadena(argv0,nombre,1);

  char cwd[200];
  getcwd(cwd, sizeof(cwd));
  strcat(cwd, nombre);
  setenv("SHELL", cwd, 1);
}

int main(int argc, char** argv){

int bandera;
int ifinal;
int contador =0;
char comandos[80][40];

if (argv[1] != NULL){
  bandera = 1;
  FILE *archivo;
  char caracteres[100];
  archivo = fopen(argv[1],"r");

  if (archivo == NULL)
    exit(1);
  else{
    while(feof(archivo) == 0){
      fgets(caracteres,100,archivo);
      strcpy(comandos[contador], caracteres);
      contador++;
    }	    
    ifinal = contador;
  }
  fclose(archivo);
}
else
  bandera = 0;

pid_t pid;
char comando[150];
char cd[150];
shellenviron(argv[0]);
contador = 0;
while (1){
  if(bandera){
    if(contador==ifinal)
      exit(0);
    strcpy(comando, comandos[contador]);
    contador++;
  }
  else{
    printf("Entrada> ");
    gets(comando);	
  }

  if(strcmp(comando,"quit") == 0)
    exit(0);
  else if(strcmp(comando,"help more")==0){
    puts("contador. cd <directory>: cambia el directorio predeterminado actual a <directory>. Si el");
    puts("El argumento <directorio> no está presente, informa el directorio actual.");
    puts("clr - Borrar la pantalla.");
    puts("dir <directory> - Lista los contenidos del directorio <directory>.");
    puts("environ - Lista todas las cadenas de entorno.");
    puts("echo <comment> - Muestra <comment> en la pantalla seguido de una nueva línea");
    puts("help more - Muestra el manual del usuario.");
    puts("pause - Pausa la operación del shell hasta que se presione 'Enter'.");
    puts("quit- Salir de la shell. ");
    puts("La entrada de la línea de comandos se interpreta como invocación del programa. ");
    puts("Si el shell se invoca con un argumento de línea de comando:");
    puts("myshell batchfile");
    puts("se asume que el archivo de proceso por lotes contiene un conjunto de líneas de comando para que el shell procese.");
    puts("Cuando se llega al final del archivo, la salida del shell. ");
    puts("El shell es compatible con la redirección de contador/o en uno o ambos stdin y/o stdout.");
    puts("Es decir, la línea de comando.");
    puts("programname arg1 arg2 <inputfile> outputfile");
    puts("ejecutará el programa programname con los argumentos arg1 y arg2, el stdin");
    puts("Secuencia de FILE reemplazada por inputfile y la transmisión de stdout FILE reemplazada por");
    puts("archivo de salida.");
  }
  else if (strcmp(comando,"dir") == 0)
    system("ls");
  else if(strcmp(comando,"cd") == 0)
    system("pwd");
  else if(strncmp(comando,"cd ",3) == 0){
    delimitarcadena(comando, cd, 3);
    if(strcmp(comando,"cd")==0)
      system("pwd");
    else  if (chdir(cd) != 0){
      
      printf("No se encuentra el directorio %s \n", cd);
    }
  }
  else if(strncmp(comando,"echo",4)==0)
    system(comando);
  else if (strcmp(comando, "clr") == 0)
    system("clear");
  else if(strncmp(comando,"pause",4)==0){
    char enter;
    enter = getchar();
  }
  else if(strcmp(comando,"environ")==0)
    system("printenv");
  else{
    pid = fork();
    if (pid == 0){
      char *despues_out = cadenasalida(comando);
      char *despues_in  = cadenaentrada(despues_out);
      char *args[100];
      argumentos(despues_in, args);

      char *sh = getenv("SHELL");
      char shx[80];
      sprintf(shx, "parent=%s", sh);
      char *x[] = {shx, NULL};

      int exe;
      exe = execvpe(args[0], args, x);
      if(exe == -1)
        exit(0);
    }
    else
      wait(NULL);
  } 	
}
}
