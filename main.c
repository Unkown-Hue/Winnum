#include <stdlib.h>
#include <stdint.h>

// random number generator using numbers from megamillions website 2024 demo.
// https://www.megamillions.com/Winning-Numbers/Previous-Drawings.aspx#page8

typedef uint_fast8_t _int;

typedef struct {
    _int n1;
    _int n2;
    _int n3;
    _int n4;
    _int n5;
    _int s_n6;
} lot;

// currently only checking for 2024 wins -> demo
const _int numb1[106] = {
    13,3,11,2,
    56,36,12,16,
    52,3,5,13,
    5,5,18,25,
    2,11,16,23,
    8,4,22,3,
    3,21,27,29,
    1,20,14,21,
    1,6,12,10,
    16,28,8,5,
    22,34,12,23,
    6,19,2,3,
    10,5,15,21,
    6,4,28,3,
    3,21,1,1,
    3,19,4,12,
    46,2,8,13,
    13,26,6,10,
    15,11,19,21,
    1,34,20,10,
    11,7,3,24,
    13,2,19,2,
    15,6,4,5,
    19,1,17,2,
    11,3,14,21,
    1,2,19,12,
    5,3

};

const _int numb2[105] = {
    22,7,14,20,66,43,14,21,60,29,22,20,35,17,31,28,24,22,22,26,43,9,34,10,19,39,35,46,6,21,31,55,2,23,41,17,18,30,20,38,55,32,29,7,23,14,9,17,35,35,26,15,8,31,16,18,22,25,5,37,11,18,54,5,17,19,22,28,13,18,23,17,30,26,12,43,30,50,30,11,8,46,25,16,20,49,33,18,6,45,23,3,22,10,22,5,31,28,9,10,34,15,23,18
};

const _int numb3[105] = {
};

const _int numb4[105] = {
};

const _int numb5[105] = {
};

const _int s_numb6[105] = {
};

void Getlot(lot* l){
    l->n1 = numb1[rand() % 170];
    l->n2 = numb2[rand() % 170];
    l->n3 = numb3[rand() % 170];
    l->n4 = numb4[rand() % 170];
    l->n5 = numb5[rand() % 170];
    return;
}

