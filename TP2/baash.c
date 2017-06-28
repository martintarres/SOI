#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>

int leerTeclado(char* argv[], char* ejecutar);
void unir(char* nombreCarpeta, char* paths[], char* direccion);
void obtenerPaths(char* paths[]);
int buscarArchivo(char* pants);
int esAmper(char* argv[]);
int chequearRedireccion(char* argv[], char nombreArchivo[]);
void salida(char nombreArchivo[]);
void entrada(char nombreArchivo[]);
int chequearPipe(char* argv[], char* argv1[], char* argv2[]);
void ejecutarPipe(char* argv1[], char* argv2[], char* paths[]);

int main(int argc, char *argv[]){

int pid, amper,esperarBandera,ejec;

char *paths[20];
obtenerPaths(paths);
char direccion[256]="";
char* argv1[20];
char* argv2[20];
char ejecutar[256]="";

	while(1){

		esperarBandera = 0;
		ejec = 0;
		int bandera = 0;
		int esPipe = 0;
		char fileName[50];

		fgets(ejecutar,256,stdin);
		argc=leerTeclado(argv, ejecutar);

		esPipe = chequearPipe(argv, argv1, argv2);
		bandera = chequearRedireccion(argv, fileName);

		amper= esAmper(argv);
		if(amper){
			argv[argc-1] = NULL;
			argc--;
		}

		if(!strcmp(argv[0],"exit")){
				printf("Usted presiono exit\n");
				return 0;
			}
			  if (!strcmp (argv[0],"cd")){
				//printf("cambiar de directorio\n");
				chdir(argv[1]);
				continue;
			 }


			unir(ejecutar, paths, direccion);

			if(direccion[0] == '0'){
				printf("Archivo no encontrado\n");
			}else {
				pid=fork();
				if (pid<0) {
					perror("Creando el hijo");
					exit(1);
				}

				else if(pid==0){


					if(bandera == 2){
						salida(fileName);
					}
					else if(bandera == 1){
						freopen(fileName,"r",stdin);
					}
					else if(esPipe == 1){
						ejecutarPipe(argv1, argv2, paths);
						ejec = 1;
					}
					if(!ejec){
						execv(direccion, argv);
						perror(direccion);
						exit(1);
					}
				}
					else{
						esperarBandera = -1;
					}
					if(amper)
						waitpid(pid,&esperarBandera,WNOHANG);
					else
						waitpid(pid,&esperarBandera,0);


						  }


	}
		return 0;
	}




int leerTeclado(char* argv[], char* ejecutar){
	int contador = 0;

	argv[0] = strtok(ejecutar, " \n");
	for(contador = 1; contador < 20; contador++){
		argv[contador] = strtok(NULL, " \n");
		if (argv[contador] == NULL)
			break;
	}
	return contador;
}

void unir(char* nombreCarpeta, char* paths[], char* direccion){
	char direc[50]="";
	int respuesta=0;

	if(nombreCarpeta[0] == '/' || (nombreCarpeta[0] == '.' &&
			nombreCarpeta[1] == '.' && nombreCarpeta[2] == '/')){

		respuesta=buscarArchivo(nombreCarpeta);
			if(respuesta==1){
				strcpy(direccion, nombreCarpeta);
			}else{
						direccion[0]= '0';
					}

		return ;
	} else if(nombreCarpeta[0] == '.' && nombreCarpeta[1] == '/'){

		char* direc1;

		getcwd(direc,50);
		direc1=strtok(nombreCarpeta,"/");
		direc1 = strtok(NULL,"/");

		respuesta=buscarArchivo(direc1);
		if(respuesta==1){
			strcpy(direccion, direc1);
		}else{
					direccion[0]= '0';
				}
	}
	else {

	for(int i=0;i<8;i++){

		strcpy(direc,paths[i]);
		strcat(direc,"/");

		strcat(direc, nombreCarpeta);

		respuesta=buscarArchivo(direc);
		if(respuesta==1){

			strcpy(direccion, direc);


			break;
		}else{
			direccion[0]= '0';
		}

	}
	}
}


int buscarArchivo(char* panths){

	FILE *archivo;
	archivo = fopen(panths,"rb");
	if (archivo == NULL){

		return 0;

	}
	fclose(archivo);
		return 1;

}



void obtenerPaths(char* paths[]){
	int contadorPath;
	char* variablePath = getenv("PATH");
	paths[0] = strtok(variablePath, ":");
	for(contadorPath = 1; contadorPath< 20; contadorPath++){
		paths[contadorPath] = strtok(NULL,":");

		if (paths[contadorPath] == NULL)
			break;
	}

	strtok(NULL,":");

}

int esAmper(char* argv[]){
	int i;

		for(i = 0; i < 20; i++){
			if(argv[i] == NULL)
				break;
		}
		if(!strcmp(argv[i-1], "&"))
			return 1;
		return 0;
}

int chequearRedireccion(char* argv[], char nombreArchivo[]){
	int i;
	for (i = 0; i < 20; i++){

		if(argv[i] == NULL){
			nombreArchivo = NULL;
			return 0;
		}
		else if (!strcmp(argv[i], "<")){

			strcpy(nombreArchivo, argv[i+1]);

			argv[i] = NULL;
			argv[i+1] = NULL;

			return 1;
		}
		else if (!strcmp(argv[i], ">")){
			strcpy(nombreArchivo, argv[i+1]);
			argv[i] = NULL;
			argv[i+1] = NULL;
			return 2;
		}
	}

	return 0;
}


void salida(char nombreArchivo[]){
	int fid;
	int banderas,permiso;
	banderas = O_WRONLY|O_CREAT|O_TRUNC;
	permiso = S_IWUSR|S_IRUSR;

	fid = open(nombreArchivo, banderas, permiso);
	if (fid<0) {
		perror("open");
		exit(1);
	}

	close(STDOUT_FILENO);
	if (dup(fid)<0) {
		perror("dup");
		exit(1);
	}

	close(fid);

	}

void entrada(char nombreArchivo[]){
int fid;
int banderas,permiso;
banderas = O_RDONLY;
permiso = S_IWUSR|S_IRUSR;

close(STDIN_FILENO);
fid = open(nombreArchivo, banderas, permiso);
if (fid<0) {
	perror("open");
	exit(1);
}

if (dup(fid)<0) {
	perror("dup");
	exit(1);
}

close(fid);

}

int chequearPipe(char* argv[], char* argv1[], char* argv2[]){
	int indexArg, aux, indexArg2;

	for(indexArg = 0; argv[indexArg] != NULL; indexArg++){
		aux = strcmp("|", argv[indexArg]);
		if(aux == 0)
			break;
		argv1[indexArg] = (char*) malloc ( strlen(argv[indexArg] + 1) ) ;
		strcpy(argv1[indexArg], argv[indexArg]);
	}

	argv1[indexArg] = '\0';


	if(argv[indexArg] == NULL)
		return 0;

	indexArg++;

	for(indexArg2 = 0; argv[indexArg] != NULL; indexArg2++){

		if(argv[indexArg] == NULL)
			break;
		argv2[indexArg2] = (char*) malloc ( strlen(argv[indexArg] + 1) ) ;
		strcpy(argv2[indexArg2], argv[indexArg]);
		indexArg++;
	}

	argv2[indexArg2] = '\0';

	return 1;
}


void ejecutarPipe(char* argv1[], char* argv2[], char* paths[]){
	char ejecutaPath[256];

	int fd[2];
	pipe(fd);
	if (fork()==0) {
		close(fd[0]);
		dup2(fd[1],1);
		close(fd[1]);
		unir(argv1[0], paths, ejecutaPath);
		execv(ejecutaPath, argv1);
		perror(ejecutaPath);
		exit(1);
	}

	else {
		close(fd[1]);
		dup2(fd[0],0);
		close(fd[0]);
		unir(argv2[0], paths, ejecutaPath);
		execv(ejecutaPath, argv2);
		perror(ejecutaPath);
		exit(1);
	}
}
