//
// Created by Alexander O'Carroll on 02/05/2024.
//

#include "../Headers/displayToUser.h"
#include "../Headers/GarbageLocations.h"
#include "../Headers/nonOptimisedRoute.h"
#include "../Headers/optimisedRoute.h"
#include "../Headers/GreedyRoute.h"
#include "../Headers/saveToFile.h"


displayToUser::displayToUser() {

}

void displayToUser::displayInformation() {

    int wage = 10;

    GarbageLocations *garbageLocations = new GarbageLocations();
    garbageLocations->loadGarbageLocations();
    garbageLocations->printGarbageLocations();
    garbageLocations->printWasteLevels();

    nonOptimisedRoute *nonOptRoute = new nonOptimisedRoute(garbageLocations);
    vector<int> nonOptPath = nonOptRoute->getPickUpPoints();
    vector<int> nonOptFullPath = nonOptRoute->getFullRoute();
    cout << "Non-Optimised Route(1):\n";
    displayPickUpRoute(nonOptPath, nonOptFullPath);
    cout << "Total Costs: RM" << getTotalCost(nonOptRoute->getDistance(), nonOptPath.size() - 2, wage);
    cout << "\nDistance: " << nonOptRoute->getDistance() << "KM";
    cout << "\nGarbage Locations Emptied Up: " << nonOptPath.size() - 2 <<"\n";

    optimisedRoute *optRoute = new optimisedRoute(garbageLocations);
    vector<int> optPath = optRoute->getBestRoute();
    vector<int> optFullPath = optRoute->getFullRoute();
    cout << "\nOptimised Route(2):\n";
    displayPickUpRoute(optPath, optFullPath);
    cout << "Total Costs: RM" << getTotalCost(optRoute->getDistance(), optPath.size() - 2, wage);
    cout << "\nDistance: " << optRoute->getDistance() << "KM";
    cout << "\nGarbage Locations Emptied Up: " << optPath.size() - 2 <<"\n";

    GreedyRoute * greedyRoute = new GreedyRoute(garbageLocations);
    vector<int> greedyPath = greedyRoute->getGreedyRoute();
    vector<int> greedyFullPath = greedyRoute->getFullRoute();
    cout << "\nGreedy Route(3):\n";
    displayPickUpRoute(greedyPath, greedyFullPath);
    cout << "Total Costs: RM" << getTotalCost(greedyRoute->getDistance(), greedyPath.size() - 2, wage);
    cout << "\nDistance: " << greedyRoute->getDistance() << "KM";
    cout << "\nGarbage Locations Emptied Up: " << greedyPath.size() - 2 <<"\n";

    int choice = 0;

    while(choice < 1 || choice > 3){
        cout << "\nPlease choose which route you would like to take (1/2/3): ";
        cin >> choice;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    cout << "\nAll Relevant information to take the chosen route is saved in the GL_Route text file";

    saveToFile *stf;
    switch(choice){
        case 1:
            stf = new saveToFile(garbageLocations, nonOptPath, nonOptFullPath);
            break;
        case 2:
            stf = new saveToFile(garbageLocations, optPath, optFullPath);
            break;
        case 3:
            stf = new saveToFile(garbageLocations, greedyPath, greedyFullPath);
            break;
    }

}

double displayToUser::getFuelCost(double distance) {
    return 2.5 * distance;
}

double displayToUser::getTimeTaken(double distance, int locations) {
    return (distance * 3) + (locations * 20);
}

double displayToUser::getWages(double wage, double time) {
    return wage * time;
}

double displayToUser::getTotalCost(double distance, int locations, double wage) {
    return getWages(wage, getTimeTaken(distance, locations)) + getFuelCost(distance) ;
}

void displayToUser::displayPickUpRoute(std::vector<int> pickUpPoints, std::vector<int> fullRoute) {

    cout << "||A||-->";
    char locationAsChar;
    int posInFullRoute = 1;
    for(int i = 1; i < pickUpPoints.size(); i++){

        for(int j = posInFullRoute; j < fullRoute.size(); j++){
            if(fullRoute[posInFullRoute] != pickUpPoints[i]){
                locationAsChar = 'A'+ fullRoute[posInFullRoute];
                cout << locationAsChar << "-->";
                posInFullRoute++;
            }
            else{
                break;
            }
        }
        if( i == pickUpPoints.size() - 1){
            break;
        }
        locationAsChar = 'A' + pickUpPoints[i];
                cout << "|" << locationAsChar << "|-->";
        posInFullRoute++;

    }

    cout << "||A||\n";

}





