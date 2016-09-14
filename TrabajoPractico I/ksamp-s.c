#include <stdio.h>
#include <time.h>
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

void horaInicio(char* hinicio){
	FILE *archivo;
		char caracter[100];
		archivo = fopen("/proc/stat","r");
		char inicio[100];
		time_t btime;
		unsigned int aux;

		if (archivo == NULL){

				printf("\nError de apertura del archivo. \n\n");
		        }else{


			    while (feof(archivo) == 0)
			    {
				 fgets(caracter, 100, archivo);


				 sscanf(caracter, "btime %u", &aux);
				 btime=(time_t)aux;


			    }
			    strftime(inicio,sizeof(inicio),"%c", localtime(&btime));
			    printf("Horario Inicio: %s \n", inicio);


}
}
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
	char cambio[30];
	char procesos[30];
	char hinicio[30];
	tiemposCpu();
	cambioContexto(cambio);
	printf("Numero de cambios de contexto: %s",cambio);
	horaInicio(hinicio);
	numeroProcesos(procesos);
	printf("Numero de procesos: %s",procesos);





}
