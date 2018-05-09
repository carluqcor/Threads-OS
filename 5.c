#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

//fgetc(*file) //Lee caracteres


typedef struct matrices{
    int *fil;
    int *v;
} matriz;

void *multiplicaMatriz(matriz *n){
int i, *sum;
sum=(int *)malloc(sizeof(int));
*sum=0;
for(i=1; i<4;i++){
	*sum+=((n->fil[i])*(n->v[i]));
	printf("El valor de la iteracion %d es %d\n", i, *sum);
	}
pthread_exit(sum);
}

int main(){
	int i=0, j=0, sumaT=0, *sumaPar, m[3][3]={{1,2,3},{3,4,5},{1,2,2}}, col[3]={1,2,3};
	pthread_t t[3];
	matriz n[3];
	for(i;i<3;i++){
		n[i].fil=&m[i][0];
		n[i].v=&col[0];
		pthread_create(t+i, NULL, (void *) multiplicaMatriz, &(n[i]));
		sleep(1);
	}
		for(j; j<3; j++){
			pthread_join(t[j], (void **) &sumaPar);
			sumaT+=(*sumaPar);
			free(sumaPar);
		}
		printf("Suma total de la matriz: %d\n", sumaT);
}