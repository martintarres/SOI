#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void cpuInfo(char* tipocpu,char* modelocpu);
void kernelInfo();
void print_time (long time);
void uptimeInfo();
void archivosSoportados();
void numeroProcesos(char* procesos);
void cambioContexto(char* cambio);
void horaInicio(char* hinicio);
void tiemposCpu();
void memoriaTotal(char* memTotal);
void memoriaDisponible(char* memDispo);
void peticionesDisco();
void promedioDeCarga();
void infoDefault();
void nombreMaquina();
void fechaHoraActual();

int main(int argc, char **argv)
{
	
	int sflag = 0;
    int lflag = 0;
    int a,b,c;

    //cambiar las funciones para que no reciban parametros.



	char cambio[30];
	char procesos[30];
	char hinicio[30];
	char memTotal[50];
	char memDispo[100];

	//hasta aca no irian los char[]



	while ((c = getopt (argc, argv, "sl:")) != -1)
   		switch (c)
      	{
      		case 's':
        		sflag = 1;
        		break;
      		case 'l':
      			if(argc==4)
      			{
        			sflag = 1;
        			lflag = 1;
        			break;
      			}
        		else
        		{
        			printf("Las opciones son -s y -l a b, siendo a y b numeros enteros.\n");
        			return 0;
        		}
      		default:
       	 		printf("Las opciones son -s y -l a b, siendo a y b numeros enteros.\n");
       	 		return 0;
		}


	infoDefault();

	if(sflag==1)
	{
		cambioContexto(cambio);
		printf("Numero de cambios de contexto: %s",cambio);
		horaInicio(hinicio);
		numeroProcesos(procesos);
		printf("Numero de procesos: %s",procesos);

		if(lflag==1)
		{	
			sscanf(argv[2],"%u",&a);
			sscanf(argv[3],"%u",&b);
			int contador=0;

			while(contador<=b)
			{
				peticionesDisco();
				memoriaTotal(memTotal);
				printf("%s",memTotal);
				memoriaDisponible(memDispo);
				printf("%s",memDispo);
				promedioDeCarga();
				sleep(a);
				contador=contador+a;
			}
		}
	}

	return 0;
}


void infoDefault()
{	
	//MODIFICAR FUNCIONES PARA QUE NO LLEVEN PARAMETROS CHAR[]
	char tipocpu[30];
	char modelocpu[50];
//	char kernel[30];

	nombreMaquina();
	fechaHoraActual();
	cpuInfo(tipocpu,modelocpu);
	printf("%s%s", tipocpu, modelocpu);
	kernelInfo();
	uptimeInfo();
	archivosSoportados();
	return;
}

void nombreMaquina()
{	
	FILE *archivo;
 	archivo = fopen("/proc/sys/kernel/hostname","r");
 	char nombre[100];

 	if (archivo == NULL)
	{
		printf("\nError de apertura del archivo. \n\n");
	}

 	fscanf(archivo, "%[^\n]s", nombre);
 	printf("Nombre de la maquina: %s\n",nombre);
 	
 	return;
}

void fechaHoraActual()  
{
	FILE *archivo;
 	archivo = fopen("/proc/driver/rtc","r");
 	char cadena[100];
 	char fecha[20];
 	char hora[20];
	char *p=NULL;
	char *h=NULL;

	if (archivo == NULL)
	{
		printf("\nError de apertura del archivo. \n\n");
	}

	while(feof(archivo)==0)
	{
		fgets(cadena,100,archivo);
		h=strstr(cadena, "rtc_time");
		if(h!=NULL) break;
	}

	strcpy(hora, h);

	sscanf(cadena, "rtc_time  : %s", hora);

	while(feof(archivo)==0)
	{
		fgets(cadena,100,archivo);
		p=strstr(cadena, "rtc_date");
		if(p!=NULL) break;
	}

	strcpy(fecha, p);

	sscanf(cadena, "rtc_date  : %s", fecha);

	fclose(archivo);

	printf("Fecha: %s\n",fecha);
	printf("Hora: %s\n", hora);

	return;
}

void cpuInfo(char* tipocpu,char* modelocpu){
		FILE *archivo;
		char caracter[100];
		archivo = fopen("/proc/cpuinfo","r");
		char *p=NULL;
		char *g=NULL;


		if (archivo == NULL){

			printf("\nError de apertura del archivo. \n\n");
	        }else{


		    printf("\nEl contenido del archivo es:\n");

		    while (feof(archivo) == 0)
		    {
			 fgets(caracter, 100, archivo);

			p=strstr (caracter , "vendor_id");

			if(p!=NULL)
					break;

		    }
		    strcpy(tipocpu,p);
		    while (feof(archivo) == 0)
		    		    {
		    			 fgets(caracter, 100, archivo);

		    			g=strstr (caracter , "model name");

		    			if(g!=NULL)
		    					break;

	        }
	        fclose(archivo);

	       strcpy(modelocpu, g);
	        strcpy(modelocpu,g);


	        return;
	}
 }

 void kernelInfo(){
	 	 FILE *archivo;
	 	char caracter;

	 	archivo = fopen("/proc/sys/kernel/osrelease","r");

	 	if (archivo == NULL){

	 		printf("\nError de apertura del archivo. \n\n");
	         }else{
	        	 printf("Kernel: ");
	 	    while (feof(archivo) == 0)
	 	    {
	 		caracter = fgetc(archivo);
	 		printf("%c",caracter);
	 	    }
	         }
	         fclose(archivo);
	 	return ;
	 }


void print_time (long time){

	const long minute = 60;
	const long hour = minute * 60;
	const long day = hour * 24;

	printf("%ld days, %ld:%02ld:%02ld\n", time / day,
		(time % day) / hour, (time % hour) / minute, time % minute);
	
	return;
}

void uptimeInfo()
{
	FILE *fp;
	double uptime;
	fp = fopen("/proc/uptime","r");

	fscanf(fp,"%lf\n",&uptime);
	printf("Hora de inicio: ");
	print_time(uptime);

	fclose (fp);

	return;
}
void archivosSoportados(){
			FILE *archivo;
		 	char caracter;
		 	int lin=0;

		 	archivo = fopen("/proc/filesystems","r");

		 	if (archivo == NULL){

		 		printf("\nError de apertura del archivo. \n\n");
		         }else{

		 	    while (feof(archivo) == 0)
		 	    {
		 		caracter = fgetc(archivo);
		 		if(caracter=='\n'){ lin++;}
		 	//	printf("%c",caracter);
		 	    }
		         }
		 	printf("El numero de archivos soportados: %u\n",lin);
		         fclose(archivo);
		 	return ;
}
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
return;
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
return;
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
return;
}
void tiemposCpu(){
 	FILE *archivo;
 	archivo = fopen("/proc/stat","r");
 	float usuario, sistema, desuso;

 	if (archivo == NULL)
 	{
 		printf("\nError de apertura del archivo. \n\n");
 	}

 	else
 	{
 		fscanf(archivo,"cpu %f %*f %f %f", &usuario, &sistema, &desuso);
 		printf("Tiempo de usuario: ");
 		print_time((long)usuario/100);
 		printf("Tiempo de sistema: ");
 		print_time((long)sistema/100);
 		printf("Tiempo de desuso: ");
 		print_time((long)desuso/100);
 	}

 	fclose(archivo);
 	return;

 }

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
		return;
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
return;
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

		return;

	}

void promedioDeCarga()
{
	FILE *archivo;
 	archivo = fopen("/proc/loadavg","r");
 	float carga;

 	if (archivo == NULL)
 	{
 		printf("\nError de apertura del archivo. \n\n");
 	}

 	else
 		{
 		fscanf(archivo,"%f", &carga);
 		printf("Promedio de Carga en un minuto: %f\n", carga);
 		}

 	fclose(archivo);
 	return;
}
