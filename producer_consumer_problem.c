#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <fcntl.h>

#define NUM_THREADS 4

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t* semaphore_full;
sem_t* semaphore_empty;
int buffer[10];
int in = 0;
int out = 0;

void* producer(void* args)
{
  while (1)
  {
    sem_wait(semaphore_empty); // decrements empty by 1, initially it was 10, now 9
    sleep(1);
    pthread_mutex_lock(&mutex);
    int x = rand() % 100;
    buffer[in] = x;
    in = (in + 1) % 10;
    pthread_mutex_unlock(&mutex);
    sem_post(semaphore_full); // increments full by 1, initially it was 0, now 1
  }
}

void* consumer(void* args)
{
  while (1)
  {
    sem_wait(semaphore_full); // decrements full by 1, initially it was 1-9, now 0-8
    sleep(1);
    pthread_mutex_lock(&mutex);
    int y = buffer[out];
    out = (out + 1) % 10;
    pthread_mutex_unlock(&mutex);
    sem_post(semaphore_empty); // increments empty by 1, initially it was 1-9, now 0-8
    printf("Got %d\n", y);
  }
}

int main(void)
{
  sem_unlink("/my_semaphore_full");
  sem_unlink("/my_semaphore_empty");

  srand(time(NULL));
  pthread_t th[NUM_THREADS];
  // sem_init(&semaphore_full_full, 0, 3);
  semaphore_full = sem_open("/my_semaphore_full", O_CREAT, 0600, 0);
  semaphore_empty = sem_open("/my_semaphore_empty", O_CREAT, 0600, 10);
  for (int i = 0; i < NUM_THREADS; i++)
  {
    if (i % 2 == 0)
      pthread_create(&th[i], NULL, &producer, NULL);
    else
      pthread_create(&th[i], NULL, &consumer, NULL);
  }
  for (int i = 0; i < NUM_THREADS; i++)
  {
    pthread_join(th[i], NULL);
  }
  // sem_destroy(&semaphore_full_full);
  sem_close(semaphore_full);
  sem_unlink("/my_semaphore_full");

  sem_close(semaphore_empty);
  sem_unlink("/my_semaphore_empty");

  pthread_mutex_destroy(&mutex);


  return 0;
}