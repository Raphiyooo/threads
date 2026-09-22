#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int x = 0;
pthread_mutex_t mutex;

void* routine(void* args)
{
  for (int i = 0; i < 1000000; i++)
  {
    pthread_mutex_lock(&mutex);
    x++;
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

int main(void)
{
  pthread_mutex_init(&mutex, NULL);
  pthread_t th[4];
  for (int i = 0; i < 4; i++)
  {
    pthread_create(&th[i], NULL, &routine, NULL);
    printf("Thread %d has started\n", i);
  }
  for (int i = 0; i < 4; i++)
  {
    pthread_join(th[i], NULL);
    printf("Thread %d has finished\n", i);
  }
  

  pthread_mutex_destroy(&mutex);

  printf("Result %d\n", x);

  return 0;
}