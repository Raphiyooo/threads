#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2

pthread_mutex_t mutex;
int fuel = 50;



void* routine(void* args)
{
  // this works now but you need to call same number
  // of unlocks as locks, the pthread_mutex_recursive attribute
  // counts the amount of locks and then subtracts until 0, when it
  // comes to 0 it is considered unlocked
  // useful if you have a recursive function that calls itself every time
  // before unlocking it
  pthread_mutex_lock(&mutex);
  pthread_mutex_lock(&mutex);
  fuel += 50;
  printf("Incremented fuel to %d\n", fuel);
  pthread_mutex_unlock(&mutex);
  pthread_mutex_unlock(&mutex);
}

int main(void)
{
  pthread_t th[NUM_THREADS];
  pthread_mutexattr_t recursive_mutex_attribute;
  pthread_mutexattr_init(&recursive_mutex_attribute);
  pthread_mutexattr_settype(&recursive_mutex_attribute, PTHREAD_MUTEX_RECURSIVE);
  pthread_mutex_init(&mutex, &recursive_mutex_attribute);

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
  printf("Fuel %d\n", fuel);
  pthread_mutexattr_destroy(&recursive_mutex_attribute);
  pthread_mutex_destroy(&mutex);

  return 0;
}