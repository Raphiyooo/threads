#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 4

sem_t semaphore;

void* routine(void* args)
{
  sem_wait(&semaphore); // decrements semaphore, 2
  sleep(1);
  printf("hello from thread %d\n", *(int*)args);
  sem_post(&semaphore); // increments semaphore
  free(args);
}

int main(void)
{
  pthread_t th[NUM_THREADS];
  sem_init(&semaphore, 0, 2);
  for (int i = 0; i < NUM_THREADS; i++)
  {
    int* index = malloc(sizeof(int));
    *index = i;
    if (pthread_create(&th[i], NULL, &routine, (void*) index) != 0)
      return 1;
  }

  for (int i = 0; i < NUM_THREADS; i++)
  {
    if (pthread_join(th[i], NULL) != 0)
      return 2;
  }
  sem_destroy(&semaphore);

  return 0;
}