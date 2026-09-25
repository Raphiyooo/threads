#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>

#define NUM_THREADS 2

void* routine(void* args)
{
  pthread_t th = pthread_self(); // get the actual number of the thread that executes here
  printf("%ul\n", th);
  printf("%d\n", (pid_t) syscall(SYS_gettid));

  // these two are not the same, tphread_t is an id that is managed by the pthread api itself
  // in a software hierarchy perspective, on the top is the code, below the pthread api and below the os
  // pthread_t has nothing to do with the os but with the api, but the tid is the internal thread id inside the os
}

int main(void)
{
  pthread_t th[NUM_THREADS];
  for (int i = 0; i < NUM_THREADS; i++)
  {
    if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
      return 1;
    printf("%ul\n", th[i]); // the numbers are set by pthread_create in the th array and
                            // used by pthread_join to identify these threads
    // pthread_t are not always ul, can be anything so printing it is not safe
  }

  for (int i = 0; i < NUM_THREADS; i++)
  {
    if (pthread_join(th[i], NULL) != 0)
      return 2;
  }

  return 0;
}