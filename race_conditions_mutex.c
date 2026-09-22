#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int x = 0;

void* routine(void* args)
{
  for (int i = 0; i < 1000000; i++)
  {
    x++;
  }
  return NULL;
}

int main(void)
{
  pthread_t t1, t2 = NULL;
  pthread_create(&t1, NULL, &routine, NULL);
  pthread_create(&t2, NULL, &routine, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  printf("Result %d\n", x);

  return 0;
}