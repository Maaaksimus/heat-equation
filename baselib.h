#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#define TAU_STEPS 20
#define TAU2_STEPS 500
#define NUM_OF_POINTS 10

// #define tau 1. / (TAU_STEPS - 1) // связано с TAU_STEPS
// #define tau2 1e-5 // связано с TAU_STEPS2
#define nu 2.
#define EPS 1e-6

using namespace std;