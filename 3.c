#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef struct sum{
    int elementos;
    int *ar;
    int n;
} sum1;

int *elementosPaciales(sum1 *s)
{
  int i, *suma;
  suma=(int *)malloc(sizeof(int));
  *suma=0;
  printf("\nHilo %d:", (*s).elementos);
  for(i=0;i<(*s).n;i++)
  {
    printf(" %d ", (*s).ar[i]);
    *suma+=(*s).ar[i];
  }
  printf("La suma es:     %d\n", *suma);
  pthread_exit(suma);
}

int main(int argc, char *argv[])
{
  if(argc!=2)
  {
    printf("Error en los argumentos");
    return -1;
  }
    int n_e=10, n_e_h, i, j, sumax=0, *sumt=0;
    int n_h=atoi(argv[1]);
    pthread_t t[n_h];
    sum1 s[n_h];
    int v[10]={0,1,2,3,4,5,6,7,8,9};
    n_e_h=n_e/n_h;
    for(i=0;i<n_h;i++)
    {
      s[i].elementos=i;
      s[i].ar=&(v[(n_e_h)*i]);
      if(n_e % n_h != 0)
      {
        if(i == n_h-1)
        {
          n_e_h+=(n_e) % (n_h);
        }
      }
      s[i].n=n_e_h;
      pthread_create((t+i), NULL, (void *) elementosPaciales, &(s[i]));   //t+i=t[0], t[1]...
      usleep(1000);
    }
    for(j=0;j<n_h;j++)
    {
      pthread_join(t[j], (void **) &sumt);
      sumax+=*sumt;
    }
  printf("Han finalizado los thread.\n");
  printf("\n La suma total es: %d\n", sumax);
  exit(EXIT_SUCCESS);
}
