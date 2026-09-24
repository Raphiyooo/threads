#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

int task = 0;
int x = 0;

void* worker(void* args)
{
  pthread_mutex_lock(&mutex);
  while (task == 0)
  {
    printf("No task\n");
    pthread_cond_wait(&cond, &mutex);
  }
  printf("Got a task\n");
  // task
  x++;

  pthread_mutex_unlock(&mutex);
}

void* manager(void* args)
{
  pthread_mutex_lock(&mutex);
  pthread_cond_signal(&cond);
  sleep(2);
  task = 1;
  printf("Changed to task = 1\n");
  pthread_cond_signal(&cond);
  
  pthread_mutex_unlock(&mutex);
}

int main(void)
{
  pthread_t th[2];
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond, NULL);

  for (int i = 0; i < 2; i++)
  {
    if (i == 0)
      pthread_create(&th[i], NULL, &worker, NULL);
    else
      pthread_create(&th[i], NULL, &manager, NULL);
  }

  for (int i = 0; i < 2; i++)
  {
    pthread_join(th[i], NULL);
  }

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);

  return 0;
}