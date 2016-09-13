#include <stdio.h>

void peticionesDisco(){
	FILE *archivo;
				char caracter[100];
				archivo = fopen("/proc/diskstats","r");
				char *p=NULL;
				//char *g=NULL;
				int lecturas;
				int escrituras;
				int total;
				if (archivo == NULL){

						printf("\nError de apertura del archivo. \n\n");
				        }else{


					    while (feof(archivo) == 0)
					    {
						 fgets(caracter, 100, archivo);

						p=strstr (caracter , "sda ");

						if(p!=NULL)
								break;

					    }
					   sscanf(p,"sda %u", &lecturas);
					   sscanf(p,"sda %*u %*u %*u %*u %u", &escrituras);
					   total=lecturas + escrituras;
					   printf("%u\n", lecturas);
					   printf("%u\n", escrituras);
					   printf("Total de lecturas pedidas a disco:%u", total);
					   printf("\n");
		}

	}


int main(int argc, char **argv){
	//char pedidosDisco[100];
	peticionesDisco();
//	printf("Numero de pedidos a disco: %s",pedidosDisco);
}
