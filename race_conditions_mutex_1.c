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
  pthread_t t1, t2 = NULL;
  pthread_create(&t1, NULL, &routine, NULL);
  pthread_create(&t2, NULL, &routine, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  printf("Result %d\n", x);

  pthread_mutex_destroy(&mutex);

  return 0;
}