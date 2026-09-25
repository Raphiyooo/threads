#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

#define NUM_THREADS 4

sem_t* semaphore;

void* routine(void* args)
{
  printf("%d Waiting\n", *(int*)args);
  sem_wait(semaphore);
  printf("%d Logged in\n", *(int*)args);
  sleep(rand() % 5 + 1);
  sem_post(semaphore);
  printf("%d Logged out\n", *(int*)args);

  free(args);
  return NULL;
}

int main(void)
{
  pthread_t th[NUM_THREADS];
  // sem_init(&semaphore, 0, 3);
  semaphore = sem_open("/my_semaphore", O_CREAT, 0600, 2);
  for (int i = 0; i < NUM_THREADS; i++)
  {
    int* index = malloc(sizeof(int));
    *index = i;
    pthread_create(&th[i], NULL, &routine, (void*)index);
  }
  for (int i = 0; i < NUM_THREADS; i++)
  {
    pthread_join(th[i], NULL);
  }
  // sem_destroy(&semaphore);
  sem_close(semaphore);
  sem_unlink("/my_semaphore");


  return 0;
}