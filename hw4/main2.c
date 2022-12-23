#include <stdio.h>
#include <pthread.h>

int x, n, sum;
pthread_mutex_t mutex;

void *thread_func(void *arg) {
  int thread_num = (int)arg;
  int start = (thread_num - 1) * (1.0 * n / x) + 1;
  int end = thread_num * (1.0 * n / x);

  printf("%d: begin\n", thread_num);

  int thread_sum = 0;
  for (int i = start; i <= end; i++) {
    thread_sum += i;
  }

  pthread_mutex_lock(&mutex);
  sum += thread_sum;
  pthread_mutex_unlock(&mutex);
  printf("%d: end\n", thread_num);

  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <num threads> <n>\n", argv[0]);
    return 1;
  }

  x = atoi(argv[1]);
  n = atoi(argv[2]);

  pthread_mutex_init(&mutex, NULL);

  pthread_t threads[x];
  for (int i = 0; i < x; i++) {
    pthread_create(&threads[i], NULL, thread_func, (void *)(i + 1));
  }

  for (int i = 0; i < x; i++) {
    pthread_join(threads[i], NULL);
  }

  printf("The sum of the numbers from 1 to %d is %d (using %d threads)\n", n, sum, x);

  return 0;
}
