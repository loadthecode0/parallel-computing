#include <stdio.h>
#include <time.h>
#include <omp.h>

#define INTERVALS 10000000

double a[INTERVALS], b[INTERVALS];

int main(int argc, char **argv)
{
  double time2;
  time_t time1 = clock();
  double *to = b;
  double *from = a;
  int    time_steps = 100;

  /* Set up initial and boundary conditions. */
  from[0] = 1.0;
  from[INTERVALS - 1] = 0.0;
  to[0] = from[0];
  to[INTERVALS - 1] = from[INTERVALS - 1];
  
  #pragma omp parallel for
  for(long i = 1; i < INTERVALS; i++)
   {
    from[i] = 0.0;
    // printf("Thread %d computes a[%d] = %d\n", omp_get_thread_num(), i, a[i]);
   }
  

  printf("Number of intervals: %ld. Number of time steps: %d\n", INTERVALS, time_steps);

  /* Apply stencil iteratively. */
  while(time_steps-- > 0)
  {
    #pragma omp parallel for
    for(long i = 1; i < (INTERVALS - 1); i++)
      {
        to[i] = from[i] + 0.1*(from[i - 1] - 2*from[i] + from[i + 1]);
        // printf("Thread %d computes a[%d] = %d\n", omp_get_thread_num(), i, a[i]);
      }
   {
    double* tmp = from;
    from = to;
    to = tmp;
   }
  }

  time2 = (clock() - time1) / (double) CLOCKS_PER_SEC;

  printf("Elapsed time (s) = %f\n", time2);

  for(long i = 2; i < 30; i += 2)
   printf("Interval %ld: %f\n", i, to[i]);
  
  return 0;
}                
