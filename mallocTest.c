#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    //array of 5 chars 
   char *arr = malloc(5*sizeof(char));
   for(int i=0; i<5; i++){
       arr[i] = 'a';
   }

   //don't free arr (our array of 5 chars)
   return 0;
}