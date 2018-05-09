#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#define clientes 10
#define proveedores 5

//Definición del semaforo binario y las cantidas de camisetas de cada modelo
pthread_mutex_t semaphoreBin=PTHREAD_MUTEX_INITIALIZER;
int camiseta[5]={500, 400, 300, 400, 500};

void *comprar(){
//El semáforo se bloqueará hasta que se resten las camisetas compradas
	pthread_mutex_lock(&semaphoreBin);

//Se hará que el modelo sea random entre 1 y 5 incluidos porque son los modelos de camiseta disponibles
	int modelo = rand()%5;
//La cantidad será un numero random entre 1 y el máximo de camisetas disponibles
	int cantidad = rand()%(camiseta[modelo]);
	printf("Cantidad a decrementar: %d camisetas del modelo %d\n", cantidad, modelo);
//Como dice el enunciado, al comprar debe decrementarse la cantidad de camisetas al comprar
	camiseta[modelo]=camiseta[modelo]-cantidad;
	
//El semáforo se ha desbloqueado camisetas compradas
	pthread_mutex_unlock(&semaphoreBin);
	pthread_exit(NULL);
}

void *proveer(){
//El semáforo se bloqueará hasta que se sume las camisetas a suministrar
	pthread_mutex_lock(&semaphoreBin);

	int modelo = rand()%5;
	int cantidad = rand()%(camiseta[modelo]);
	printf("Cantidad a incrementar: %d camisetas del modelo %d\n", cantidad, modelo);
//Como dice el enunciado, se debe incrementar la cantidad de camisetas al proveer
	camiseta[modelo]=camiseta[modelo]+cantidad;
	
//El semáforo se ha desbloqueado, camisetas proveídas
	pthread_mutex_unlock(&semaphoreBin);
	pthread_exit(NULL);
}

int main(){
//Semilla de tiempo para el rand number
	srand(time(NULL));
	pthread_t t1, t2;
	int i;
	
	printf("\n");
	for(i=0;i<5;i++) printf("El modelo %d tiene: %d camisetas\n", i, camiseta[i]);
	printf("\n");

//Pthread_create de los hilos que usaran las funciones comprar y proveer
	for (i=0;i<clientes;i++) 
		pthread_create(&t1, NULL, (void *)comprar, NULL); 
    for (i=0;i<proveedores;i++)  
		pthread_create(&t2, NULL, (void *)proveer, NULL); 

//	Pthread_join de la espera de los hilos que usaron las funciones
	for(i=0;i<clientes;i++) 
		pthread_join(t1, NULL);
	for(i=0;i<proveedores;i++) 
		pthread_join(t2, NULL);

	printf("\nEl stock final de camisetas es:");
	printf("\n");
	for(i=0;i<5;i++) printf("El modelo %d tiene: %d camisetas\n", i, camiseta[i]);
		printf("\n");
//Al final del programa se debe destruir el semáforo al igual que una reserva de memoria hay que liberarla
	pthread_mutex_destroy(&semaphoreBin);
return 0;
}
