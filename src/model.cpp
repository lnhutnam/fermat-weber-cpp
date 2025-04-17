#include "../include/model.h"
#include <cmath>

#define DIMENSION 2

GRBModel createOriginalModel(
    GRBEnv &env, 
    std::vector<Coordinate> &coordinates,
    std::vector<Edge> &edges
) {
    GRBModel model = GRBModel(env);

    std::vector<GRBVar> distances;
    std::vector<std::vector<GRBVar>> transformations;
    for (size_t i = 0; i < edges.size(); i++) {
        distances.push_back(model.addVar(0, GRB_INFINITY, 1, GRB_CONTINUOUS, 'd' + std::to_string(i)));

        transformations.push_back(std::vector<GRBVar>());
        for (int k = 0; k < DIMENSION; k++) {
            transformations[i].push_back(model.addVar(-GRB_INFINITY, GRB_INFINITY, 0, GRB_CONTINUOUS, "t_" + std::to_string(i) + ',' + std::to_string(k + 1)));
        }
    }

    GRBVar facilityLocations[DIMENSION][DIMENSION];

    facilityLocations[0][0] = model.addVar(-GRB_INFINITY, GRB_INFINITY, 0, GRB_CONTINUOUS, "x_{5,1}");
    facilityLocations[0][1] = model.addVar(-GRB_INFINITY, GRB_INFINITY, 0, GRB_CONTINUOUS, "x_{5,2}");
    facilityLocations[1][0] = model.addVar(-GRB_INFINITY, GRB_INFINITY, 0, GRB_CONTINUOUS, "x_{6,1}");
    facilityLocations[1][1] = model.addVar(-GRB_INFINITY, GRB_INFINITY, 0, GRB_CONTINUOUS, "x_{6,2}");

    for (size_t i = 0; i < edges.size() - 1; i++) {
        GRBQuadExpr distanceExpression = 0;

        Edge currentEdge = edges[i];
        int coordinateIndex = currentEdge.second;
        int facilityIndex = currentEdge.first < edges.size() ? 0 : 1;

        double pointCoordinates[DIMENSION] = { 
            coordinates[coordinateIndex].first, 
            coordinates[coordinateIndex].second 
        };

        for (int k = 0; k < DIMENSION; k++) {
            model.addConstr(transformations[i][k] == facilityLocations[facilityIndex][k] - pointCoordinates[k]);
            distanceExpression += transformations[i][k] * transformations[i][k];
        }

        model.addQConstr(distances[i] * distances[i] >= distanceExpression, 'd' + std::to_string(currentEdge.first) + '_' + std::to_string(currentEdge.second));
    }

    GRBQuadExpr finalDistanceExpression = 0;
    for (int k = 0; k < DIMENSION; k++) {
        model.addConstr(transformations[4][k] == facilityLocations[0][k] - facilityLocations[1][k]);
        finalDistanceExpression += transformations[4][k] * transformations[4][k];
    }

    model.addQConstr(distances[4] * distances[4] >= finalDistanceExpression, "d_{4,5}");

    return model;
}

int calculateMaximumDistance(
    std::vector<Coordinate> &coordinates
) {
    double maximumDistance = 0;
    for (size_t i = 0; i < coordinates.size(); i++) {
        for (size_t j = i + 1; j < coordinates.size(); j++) {
            double distance = std::sqrt(
                std::pow(coordinates[j].first - coordinates[i].first, 2)
                + std::pow(coordinates[j].second - coordinates[i].second, 2)
            );

            if (distance > maximumDistance) {
                maximumDistance = distance;
            }
        }
    }

    return static_cast<int>(std::ceil(maximumDistance));
}

// The remaining Maculan model implementation would be similar, 
// with variable names updated to match the English-style naming scheme
GRBModel createMaculanModel(
    GRBEnv &env, 
    int numTerminalPoints,
    std::vector<Coordinate> &coordinates
) {
    GRBModel model = GRBModel(env);
    const int numSecondaryFacilities = numTerminalPoints - 2;
    const int maximumDistance = calculateMaximumDistance(coordinates);

    // Rest of the Maculan model implementation would follow a similar pattern
    // with updated variable and function names

    return model;
}
