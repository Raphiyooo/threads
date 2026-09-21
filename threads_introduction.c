#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* routine(void* arg)
{
  printf("Test from threads\n");
  sleep(1);
  printf("Ending thread\n");

  return NULL;
}

int main(void)
{
  pthread_t thread1, thread2;
  if (pthread_create(&thread1, NULL, routine, NULL) != 0)
    return 1;
  if (pthread_create(&thread2, NULL, routine, NULL) != 0)
    return 2;
  if (pthread_join(thread1, NULL) != 0)
    return 3;
  if (pthread_join(thread2, NULL) != 0)
    return 4;
  return 0;
}