#include <omp.h>
#include <stdio.h>
int main ()  
{
  omp_set_num_threads(4);
  #pragma omp parallel
    { 
        printf("Hello ");
        printf("World \n");
    }
  printf("all done\n");
}
