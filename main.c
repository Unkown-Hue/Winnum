#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "numarray.h"

// random number generator using numbers from megamillions website 2024 demo.
// https://www.megamillions.com/Winning-Numbers/Previous-Drawings.aspx#page8

#define Bits() (Random() & Random() & Random())

size_t Random(){
    size_t r1 = (rand() & 0xFFFF);
    size_t r2 = (rand() & 0xFFFF) << 16;
    size_t r3 = (size_t)(rand() & 0xFFFF) << 32;
    size_t r4 = (size_t)(rand() & 0xFFFF) << 45;
    return r1 | r2 | r3 | r4;
}

typedef struct {
    int n1;
    int n2;
    int n3;
    int n4;
    int n5;
    int s_n6;
} lot;

int arraysize;

// currently only checking for 2024 wins -> demo
int *numb1;

int *numb2;

int *numb3;

int *numb4;

int *numb5;

int *s_numb6;

void Getlot(lot* l){
    l->n1 = numb1[Bits() % arraysize];
    l->n2 = numb2[Bits() % arraysize];
    l->n3 = numb3[Bits() % arraysize];
    l->n4 = numb4[Bits() % arraysize];
    l->n5 = numb5[Bits() % arraysize];
    l->s_n6 = s_numb6[Bits() % arraysize];
    return;
}

void init(){
    int i;
    int j;
    arraysize = ((sizeof(numarray) + 6) * sizeof(int)) / 6;
    numb1 = (int*)malloc((arraysize));
    numb2 = (int*)malloc((arraysize));
    numb3 = (int*)malloc((arraysize));
    numb4 = (int*)malloc((arraysize));
    numb5 = (int*)malloc((arraysize));
    s_numb6 = (int*)malloc((arraysize));
    for (i = 0, j = 0; i + 5 < sizeof(numarray); i+=6, j++){
        numb1[j] = numarray[i];
        numb2[j] = numarray[i + 1];
        numb3[j] = numarray[i + 2];
        numb4[j] = numarray[i + 3];
        numb5[j] = numarray[i + 4];
        s_numb6[j] = numarray[i + 5];
    }
    numb1[j] = -2;
    numb2[j] = -2;
    numb3[j] = -2;
    numb4[j] = -2;
    numb5[j] = -2;
    s_numb6[j] = -2;
    printf("%d\n", j);
    arraysize -= sizeof(int);
    arraysize /= sizeof(int);
}

void Freearray(){
    free(numb1);
    free(numb2);
    free(numb3);
    free(numb4);
    free(numb5);
    free(s_numb6);
}

int Getsize(int *array){
    int i;
    for (i = 0; array[i] != -2; i++){
    }
    return i;
}

int main(){
    init();
    lot l;
    Getlot(&l);
    printf("size of array: %llu\n", sizeof(numarray) / 6);
    printf("size of s_6: %d\n", Getsize(s_numb6));
    printf("size of a5: %d\n", Getsize(numb5));
    printf("size of a4: %d\n", Getsize(numb4));
    printf("size of a3: %d\n", Getsize(numb3));
    printf("size of a2: %d\n", Getsize(numb2));
    printf("size of a1: %d\n", Getsize(numb1));
    printf("First Number: %d\n", l.n1);
    printf("Second Number: %d\n", l.n2);
    printf("Third Number: %d\n", l.n3);
    printf("Fourth Number: %d\n", l.n4);
    printf("Fifth Number: %d\n", l.n5);
    printf("Sixth Number: %d\n", l.s_n6);
    Freearray();
}
