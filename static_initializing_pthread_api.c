#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>

#define NUM_THREADS 2

// with this the mutex is initialized with default values
// just use this if you know you would set 
// the second argument of pthread_mutex_init to NULL
// when using an array of mutexes you need to call
// init, same for condition variables
// you dont have to call destroy but it is good practice
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* routine(void* args)
{

}

int main(void)
{
  pthread_t th[NUM_THREADS];
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
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);

  return 0;
}