
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>
#ifndef __APPLE__
#include <sys/sysinfo.h>
#endif
#include <stddef.h>
#include <time.h>
#include <math.h>
#include <errno.h>

int Running = 1;
double *Times;
unsigned int N;

void tick(int sig) {
  static unsigned int i = 0;
  static double t0 = 0;
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  if (i == 0) {
    Times[i] = 0;
    t0 = ts.tv_sec+ts.tv_nsec/1E9;
  }
  else
    Times[i] = ts.tv_sec+ts.tv_nsec/1E9 - t0;
  // printf("%d, %f\n", i, Times[i]);
  if (++i >= N) Running = 0;
}



int main(int argc, char* argv[]) {
  struct itimerval timer;
  struct sigaction sa;
  unsigned int n, ts, i;
  double max = 0, min = 0, mean = 0, sd = 0, dt = 0;
#ifndef __APPLE__ // BSD does not have sched_setscheduler()
  // Setting scheduler
  struct sched_param sparam;
  sparam.sched_priority = sched_get_priority_min(SCHED_FIFO);
  if (sched_setscheduler(0, SCHED_FIFO, &sparam) != 0) {
    perror("Error setting scheduler to SCHED_FIFO");
  }
#endif

  if (argc != 3) {
    printf("Need the count and the timestep in milliseconds\n");
    exit(0);
  }

  N = atoi(argv[1]);
  ts = atoi(argv[2]);
  Times = (double *)malloc(N * sizeof(double));

  memset (&sa, 0, sizeof (sa));
  sa.sa_handler = &tick;
  sigaction (SIGALRM, &sa, NULL);

  timer.it_interval.tv_sec = 0;
  timer.it_interval.tv_usec = ts * 1E3;
  timer.it_value.tv_sec = 0;
  timer.it_value.tv_usec = ts * 1E3;
  setitimer(ITIMER_REAL, &timer, NULL);

  while(Running) {sleep(1);}

  min = 1E3;
  max = 0;
  for (i = 1; i < N; i++) {
    dt = Times[i] - Times[i-1];
    min = dt < min ? dt : min;
    max = dt > max ? dt : max;
    mean += dt;
  }
  mean /= (N - 1);
  for (i = 1; i < N; i++) {
    dt = Times[i] - Times[i-1];
    sd += pow(dt - mean, 2);
  }
  sd = sqrt(sd/(N - 2));

  printf("   Min: %fs\n   Max: %fs\n  Mean: %fs\nSt.dev: %fs\n", min, max, mean, sd);

  return 0;
}
