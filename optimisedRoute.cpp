//
// Created by Alexander O'Carroll on 19/04/2024.
//

#include "../Headers/optimisedRoute.h"
#include "../Headers/FloydWarshall.h"
#include <limits>


optimisedRoute::optimisedRoute(GarbageLocations *gl) {
    this->gl = gl;
}

void optimisedRoute::findOptimisedRoute() {

    int wasteThreshold = 60;
    int maxDistance = 20;

    vector<vector<array<int, 2>>> adjLists = gl->getAdjLists();
    vector<int> locationsForCollection = gl->getLocationsByWaste(wasteThreshold);
    FloydWarshall *fw = new FloydWarshall(adjLists);
    vector<vector<int>> shortestPathMatrix = fw->getShortestPathMatrix();

    vector<int> currentRoute;
    currentRoute.push_back(0);
    int bestDistance;
    int currentDistance;

    bestRoute = shortestPath(0, bestRoute, currentRoute, bestDistance, currentDistance, maxDistance, locationsForCollection,
                             shortestPathMatrix);
    bestRoute.push_back(0);

    distance = getRouteDistance(bestRoute, shortestPathMatrix);
    this->fullRoute = bestToFullRoute(fw);

}

int optimisedRoute::getNClosest(int start, int n, vector<vector<int>> shortestPathMatrix, vector<int> locationsForCollection) {

    vector<array<int, 2>> shortestList;
    int max = numeric_limits<int>::max();
    int min;
    int pos = -1;

    for(int location : locationsForCollection){
        shortestList.push_back({shortestPathMatrix[start][location], location});
    }

    for(int i = 0; i < n; i++){
        min = max;

        if(pos != -1){
            shortestList.erase(shortestList.begin() + pos);
        }

        for(int j = 0; j < shortestList.size(); j++){

             if(shortestList[j][0] < min){
                 min = shortestList[j][0];
                 pos = j;
             }
        }
    }

    return shortestList[pos][1];

}

vector<int> optimisedRoute::shortestPath(int location, vector<int> bestRoute,
                                         vector<int> currentRoute, int bestDistance,
                                         int currentDistance, int maxDistance, vector<int> locationsForCollection,
                                         vector<vector<int>> shortestPathMatrix) {


    for(int i = 0; i < locationsForCollection.size(); i++){

        int nextLocation = getNClosest(location, i+1, shortestPathMatrix, locationsForCollection);

        int newTotalDistance = currentDistance + shortestPathMatrix[location][nextLocation] +
                shortestPathMatrix[nextLocation][0];

        if(newTotalDistance > maxDistance){
            continue;
        }

        currentDistance += shortestPathMatrix[location][nextLocation];
        currentRoute.push_back(nextLocation);
        locationsForCollection.erase(remove(locationsForCollection.begin(),locationsForCollection.end(),
                                            nextLocation), locationsForCollection.end());
        bestRoute = shortestPath(nextLocation, bestRoute, currentRoute, bestDistance, currentDistance,
                     maxDistance, locationsForCollection, shortestPathMatrix);

        currentDistance -= shortestPathMatrix[location][nextLocation];
        currentRoute.pop_back();
        locationsForCollection.push_back(nextLocation);

    }

    if(currentRoute.size() > bestRoute.size()){
        return currentRoute;
    }
    else if(currentRoute.size() == bestRoute.size() && currentDistance + shortestPathMatrix[location][0] < getRouteDistance(bestRoute, shortestPathMatrix)
    + shortestPathMatrix[bestRoute[bestRoute.size()-1]][0]){
        return currentRoute;
    }
    return bestRoute;

}

int optimisedRoute::getRouteDistance(vector<int> route, vector<vector<int>> shortestPathMatrix) {

    int distance = 0;

    for(int i = 0; i < route.size() - 1; i++){

        distance += shortestPathMatrix[route[i]][route[i+1]];

    }

    return distance;
}

vector<int> optimisedRoute::getBestRoute() {
    if(bestRoute.empty()){
        findOptimisedRoute();
    }
    return bestRoute;
}

vector<int> optimisedRoute::getFullRoute() {
    if(fullRoute.empty()){
        findOptimisedRoute();
    }
    return fullRoute;
}

vector<int> optimisedRoute::bestToFullRoute(FloydWarshall *fw) {

    vector<int> fullPath;
    vector<int> betweenPath;
    fullPath.push_back(bestRoute[0]);

    for(int i = 0; i < bestRoute.size() - 1; i++){

        int u = bestRoute[i];
        int v = bestRoute[i+1];

        betweenPath = fw->getPath(u, v);

        for(int j = 1; j < betweenPath.size(); j++){
            fullPath.push_back(betweenPath[j]);
        }
    }

    return fullPath;

}

int optimisedRoute::getDistance() const {
    return distance;
}

