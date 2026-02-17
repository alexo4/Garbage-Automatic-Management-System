//
// Created by Alexander O'Carroll on 02/05/2024.
//

#include "../Headers/nonOptimisedRoute.h"
#include <iostream>

using namespace std;

nonOptimisedRoute::nonOptimisedRoute(GarbageLocations *gl) {
    this->gl = gl;
}

void nonOptimisedRoute::findRoute() {

    fullRoute = {0, 2, 3, 1, 3, 5, 7, 6, 9, 8, 4, 0};
    int wasteThreshold = 40;
    vector<int> locationsForCollection = gl->getLocationsByWaste(wasteThreshold);

    pickUpPoints.push_back(0);

    for(int i = 1; i < fullRoute.size() - 1; i++){

        int location = fullRoute[i];
        if(find(locationsForCollection.begin(), locationsForCollection.end(), location) != locationsForCollection.end()){
            if(find(pickUpPoints.begin(), pickUpPoints.end(), location) == pickUpPoints.end()){
                pickUpPoints.push_back(location);
            }
        }
    }
    pickUpPoints.push_back(0);

}

vector<int> nonOptimisedRoute::getPickUpPoints() {
    if(pickUpPoints.empty())
        findRoute();
    return pickUpPoints;
}

vector<int> nonOptimisedRoute::getFullRoute() {
    if(fullRoute.empty())
        findRoute();
    return fullRoute;
}

int nonOptimisedRoute::getDistance() {
    return 34;
}

