#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "numarray.h"

// random number generator using numbers from megamillions website.
// https://www.megamillions.com/Winning-Numbers/Previous-Drawings.aspx#page8

#define Rand() (rand() & rand() & rand())

typedef struct {
    int n1;
    int n2;
    int n3;
    int n4;
    int n5;
    int s_n6;
} lot;

int arraysize;

// checking for 2019 -> 2024 wins
int *numb1;

int *numb2;

int *numb3;

int *numb4;

int *numb5;

int *s_numb6;

// returns random lot numbers
void Getlot(lot* l){
    l->n1 = numb1[Rand() % arraysize];
    l->n2 = numb2[Rand() % arraysize];
    l->n3 = numb3[Rand() % arraysize];
    l->n4 = numb4[Rand() % arraysize];
    l->n5 = numb5[Rand() % arraysize];
    l->s_n6 = s_numb6[Rand() % arraysize];
    return;
}

// initializes the arrays
void init(){
    int i;
    int j;
    arraysize = sizeof(numarray) / sizeof(int) / 6;
    numb1 = (int*)malloc(arraysize * sizeof(int));
    numb2 = (int*)malloc(arraysize * sizeof(int));
    numb3 = (int*)malloc(arraysize * sizeof(int));
    numb4 = (int*)malloc(arraysize * sizeof(int));
    numb5 = (int*)malloc(arraysize * sizeof(int));
    s_numb6 = (int*)malloc(arraysize * sizeof(int));
    for (i = 0, j = 0; i + 5 < arraysize * 6; i += 6, j++){
        numb1[j] = numarray[i];
        numb2[j] = numarray[i + 1];
        numb3[j] = numarray[i + 2];
        numb4[j] = numarray[i + 3];
        numb5[j] = numarray[i + 4];
        s_numb6[j] = numarray[i + 5];
    }
    printf("%d\n", j);
}

//free memory from the arrays
void Freearray(){
    free(numb1);
    free(numb2);
    free(numb3);
    free(numb4);
    free(numb5);
    free(s_numb6);
}

int main(){
    // makes the rand() function random
    srand(time(NULL));
    // initializes the arrays
    init();
    lot l;
    // returns a random number from the array
    Getlot(&l);
    printf("First Number: %d\n", l.n1);
    printf("Second Number: %d\n", l.n2);
    printf("Third Number: %d\n", l.n3);
    printf("Fourth Number: %d\n", l.n4);
    printf("Fifth Number: %d\n", l.n5);
    printf("Sixth Number: %d\n", l.s_n6);
    Freearray();
}
