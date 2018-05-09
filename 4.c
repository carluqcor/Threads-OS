#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

//fgetc(*file) //Lee caracteres


typedef struct lane{
    char *f;
    int indices;
} lineas;


void *lineass(lineas *n){
int *lanes;
char s;
FILE *fin;
lanes=(int *)malloc(sizeof(int));
*lanes=1;
fin=fopen(n->f, "r");
printf("\nHilo %d:", n->indices);
	while((s=fgetc(fin))!=EOF){
		if(s=='\n'){
			*lanes=*lanes+1;
		}
	}
	fclose(fin);
	printf(" Numero de lineas del fichero actual: %d\n", *lanes);
	pthread_exit(lanes);
}

int main(int argc, char *argv[]){
	int i=0, j=0, lineasx=0, *lanes=0;
	pthread_t t[argc-1];
	lineas n[argc-1];
	for(i;i<(argc-1);i++){
		n[i].indices=i;
		n[i].f=argv[i+1];
		pthread_create(t+i, NULL, (void *) lineass, &(n[i]));
		usleep(10000);
	}
		for(j; j<(argc-1); j++){
			pthread_join(t[j], (void **) &lanes);
			lineasx+=*lanes;
		}
		printf("Numero de lineas total: %d\n", lineasx);
}