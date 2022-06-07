#include"filter_moving_average.h"

void moving_average(int readValue)
{
   for(int i= n-1; i > 0; i--){ 
       samples[i] = samples[i-1];
    }

   samples[0] = readValue; 

   long acc = 0;          

   for(int i=0; i<n; i++){ 
       acc += samples[i];
   } 

   mv_filtered =  acc/n;

}