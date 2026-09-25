#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int fuel = 50;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int water = 10;

// void* routine(void* args)
// {
//   pthread_mutex_lock(&mutex);
//   // pthread_mutex_lock(&mutex); nothing gets printed because it tries to lock the same mutex
//   pthread_mutex_lock(&mutex1);
//   fuel += 50;
//   water = fuel;
//   printf("Incremented fuel to %d and set water to %d\n", fuel, water);
//   pthread_mutex_unlock(&mutex);
//   pthread_mutex_unlock(&mutex1);
// }

void* routine(void* args)
{
  // this is dangerous because if one thread goes into if and locks mutex and the other in the
  // else and locks mutex1 both wait for each other and this causes a deadlock, in the if or else
  // switch the mutex and mutex1 order, this mkaes the if else redundant so you can just write it
  // without the if else
  if (rand() % 2 == 0)
  {
    pthread_mutex_lock(&mutex);
    pthread_mutex_lock(&mutex1);
  }
  else
  {
    pthread_mutex_lock(&mutex1);
    pthread_mutex_lock(&mutex);
  }
  fuel += 50;
  water = fuel;
  printf("Incremented fuel to %d and set water to %d\n", fuel, water);
  pthread_mutex_unlock(&mutex);
  pthread_mutex_unlock(&mutex1);
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
  printf("Fuel %d\n", fuel);
  printf("Water %d\n", water);
  pthread_mutex_destroy(&mutex);
  pthread_mutex_destroy(&mutex1);

  return 0;
}