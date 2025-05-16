#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "numarray.h"

char *Getline(){
	int ch;
	char *buffer;
	size_t buffersize;
	size_t n;
	n = 0;
	buffersize = 512;
	buffer = (char*)malloc(buffersize);
	while ((ch = getchar()) != EOF){
		if (n > buffersize){
			buffersize += 512;
			buffer = (char*)realloc(buffer, buffersize);
		}
		if (ch == '\n'){
			buffer[n] = '\0';
			return buffer;
		}
		buffer[n++] = ch;
	}
	buffer[n] = '\0';
	return buffer;
}

// random number generator using numbers from megamillions website.
// https://www.megamillions.com/Winning-Numbers/Previous-Drawings.aspx#page8

typedef struct {
    int n1;
    int n2;
    int n3;
    int n4;
    int n5;
    int s_n6;
} lot;

#define Rand() (rand() & rand() & rand())

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

void Printlot(lot *l){
    printf("\n---------------------------------------------\n");
    printf("First number: %d\n", l->n1);
    printf("Second number: %d\n", l->n2);
    printf("Third number: %d\n", l->n3);
    printf("Fourth number: %d\n", l->n4);
    printf("Fifth number: %d\n", l->n5);
    printf("Special number: %d\n", l->s_n6);
    printf("---------------------------------------------\n");
}

int main(){
    lot l;
    char *str;
    // makes the rand() function random
    srand(time(NULL));
    // initializes the arrays
    init();
    // returns a random number from the array
    Getlot(&l);
    Freearray();
    Printlot(&l);
    printf("Press Enter To exit.\n");
    str = Getline();
    return 1;
}
