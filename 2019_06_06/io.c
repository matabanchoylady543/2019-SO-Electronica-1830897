#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
	char *archivo = argv[1];
	FILE *file = fopen(archivo,"rb");
	if (file == NULL)
	{
		printf("\n\nNo existe el archivo");
		fclose(file);
		exit(1);
	}
	else
	{	
		int cont =0;
		fseek(file,0,SEEK_SET);
		printf("\nTEXTO INGRESADO:\n");
    	while (!feof(file))
    	{	
    		char letra;
			letra = fgetc(file);
			printf("%c",letra);
			cont++;
		}
		fseek(file,-1,SEEK_END);
		printf("\n\nTEXTO PROCESADO:\n");
		int n = -1;
		while (ftell(file)>=0)
		{
			char letra;
			letra = fgetc(file);
			printf("%c",letra);
			n--;
			if (n == -cont)
			{
				printf("\n\nPrograma finalizado\n");
				return 0;
			}
			else 
			{
				fseek(file,n,SEEK_END);	
			}
		}
	}
}
