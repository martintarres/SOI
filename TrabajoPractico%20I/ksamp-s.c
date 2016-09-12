#include <stdio.h>

void cambioContexto(char* cambio){
	FILE *archivo;
		char caracter[100];
		archivo = fopen("/proc/stat","r");
		char *p=NULL;

		if (archivo == NULL){

				printf("\nError de apertura del archivo. \n\n");
		        }else{


			    printf("\nEl contenido del archivo es:\n");

			    while (feof(archivo) == 0)
			    {
				 fgets(caracter, 100, archivo);

				p=strstr (caracter , "ctxt");

				if(p!=NULL)
						break;

			    }
			    strcpy(cambio,p);

}
}


int main(int argc, char **argv){
	char cambio[30];
	cambioContexto(cambio);
	printf("%s",cambio);
	return 0;
}
