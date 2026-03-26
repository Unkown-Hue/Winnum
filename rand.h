#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define R1 (uint64_t)(rand())
#define R2 (uint64_t)(rand() )<< 16
#define R3 (uint64_t)(rand() )<< 32
#define R4 (uint64_t)(rand())<< 48
#define R() (R1 | R2 | R3 | R4)
#define Rand() (splitmax())

unsigned long splitmax();

void Seed();