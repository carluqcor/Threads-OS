#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>

int num=0;

void *contador(){
	int i;
	for (i=0; i<100; i++){
		num++;
	}
	printf("contador=%d\n\n", num);
}


int main(){
	int value, nHilos, *recuento, i, j;
	printf("Indique el numero de hilos: ");
	scanf("%d",&nHilos);

	pthread_t t[nHilos];	
	for(i=0; i<nHilos; i++){
		value=pthread_create( &(t[i]), NULL, (void *)contador, NULL);
		if(value!=0){
			printf("Error creando las hebras\n");
			exit(EXIT_FAILURE);
		}
	}
	for(j=0; j<nHilos; j++){
		value=pthread_join(t[j], NULL);
		if(value!=0){
			printf("Error esperando a las hebras o sobrecarga de hebras en la pila\n");
			exit(EXIT_FAILURE);
		}
	}
	printf("CONTADOR: %d\n", num);
}


