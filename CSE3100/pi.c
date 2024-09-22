#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int main()
{
    int n, i;
    double pi = 0;
    printf("n = ");
    scanf("%d", &n);
    assert(n>=0); //conditions of n non negative number

    // TODO
    // add code below
    double substraction = 0.0;
    double powerI = 1.0;

    for(i = 0; i < n+1; i++){
        substraction = ((4.0/((8*i)+1))
                        -(2.0/((8*i)+4))
                        -(1.0/((8*i)+5))
                        -(1.0/((8*i)+6)));
        pi += substraction / powerI; //We divide by the actual power of 16
        powerI *= 16; //Then we put 16 to the next power

    }

    printf("PI = %.10f\n", pi);
    return 0;
}