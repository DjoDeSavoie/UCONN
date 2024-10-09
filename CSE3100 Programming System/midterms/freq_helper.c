#include <assert.h>

//TODO
unsigned firstDigit(unsigned k)
{
	//fill in code below
	//we divide k by 10 until it is under 10
    while (k >= 10)  
        k /= 10; 
      
    return k; 
}

//TODO
void FirstDigitCount(unsigned *a, unsigned n, unsigned freq[10])
{
	//fill in your code below
	for(int i = 0; i < 10; i++) freq[i] = 0;
	for(unsigned i = 0; i < n; i++) {
		freq[firstDigit(a[i])]++; //we increment the value of the frequencies for the position of the first digit of the number
	}
}