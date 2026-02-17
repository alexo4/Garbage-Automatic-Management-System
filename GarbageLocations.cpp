//
// Created by Alexander O'Carroll on 08/04/2024.
//

#include "../Headers/GarbageLocations.h"
#include <fstream>
#include <iostream>
#include <sstream>

GarbageLocations::GarbageLocations() {
    findNumOfLocations();
    generateWasteLevels();
    vector<vector<array<int, 2>>> vec(numOfLocations);
    this->adjLists = vec;
}


void GarbageLocations::loadGarbageLocations() {


    ifstream garbageFile;
    garbageFile.open("textFiles/garbageLocations.txt");

    if(garbageFile.is_open()) {

        int lineCount = 0;
        string strLine;

        while (getline(garbageFile, strLine)) {

            if (lineCount == 0 || lineCount == 1) {
                lineCount++;
                continue;
            }

            istringstream ss(strLine);
            string num;
            int v, u, w, i = 0;

            while (getline(ss, num, ',')) {

                switch (i) {
                    case 0:
                        v = stoi(num);
                        break;
                    case 1:
                        u = stoi(num);
                        break;
                    case 2:
                        w = stoi(num);
                        break;
                    default:
                        break;
                }
                i++;
            }

            adjLists[v].push_back({u, w});
            adjLists[u].push_back({v, w});

        }
        garbageFile.close();
    }



}


void GarbageLocations::generateWasteLevels() {

    srand(time(0));

    for(int i = 0; i < numOfLocations-1; i++){
        wasteLevels.push_back(rand() % 100);
    }

}

void GarbageLocations::findNumOfLocations() {

    ifstream garbageFile;
    garbageFile.open("textFiles/garbageLocations.txt");

    if(garbageFile.is_open()){

        int lineCount = 0;
        string strLine;

        while(getline(garbageFile, strLine)) {

            if (lineCount == 0) {
                lineCount++;
                continue;
            }else{
                this->numOfLocations = stoi(strLine);
                return;
            }
        }
    }

}

std::vector<int> GarbageLocations::getLocationsByWaste(int wasteLevel) {

    vector<int> locations;

    for(int i = 0; i < numOfLocations-1; i++){
        if(wasteLevels[i] >= wasteLevel){
            locations.push_back(i+1);
        }
    }
    return locations;
}

std::vector<std::vector<std::array<int, 2>>> GarbageLocations::getAdjLists() {
    return adjLists;
}


void GarbageLocations::printGarbageLocations() {
    cout << "\nMap:\n"
            "                B\n"
            "                |\n"
            "                2\n"
            "                |\n"
            "        C---4---D---|\n"
            "        |       |   |\n"
            "        2       3   |\n"
            "        |       |   |\n"
            "E---4---A---2---F   5\n"
            "|       |       |   |\n"
            "|       3       4   |\n"
            "|       |       |   |\n"
            "6       G---2---H---|\n"
            "|       |\n"
            "|       3\n"
            "|       |\n"
            "I---2---J\n";
}

void GarbageLocations::printWasteLevels() {

    cout << "\nWaste Levels: \n";
    char loc = 'B';
    for(int wasteLevel : wasteLevels){

        cout << loc << ": " << wasteLevel << "%  ";
        loc++;
    }
    cout << "\n\n";
}

vector<int> GarbageLocations::getWasteLevels() {
    return wasteLevels;
}


