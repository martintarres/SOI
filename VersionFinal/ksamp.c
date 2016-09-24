/**
*Ksamp.
*Muestra de diversass formas algun subconjunto de la 
*informacion disponible en /proc.
*/

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

/**
*main con parametros
*@param arg un numero entero correspondiente a la cantidad de
*		argumentos introducidos
*@param argv array de puntero a carateres segun el cual
*       se muestra distinta informacion. 
*/

int main(int argc, char **argv)
{
	
	int sflag = 0;
    int lflag = 0;
    int a,b,c;

	char cambio[30];
	char procesos[30];
	char hinicio[30];
	char memTotal[50];
	char memDispo[100];



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
			sscanf(argv[2],"%d",&a);
			sscanf(argv[3],"%d",&b);
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

/**
*Llama a los metodos correspondientes para imprimir el nombre de la maquina
*fecha y hora actuales
*tipo y modelo de CPU
*version del kernel
*cantidad de tiempo transcurrido desde que se inicio el sistema
*cantidad de sistemas de arichivos soportados por el kernel.
*/
void infoDefault()
{	
	char tipocpu[30];
	char modelocpu[50];

	nombreMaquina();
	fechaHoraActual();
	cpuInfo(tipocpu,modelocpu);
	printf("%s%s", tipocpu, modelocpu);
	kernelInfo();
	uptimeInfo();
	archivosSoportados();
	return;
}
/**
*Imprime el nombre de la maquina segun lo tomado del archivo hostname
*/
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

 	fclose(archivo);
 	
 	return;
}
/**
*Imprime la fecha y hora actual segun lo tomado del archivo rtc
*/

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

/**
*Imprime el tipo y modelo de cpu segun lo tomado del archivo cpuinfo
*/

void cpuInfo(char* tipocpu,char* modelocpu)
{
	FILE *archivo;
	char caracter[100];
	archivo = fopen("/proc/cpuinfo","r");
	char *p=NULL;
	char *g=NULL;


	if (archivo == NULL)
	{
		printf("\nError de apertura del archivo. \n\n");
    }
	else
	{

	    printf("\nEl contenido del archivo es:\n");

	    while (feof(archivo) == 0)
	    {
			fgets(caracter, 100, archivo);

			p=strstr (caracter , "vendor_id");

			if(p!=NULL)	break;

		}
	    strcpy(tipocpu,p);
	    while (feof(archivo) == 0)
	    {
			fgets(caracter, 100, archivo);
			g=strstr (caracter , "model name");
			if(g!=NULL) break;
	    }
	    fclose(archivo);
	    strcpy(modelocpu, g);
	    strcpy(modelocpu,g);
	}
	return;
 }

 /**
 *Imprime la version del kernel segun lo tomado del archivo osrelease
 */

 void kernelInfo()
 {
	FILE *archivo;
	char caracter;

	archivo = fopen("/proc/sys/kernel/osrelease","r");

	if (archivo == NULL)
	{
 		printf("\nError de apertura del archivo. \n\n");
	}
	else
	{
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


/**
*Conversor de tiempo.
*Imprime el tiempo que recive como dias, horas, minutos y segundos.
*@param time un numero del tipo long que representa el tiempo a convertir
*/
void print_time (long time){

	const long minute = 60;
	const long hour = minute * 60;
	const long day = hour * 24;

	printf("%ld days, %ld:%02ld:%02ld\n", time / day,
		(time % day) / hour, (time % hour) / minute, time % minute);
	
	return;
}

/**
*Imprime el tiempo transcurrido desde que se inicio el sistema
*a partir de lo tomado del archivo uptime.
*/
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

/**
*Imprime la cantidad de archivos soportados por el kernel 
*a partir de lo tomado del archivo filesystems.
*/
void archivosSoportados()
{
	FILE *archivo;
 	char caracter;
 	int lin=0;

	archivo = fopen("/proc/filesystems","r");

	if (archivo == NULL)
	{
		printf("\nError de apertura del archivo. \n\n");
	}
	else
	{
 	    while (feof(archivo) == 0)
 	    {
	 		caracter = fgetc(archivo);
	 		if(caracter=='\n')
	 		{
	 			lin++;
	 		}
 	//	printf("%c",caracter);
    	}
   	}
   	printf("El numero de archivos soportados: %u\n",lin);
	fclose(archivo);
	return ;
}

/**
*Imprime la cantidad de procesos creados desde que se inicio el sistema
*a partir de lo tomado del archivo stat.
*@param procesos puntero del tipo char 
*/
void numeroProcesos(char* procesos)
{
	FILE *archivo;
	char caracter[100];
	archivo = fopen("/proc/stat","r");
	char *p=NULL;

	if (archivo == NULL)
	{
		printf("\nError de apertura del archivo. \n\n");
    }
	else
	{
	    while (feof(archivo) == 0)
	    {
	     	fgets(caracter, 100, archivo);
			p=strstr (caracter , "processes");

			if(p!=NULL)	break;

	    }
	    strcpy(procesos,p);
	}

 	fclose(archivo);

	return;
}

/**
*Imprime la cantidad de cambios de contexto producidos a partir
*de lo tomado del archivo stat.
*@param cambio puntero del tipo char
*/
void cambioContexto(char* cambio)
{
	FILE *archivo;
	char caracter[100];
	archivo = fopen("/proc/stat","r");
	char *p=NULL;

	if (archivo == NULL)
	{
		printf("\nError de apertura del archivo. \n\n");
	}
	else
	{

	    while (feof(archivo) == 0)
		    {
				fgets(caracter, 100, archivo);
				p=strstr (caracter , "ctxt");

				if(p!=NULL) break;
			}
	    strcpy(cambio,p);
	}

 	fclose(archivo);

	return;
}

/**
*Imprime la hora en la que se inicio el sistema a partir de
*lo tomado del archivo stat.
*/
void horaInicio(char* hinicio)
{
	FILE *archivo;
	char caracter[100];
	archivo = fopen("/proc/stat","r");
	char inicio[100];
	time_t btime;
	unsigned int aux;

	if (archivo == NULL)
	{

		printf("\nError de apertura del archivo. \n\n");
	}
	else
	{
		while (feof(archivo) == 0)
		    {
				fgets(caracter, 100, archivo);
				sscanf(caracter, "btime %u", &aux);
				btime=(time_t)aux;
			}
	    strftime(inicio,sizeof(inicio),"%c", localtime(&btime));
	    printf("Horario Inicio: %s \n", inicio);
	}

	fclose(archivo);

	return;
}

/**
*Imprime la cantidad de tiempo de CPU utilizado para usuarios, sistema
*y proceso idle a partir de lo tomado del archivo stat.
*/
void tiemposCpu()
{
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
/**
*Imprime la cantidad de memoria configurada en el hardware a partir
*de lo tomado del archivo meminfo.
*@param memTotal puntero a caracter
*/
void memoriaTotal(char* memTotal)
{
 	FILE *archivo;
	char caracter[100];
	archivo = fopen("/proc/meminfo","r");
	char *p=NULL;

	if (archivo == NULL)
	{
		printf("\nError de apertura del archivo. \n\n");
	}
	else
	{

	    while (feof(archivo) == 0)
		    {
				fgets(caracter, 100, archivo);
				p=strstr (caracter , "MemTotal:");

				if(p!=NULL)	break;
			}
		strcpy(memTotal,p);

	}

	fclose(archivo);

	return;
}
		
/**
*Imprime la cantidad de memoria disponible a partir de lo tomado del 
*archivo meminfo.
*/

void memoriaDisponible(char* memDispo){
	FILE *archivo;
	char caracter[100];
	archivo = fopen("/proc/meminfo","r");
	char *p=NULL;

	if (archivo == NULL)
	{
		printf("\nError de apertura del archivo. \n\n");
	}
	else
	{
	    while (feof(archivo) == 0)
	    {
			fgets(caracter, 100, archivo);

			p=strstr (caracter , "MemAvailable:");

			if(p!=NULL) break;

		}
		strcpy(memDispo,p);

	}
	fclose(archivo);
	return;
}

/**
*Imprime la cantidad de peticiones a disco realizadas a partir
*de lo tomado del archivo disckstats.
*/
void peticionesDisco()
{
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
					   sscanf(p,"sda %d", &lecturas);
					   sscanf(p,"sda %*d %*d %*d %*d %d", &escrituras);
					   total=lecturas + escrituras;
					 //  printf("%u\n", lecturas);
					 //  printf("%u\n", escrituras);
					   printf("Total de lecturas pedidas a disco :%u", total);
					   printf("\n");
		}

		fclose(archivo);

		return;

	}

/**
*Imprime una lista de promedios de carga en un minuto a partir
*de lo tomado del archivo loadvg.
*/
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
