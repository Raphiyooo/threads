#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 3

pthread_barrier_t barrier;

void* routine(void* args)
{
  // while(1) {
  printf("Waiting at the barrier\n");
  pthread_barrier_wait(&barrier); // at this line the threads are waiting until 3 are waiting
  printf("We passed the barrier\n");
  // }
}

int main(void)
{
  pthread_t th[NUM_THREADS];
  pthread_barrier_init(&barrier, NULL, 3);
  for (int i = 0; i < NUM_THREADS; i++)
  {
    if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
      return 1;
  }

  for (int i = 0; i < NUM_THREADS; i++)
  {
    if (pthread_join(th[i], NULL) != 0)
      return 2;
  }
  pthread_barrier_destroy(&barrier);

  return 0;
}