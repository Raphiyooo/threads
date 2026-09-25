#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

pthread_mutex_t mutex[4];
int stove_fuel[4] = { 100, 100, 100, 100 };

void* routine(void* args)
{
  while (stove_fuel[0] > 0 || stove_fuel[1] > 0 || stove_fuel[2] > 0 || stove_fuel[3] > 0)
  for (int i = 0; i < 4; i++)
  {
    if (pthread_mutex_trylock(&mutex[i]) == 0)
    {
      int fuel_needed = 10;
      if (stove_fuel[i] - fuel_needed < 0)
      {
        printf("No more fuel\n");
        pthread_mutex_unlock(&mutex[i]);
        break;
      }
      else
      {
        stove_fuel[i] -= fuel_needed;
        printf("Fuel left: %d, at stove %d\n", stove_fuel[i], i);
      }
      pthread_mutex_unlock(&mutex[i]);
    }
    else
    {
      printf("Stove %d locked, trying next sove\n", i);
    }

  }
  return NULL;
}

int main(void)
{
  srand(time(NULL));
  pthread_t th[4];
  for (int i = 0; i < 4; i++)
  {
    pthread_mutex_init(&mutex[i], NULL);
  }
  for (int i = 0; i < 4; i++)
  {
    pthread_create(&th[i], NULL, &routine, NULL);
  }
  for (int i = 0; i < 4; i++)
  {
    pthread_join(th[i], NULL);
  }
  for (int i = 0; i < 4; i++)
  {
    pthread_mutex_destroy(&mutex[i]);
  }
  

  return 0;
}