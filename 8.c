#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#define Productor 5
#define Acciones 20

pthread_mutex_t semaphoreBin = PTHREAD_MUTEX_INITIALIZER;

int camiseta[5]={0,0,0,0,0};
int iterador=0;

void *repone(){
	int posicion=0,itAcciones=0, cantidad;
it
	while(itAcciones<Acciones){
		usleep(50000);
		pthread_mutex_lock(&semaphoreBin); 

		if(iterador!=5){
//El stock nunca será mayor de 100 ya que es su máximo
			if(camiseta[posicion]<100){
//La cantidad que se produce es aleatoria siendo proporcional a la que falta para llenar el stock
				cantidad=rand()%(100-camiseta[posicion]);
				printf("Se producen %d camisetas para el tipo %d\n", cantidad, posicion);
//Se suman las camisetas que habia antes a las que se producen
				camiseta[posicion]=camiseta[posicion]+cantidad;
				posicion=(posicion+1)%Productor;
				iterador++;
				itAcciones++;
			}else{
				printf("La cantidad de camiseta de este modelo %d ya está en su stock máximo\n", posicion);
				posicion=(posicion+1)%Productor;
				itAcciones++;
			}	
		}
		pthread_mutex_unlock(&semaphoreBin); 
	}
	pthread_exit(NULL);
}

void *compra(){
	int posicion=0,itAcciones=0, cantidad;

	while(itAcciones<Acciones){
		usleep(50000);
		pthread_mutex_lock(&semaphoreBin); 

		if(iterador!=0){
//Si el numero de camisetas es menor o igual a 0 no se podrá comprar camisetas de ese modelo y pasarña a la siguiente acción
		if(camiseta[posicion]<=0){
			posicion=(posicion+1)%Productor;
			itAcciones++;
		}else{
			cantidad=rand()%camiseta[posicion];
			printf("Se compran %d camisetas del tipo %d\n", cantidad, posicion);
			camiseta[posicion]=camiseta[posicion]-cantidad;
			posicion=(posicion+1)%Productor;
			iterador--;
			itAcciones++;
		}
	}
		pthread_mutex_unlock(&semaphoreBin);

}
	pthread_exit(NULL);
}


int main(){
	srand(time(NULL));
	pthread_t t1,t2;
	int i;

	for(i=0;i<Productor;i++) printf("El modelo %d tiene: %d camisetas\n", i, camiseta[i]);
		printf("\n");
	
	pthread_create(&t1, NULL, (void *)repone, NULL);
	pthread_create(&t2, NULL, (void *)compra, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	printf("\nEl stock final de camisetas es:");
	printf("\n");
	for(i=0;i<Productor;i++) printf("El modelo %d tiene: %d camisetas\n", i, camiseta[i]);
		printf("\n");
//Al final del programa se debe destruir el semáforo al igual que una reserva de memoria hay que liberarla
	pthread_mutex_destroy(&semaphoreBin);
	return 0;
}

