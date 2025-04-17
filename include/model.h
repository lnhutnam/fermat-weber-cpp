#ifndef MODELO_H
#define MODELO_H

#include "gurobi_c++.h"
#include "tipos.h"

GRBModel createOriginalModel(
    GRBEnv &env, 
    std::vector<Coordinate> &coordinates,
    std::vector<Edge> &edges
);

GRBModel createMaculanModel(
    GRBEnv &env,
    int numTerminalPoints,
    std::vector<Coordinate> &coordinates  
);

#endif
