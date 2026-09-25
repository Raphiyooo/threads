#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>

#define NUM_THREADS 2

void* routine(void* args)
{
  sleep(1);
  printf("Finished execution\n");
}

int main(void)
{
  pthread_t th[NUM_THREADS];
  pthread_attr_t detached_th;
  pthread_attr_init(&detached_th);
  pthread_attr_setdetachstate(&detached_th, PTHREAD_CREATE_DETACHED);
  // you can set a lot of pthread_attr
  for (int i = 0; i < NUM_THREADS; i++)
  {
    if (pthread_create(&th[i], &detached_th, &routine, NULL) != 0)
    {
      perror("Failed to join thread");
      return 2;
    }
    // pthread_detach(th[i]);
  }
  // for a detached thread you dont need to call pthread_join since
  // its gonna clean it up by itself
  // the code right now will terminate because the main process will finish its
  // execution with return 0, if you want the main process to wait for others
  // you cant call pthread_join, you can call pthread_exit instead of return 0
  // so the main process waits for all threads created to finish their execution

  // you dont have to call pthread_detach, you can use the second argument in
  // pthread_create, its used to specify certain things how the thread is created
  // with this you make sure the threads are always created in a detached state
  // in some case it could be that the thread finishes its execution right between
  // pthread_create and pthread_detach, the resources would not be freed because
  // join isnt used

  pthread_attr_destroy(&detached_th);

  return 0;
  // pthread_exit(0);
}