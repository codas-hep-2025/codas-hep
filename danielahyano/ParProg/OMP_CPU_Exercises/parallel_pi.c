/*

This program will numerically compute the integral of

                  4/(1+x*x) 
				  
from 0 to 1.  The value of this integral is pi -- which 
is great since it gives us an easy way to check the answer.

The is the original sequential program.  It uses the timer
from the OpenMP runtime library

History: Written by Tim Mattson, 11/99.

*/
#include <stdio.h>
#include <omp.h>
static long num_steps = 100000000;
double step;
int main ()
{
	  int i;
	  double pi, sum = 0.0;
	  double start_time, run_time;

	  step = 1.0/(double) num_steps;
        	 
	  start_time = omp_get_wtime();
      int num_threads = 4;
      double sums_list[num_threads];

      omp_set_num_threads(num_threads);
      #pragma omp parallel
      {
          int current_thread = omp_get_thread_num();
          printf("%d ", current_thread);
          double partial_sum = 0.0;

          int start_index = (num_steps/num_threads) * current_thread + 1;
          int end_index = start_index + (num_steps/num_threads); 
          double x; 
          for (i=start_index;i<= end_index; i++){
    		  x = (i-0.5)*step;
    		  partial_sum = partial_sum + 4.0/(1.0+x*x);
    	  }
           
          printf("partial: %d ", partial_sum);
          sums_list[current_thread] = partial_sum;
      }

      for (i=1;i<= num_threads; i++){
        sum += sums_list[i]; // Add the current element to sum
      }
      
	  pi = step * sum; 
      printf("%d", pi);
	  // run_time = omp_get_wtime() - start_time;
	  // printf("\n pi with %ld steps is %lf in %lf seconds\n ",num_steps,pi,run_time);
}	  





