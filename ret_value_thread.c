#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 3

// how to get the int value to the main function, to use it there
void* roll_dice(void* args)
{
  int value = (rand() % 6) + 1; // result between 1 and 6
  int* result = malloc(sizeof(int));
  if (result == NULL)
    return NULL;
  *result = value;

  printf("Thread address: %p\n", (void*) result);
  return (void*) result;
}

int main(void)
{
  srand(time(NULL));
  pthread_t th[NUM_THREADS];
  for (int i = 0; i < NUM_THREADS; i++)
  {
    if (pthread_create(&th[i], NULL, &roll_dice, NULL) != 0)
      return 1;
  }
  for (int i = 0; i < NUM_THREADS; i++)
  {
    void* thread_result = NULL;
    if (pthread_join(th[i], &thread_result) != 0)
      return 2;

    int* result = thread_result;
    if (thread_result != NULL)
    {
      printf("Main address: %p\n", (void*) result);
      printf("Result: %d\n", *result);
      free(result);
    }
  }

  return 0;
}