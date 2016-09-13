#include <stdio.h>

void numeroProcesos(char* procesos){
	FILE *archivo;
			char caracter[100];
			archivo = fopen("/proc/stat","r");
			char *p=NULL;

			if (archivo == NULL){

					printf("\nError de apertura del archivo. \n\n");
			        }else{


				    while (feof(archivo) == 0)
				    {
					 fgets(caracter, 100, archivo);

					p=strstr (caracter , "processes");

					if(p!=NULL)
							break;

				    }
				    strcpy(procesos,p);

	}

}
void cambioContexto(char* cambio){
	FILE *archivo;
		char caracter[100];
		archivo = fopen("/proc/stat","r");
		char *p=NULL;

		if (archivo == NULL){

				printf("\nError de apertura del archivo. \n\n");
		        }else{


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
	char procesos[30];
	cambioContexto(cambio);
	printf("Numero de cambios de contexto: %s",cambio);
	numeroProcesos(procesos);
	printf("Numero de procesos: %s",procesos);
	return 0;
}
