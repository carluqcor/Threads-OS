#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define productores 3
#define compradores 3
#define vectorTam 5
#define Acciones 5

pthread_mutex_t semaphoreGen = PTHREAD_MUTEX_INITIALIZER;
int buffer[vectorTam];
sem_t sem_finFunc; //Buffer rellenado
sem_t sem_inicioFun; //BUffer sin rellenar

void *productor(void *productor_consumidor){
	int i, elemento;

    for (i=0;i<Acciones;i++){
        elemento=rand()%50;

//Este semáforo sirve para esperar si el elemento del buffer está vació
        sem_wait(&sem_inicioFun);
//Este semáforo bloquea si el hilo está en ejecución
        pthread_mutex_lock(&semaphoreGen);
    
        buffer[i]=buffer[i]+elemento;
      	printf("El productor %d, implementa %d nuevos elementos en el buffer %d\n", (int)productor_consumidor, elemento, i);
//Este semáforo libera si el hilo a acabado su ejecución
        
        pthread_mutex_unlock(&semaphoreGen);
        sem_post(&sem_finFunc);
     
        sleep(1);	//Si no hacemos este sleep, se solaparán los productores y compradores
    }
}

void *compra(void *productor_consumidor){
	int i, elemento;

    for (i=0;i<Acciones;i++) {
        
        sem_wait(&sem_finFunc);
        pthread_mutex_lock(&semaphoreGen);

        elemento=rand()%buffer[i];
        buffer[i]=buffer[i]-elemento;
   		printf("El consumidor %d, adquiere %d elementos del buffer %d\n", (int)productor_consumidor, elemento, i);

        pthread_mutex_unlock(&semaphoreGen);
        sem_post(&sem_inicioFun);//Incrementa el numero de huecos del buffer fins
    
        sleep(1);
    }
}

int main(){

	srand(time(NULL));
	pthread_t t1,t2;
	int i;

    sem_init(&sem_finFunc, 0, 0);
    sem_init(&sem_inicioFun, 0, vectorTam);

	for(i=0;i<vectorTam;i++) 
		printf("El buffer %d tiene: %d elementos\n", i, buffer[i]);
		printf("\n");
	
	for(i=0;i<productores; i++){
		pthread_create(&t1, NULL, (void *)productor,(void*)i);
		usleep(50000);
	}
	
	for(i=0; i<compradores;i++){
	 	pthread_create(&t2, NULL, (void *)compra, (void*)i);
		usleep(50000);
	}

		pthread_join(t1, NULL);
		pthread_join(t2, NULL);

		printf("\nEl buffer global es:");
		printf("\n");
		for(i=0;i<vectorTam;i++) printf("El buffer %d tiene: %d elementos\n", i, buffer[i]);
		printf("\n");
	pthread_mutex_destroy(&semaphoreGen);
	return 0;
}

