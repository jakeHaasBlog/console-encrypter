#include <random>
#include <iostream>

#ifndef CONSISTANT_RAND
#define CONSISTANT_RAND

namespace {
    std::mt19937 engine(0);
}

int c_rand() {

    unsigned int ui = engine();
    int r = *((int*)(&ui));

    return abs(r);

    //return rand();
}


void c_srand(unsigned int seed) {

    engine.seed(seed);

    //srand(seed);
}


#endif


