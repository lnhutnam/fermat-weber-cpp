#ifndef EXEMPLO_H
#define EXEMPLO_H

#include "tipos.h"
#include <vector>

typedef struct problem_instance {
    std::vector<Coordinate> coordinates;
    std::vector<Edge> edges;
} ProblemInstance;

ProblemInstance createProblemOne();
ProblemInstance createProblemTwo();
ProblemInstance createProblemThree();

#endif
