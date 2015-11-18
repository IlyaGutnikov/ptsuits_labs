#include <stdio.h>

int main()
{
    long val = 874799703;
    int k = 0;
    
    int arr[4];
    int arr_abs[4];
    
    int avr;
    int min;
    int result;
    
    void *p = &val;
    
    arr[0] = ((char*)p)[3];
    arr[1] = ((char*)p)[2];
    arr[2] = ((char*)p)[1];
    arr[3] = ((char*)p)[0];
    //avr
    avr = arr[0] + arr[1] + arr[2] + arr[3];
    
    //abs
    arr_abs[0] = ((avr - arr[0]*4)*(avr - arr[0]*4));
    arr_abs[1] = ((avr - arr[1]*4)*(avr - arr[1]*4));
    arr_abs[2] = ((avr - arr[2]*4)*(avr - arr[2]*4));
    arr_abs[3] = ((avr - arr[3]*4)*(avr - arr[3]*4));
    
    min = arr_abs[0];
    int j=0;
    for (j=0; j<4; j++) {
        if (arr_abs[j]<min) {
         
         min = arr_abs[j];
         result = j;
            
        }
    }
    
    printf("%i", arr_abs[0]);
    printf("\n");
    
    printf("%i", arr_abs[1]);
    printf("\n");

    printf("%i", arr_abs[2]);
    printf("\n");
    
    printf("%i", arr_abs[3]);
    printf("\n");
    
    printf("avr: %i", avr);
    printf("\n");
    
    printf("min: %i", min);
    printf("\n");
    
    printf("result: %i", result);
    printf("\n");
    
    return 0;
}