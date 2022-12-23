#include <stdio.h>
#include <pthread.h>
#include <time.h>

int x, n;

void *thread_func(void *arg) {
  int thread_num = (int)arg;
  long long start = (thread_num - 1) * (1.0 * n / x) + 1;
  long long end = thread_num * (1.0 * n / x);


  long long ret = 0;
  for (long long i = start; i <= end; i++) {
    ret += i;
  }

  pthread_exit((void *) ret);

  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <num threads> <n>\n", argv[0]);
    return 1;
  }

  void *ret;
  x = atoi(argv[1]);
  n = atoi(argv[2]);

  pthread_t threads[x];
  for (int i = 0; i < x; i++) {
    pthread_create(&threads[i], NULL, thread_func, (void *)(i + 1));
  }

  long long sum = 0;
  float t1, t2;

  time_t start, end;
  start = clock();
  for (int i = 0; i < x; i++) {
    pthread_join(threads[i], &ret);
    sum += (long long) ret;
  }
  end = clock();

  printf("Time With Thread: %f\n", t1 = difftime(end, start));

  long long sum2 = 0;

  start = clock();
  for (int i = 1; i <= n; i++) {
    sum2 += i;
  }
  end = clock();

  printf("Time Without Thread: %f\n", t2 = difftime(end, start));

  printf("Time Difference: %f\n", t2 / t1);

  printf("The sum of the numbers from 1 to %d is %lld (using %d threads)\n", n, sum, x);

  return 0;
}
