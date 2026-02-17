//
// Created by Alexander O'Carroll on 02/05/2024.
//

#include "../Headers/saveToFile.h"
#include <iostream>


using namespace std;

saveToFile::saveToFile(GarbageLocations *gl, std::vector<int> pickUpPoints, std::vector<int> fullRoute) {

    this->gl = gl;

    saveAllInfoToFile(pickUpPoints, fullRoute);

}

void saveToFile::saveAllInfoToFile(std::vector<int> pickUpPoints, std::vector<int> fullRoute) {


    ofstream txtFile("textFiles/GL_Route.txt");

    saveMap(txtFile);
    saveWasteLevel(gl->getWasteLevels(), txtFile);
    txtFile << "Route:\n";
    savePickUpRoute(pickUpPoints, fullRoute, txtFile);
    txtFile.close();

}

void saveToFile::savePickUpRoute(std::vector<int> pickUpPoints, std::vector<int> fullRoute, ofstream &txtFile) {

    txtFile << "||A||-->";
    char locationAsChar;
    int posInFullRoute = 1;
    for(int i = 1; i < pickUpPoints.size(); i++){

        for(int j = posInFullRoute; j < fullRoute.size(); j++){
            if(fullRoute[posInFullRoute] != pickUpPoints[i]){
                locationAsChar = 'A'+ fullRoute[posInFullRoute];
                txtFile << locationAsChar << "-->";
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
        txtFile << "|" << locationAsChar << "|-->";
        posInFullRoute++;

    }

    txtFile << "||A||\n";
}

void saveToFile::saveMap(ofstream &txtFile) {
    txtFile << "\nMap:\n"
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

void saveToFile::saveWasteLevel(std::vector<int> wasteLevels, ofstream &txtFile) {

    txtFile << "\nWaste Levels: \n";
    char loc = 'B';
    for(int wasteLevel : wasteLevels){

        txtFile << loc << ": " << wasteLevel << "%  ";
        loc++;
    }
    txtFile << "\n\n";


}