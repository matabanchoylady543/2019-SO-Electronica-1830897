
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  printf("Hola mundo y variable padre es: \n");
  printf("%s \n", getenv("PARENT"));
  
}

