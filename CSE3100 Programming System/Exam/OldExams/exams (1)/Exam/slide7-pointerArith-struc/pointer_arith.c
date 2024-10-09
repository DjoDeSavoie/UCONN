#include <stdlib.h>

int main(){
    int *tab = (int*)malloc(sizeof(int)*10);
    tab[3] = 10;
    int *p = tab + 3;
    printf("What is at tab+3? = %d\n", p);
    *p = 20;
    printf("What is at tab[3]? = %d\n", tab[3]);
    return 0;
}