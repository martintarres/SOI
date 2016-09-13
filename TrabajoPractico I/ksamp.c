#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

	printf("%ldD:%ld:%02ld:%02ld\n",time / day, (time % day) / hour,
					(time % hour) / minute,time % minute);

}

void uptimeInfo(){
	FILE *fp;
double uptime;
fp = fopen("/proc/uptime","r");
fscanf(fp,"%lf\n",&uptime);
//printf("%lf\n",uptime);
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
int main(int argc, char **argv){
	char tipocpu[30];
	char modelocpu[50];
	char kernel[30];
	cpuInfo(tipocpu,modelocpu);
	printf("%s%s", tipocpu, modelocpu);
	 kernelInfo();

	uptimeInfo();
	archivosSoportados();
	return 0;
}
