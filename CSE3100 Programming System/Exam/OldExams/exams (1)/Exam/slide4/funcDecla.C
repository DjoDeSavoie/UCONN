#include <stdio.h>

int fahrToCelcius(int);

int main(){
    for(int fahr=0; fahr <= 300; fahr += 10){
        printf("%d F is %d C degrees\n", fahr, fahrToCelcius(fahr));
    }
    return 0;
}

int fahrToCelcius(int degF){
    return 5 * (degF - 32) / 9;
}