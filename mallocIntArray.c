#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int j=1;
    //array of 12 ints 
   int *arr = malloc(12*sizeof(int));
   for(int i=0; i<12; i++){
       arr[i] = j;
       j++;
   }

   //don't free arr (our array of 12 ints)
   return 0;
}