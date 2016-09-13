#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print_time (long time){
	const long minute = 60;
	const long hour = minute * 60;
	const long day = hour * 24;

	printf("%ldD:%ld:%02ld:%02ld\n",time / day, (time % day) / hour,
					(time % hour) / minute,time % minute);

}

void tiemposCpu(){
	FILE *archivo;
	//char caracter[100];
	//double userTime;
	//char *p=NULL;
	archivo = fopen("/proc/stat","r");

	float usuario, sistema, desuso;

	if (archivo == NULL){

		printf("\nError de apertura del archivo. \n\n");
	}

	else{


		printf("\nEl contenido del archivo es:\n");


		fscanf(archivo,"cpu %f %*f %f %f", &usuario, &sistema, &desuso);
		printf("usuario: ");
		print_time((long)usuario);
		printf("sistema: ");
		print_time((long)sistema);
		printf("desuso: ");
		print_time((long)desuso);

					

			}
		
	fclose(archivo);
	return;

}

int main(int argc, char **argv){

	tiemposCpu();

	return 0;
}