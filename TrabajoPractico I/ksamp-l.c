#include <stdio.h>

void memoriaTotal(char* memTotal){
				FILE *archivo;
				char caracter[100];
				archivo = fopen("/proc/meminfo","r");
				char *p=NULL;

				if (archivo == NULL){

						printf("\nError de apertura del archivo. \n\n");
				        }else{


					    while (feof(archivo) == 0)
					    {
						 fgets(caracter, 100, archivo);

						p=strstr (caracter , "MemTotal:");

						if(p!=NULL)
								break;

					    }
					    strcpy(memTotal,p);

		}

}
void memoriaDisponible(char* memDispo){
				FILE *archivo;
				char caracter[100];
				archivo = fopen("/proc/meminfo","r");
				char *p=NULL;

				if (archivo == NULL){

						printf("\nError de apertura del archivo. \n\n");
				        }else{


					    while (feof(archivo) == 0)
					    {
						 fgets(caracter, 100, archivo);

						p=strstr (caracter , "MemAvailable:");

						if(p!=NULL)
								break;

					    }
					    strcpy(memDispo,p);

		}

}
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
					 //  printf("%u\n", lecturas);
					 //  printf("%u\n", escrituras);
					   printf("Total de lecturas pedidas a disco :%u", total);
					   printf("\n");
		}

	}


int main(int argc, char **argv){
	char memTotal[50];
	char memDispo[100];
	peticionesDisco();
	memoriaTotal(memTotal);
	printf("%s",memTotal);
	memoriaDisponible(memDispo);
	printf("%s",memDispo);
}
