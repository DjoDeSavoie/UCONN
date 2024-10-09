#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    int *p = malloc(sizeof(int)*10);
    int *last = p+9;
    int dist = (void*)last-(void*)p;
    printf("Distance is %d\n", dist);
}