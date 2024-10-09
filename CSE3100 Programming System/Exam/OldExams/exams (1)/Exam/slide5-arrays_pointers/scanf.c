#include <stdio.h>

int main(){
    char name[128];
    int pears = 0;
    int apples = 0;
    scanf("%s %d %d", name, &pears, &apples);
    //We need & on pears and apples to give the addresses to scanf as scanf must write there
}