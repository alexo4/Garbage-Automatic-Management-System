//
// Created by Alexander O'Carroll on 24/04/2024.
//

#include "../Headers/GreedyRoute.h"
#include <limits>

using namespace std;


GreedyRoute::GreedyRoute(GarbageLocations* gl) {
    this->gl = gl;
}

void GreedyRoute::findGreedyRoute() {

    int wasteThreshold = 10;

    vector<vector<array<int, 2>>> adjLists = gl->getAdjLists();
    vector<int> locationsForCollection = gl->getLocationsByWaste(wasteThreshold);

    vector<int> distanceWithPath;

    greedyRoute.push_back(0);
    fullRoute.push_back(0);
    int location = 0;

    int distance = 0;

    while(!locationsForCollection.empty()){

        distanceWithPath = dijkstrasAlgorithm(adjLists, location, -1, locationsForCollection);
        distance += distanceWithPath[0];
        location = distanceWithPath[1];
        greedyRoute.push_back(location);

        for(int i = distanceWithPath.size() - 1; i > 0; i--){
            fullRoute.push_back(distanceWithPath[i]);
        }

        locationsForCollection.erase(remove(locationsForCollection.begin(), locationsForCollection.end(),
                                            location), locationsForCollection.end());

    }

    greedyRoute.push_back(0);

    distanceWithPath = dijkstrasAlgorithm(adjLists, location, 0, locationsForCollection);

    distance += distanceWithPath[0];

    for(int i = distanceWithPath.size() - 1; i > 0; i--){
        fullRoute.push_back(distanceWithPath[i]);
    }
    this->distance = distance;
}

vector<int> GreedyRoute::dijkstrasAlgorithm(vector<vector<array<int, 2>>> adjLists, int location, int nextLocation, vector<int> locationsForCollection) {

    int size = adjLists.size();
    int max = numeric_limits<int>::max();
    vector<int> distances (size, max);
    distances[location] = 0;

    vector<int> prevNode (size);

    vector<int> unvisited;
    for(int i = 0; i < size; i++){
        unvisited.push_back(i);
    }

    int node = location;

    for(int i = 0; i < size; i++){

        for(array<int, 2> adjNode: adjLists[node]){

            int newDistance = distances[node] + adjNode[1];
            int currentDistance = distances[adjNode[0]];

            if(newDistance < currentDistance){
                distances[adjNode[0]] = newDistance;
                prevNode[adjNode[0]] = node;
            }

        }

        if(i != 0){

            unvisited.erase(remove(unvisited.begin(),unvisited.end(),
                   node), unvisited.end());
        }

        node = getClosestGarbage(unvisited, distances);

    }
    if(nextLocation == -1){
        nextLocation = getClosestGarbage(locationsForCollection, distances);
    }

    vector<int> distanceWithPrev;
    distanceWithPrev.push_back(distances[nextLocation]);
    distanceWithPrev.push_back(nextLocation);
    while(prevNode[nextLocation] != location){
        nextLocation = prevNode[nextLocation];
        distanceWithPrev.push_back(nextLocation);

    }

    return distanceWithPrev;
}

int GreedyRoute::getClosestGarbage(std::vector<int> unvisited, std::vector<int> distances) {

    int min = distances[unvisited[0]];
    int pos = unvisited[0];

    for(int i = 1; i < unvisited.size(); i++){

        int newMin = distances[unvisited[i]];
        if(newMin < min){
            min = newMin;
            pos = unvisited[i];
        }

    }
    return pos;
}

vector<int> GreedyRoute::getGreedyRoute(){
    if(greedyRoute.empty()){
        findGreedyRoute();
    }
    return greedyRoute;
}

vector<int> GreedyRoute::getFullRoute(){
    if(fullRoute.empty()){
        findGreedyRoute();
    }
    return fullRoute;
}

int GreedyRoute::getDistance() {
    return distance;
}






