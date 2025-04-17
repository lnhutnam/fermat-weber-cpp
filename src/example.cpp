#include "../include/example.h"

std::vector<Coordinate> buildCoordinates() {
    std::vector<Coordinate> coordinates;
    
    coordinates.push_back({0, 1});
    coordinates.push_back({5, 0});
    coordinates.push_back({11, 1});
    coordinates.push_back({4, 4});

    return coordinates;
}

ProblemInstance createProblemOne() {
    std::vector<Coordinate> coordinates = buildCoordinates();

    std::vector<Edge> edges;

    edges.push_back({4, 0});
    edges.push_back({4, 3});
    edges.push_back({5, 1});
    edges.push_back({5, 2});
    edges.push_back({4, 5});

    return { coordinates, edges };
}

ProblemInstance createProblemTwo() {
    std::vector<Coordinate> coordinates = buildCoordinates();

    std::vector<Edge> edges;

    edges.push_back({4, 0});
    edges.push_back({4, 1});
    edges.push_back({5, 2});
    edges.push_back({5, 3});
    edges.push_back({4, 5});

    return { coordinates, edges };
}

ProblemInstance createProblemThree() {
    std::vector<Coordinate> coordinates;

    coordinates.push_back({0, 1});
    coordinates.push_back({2, 0});
    coordinates.push_back({5, 0});
    coordinates.push_back({7, 1});
    coordinates.push_back({5, 2});
    coordinates.push_back({2, 2});

    std::vector<Edge> edges;

    return { coordinates, edges };
}
