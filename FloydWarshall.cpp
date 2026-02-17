//
// Created by Alexander O'Carroll on 12/04/2024.
//

#include "../Headers/FloydWarshall.h"
#include <iostream>
#include <sstream>
#include <limits>

using namespace std;

FloydWarshall::FloydWarshall(vector<vector<array<int, 2>>> adjLists) {

    this->adjLists = adjLists;

}

void FloydWarshall::initialiseSPMatrix() {

    int size = adjLists.size();
    vector<vector<int> >array(size);
    this->shortestPathMatrix = array;
    this->nextNodeMatrix = array;
    int max = numeric_limits<int>::max() / 2;

    int i = 0;
    for(vector<int> &col : shortestPathMatrix){

        col = vector<int>(size);
        nextNodeMatrix[i] = vector<int>(size);

        for(std::array<int, 2> edge : adjLists[i]){

            col[edge[0]] = edge[1];
            nextNodeMatrix[i][edge[0]] = edge[0];
        }

        i++;

    }

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(shortestPathMatrix[i][j] == 0 && i != j){
                shortestPathMatrix[i][j] = max;
                nextNodeMatrix[i][j] = -1;

            }
        }
    }

}

void FloydWarshall::findShortestPath() {

    int size = adjLists.size();

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            for(int k = j + 1; k < size; k++){
                if(i == j || i == k){
                    continue;
                }

                int currentDistance = shortestPathMatrix[j][k];
                int newRouteDistance = shortestPathMatrix[j][i] + shortestPathMatrix[i][k];
                if(currentDistance > newRouteDistance){
                    shortestPathMatrix[j][k] = newRouteDistance;
                    shortestPathMatrix[k][j] = newRouteDistance;
                    nextNodeMatrix[j][k] = nextNodeMatrix[j][i];
                    nextNodeMatrix[k][j] = nextNodeMatrix[k][i];

                }

            }
        }
    }

}

std::vector<std::vector<int>> FloydWarshall::getShortestPathMatrix() {

    if(shortestPathMatrix.empty()){
        initialiseSPMatrix();
        findShortestPath();
    }
    return shortestPathMatrix;
}

std::vector<int> FloydWarshall::getPath(int u, int v) {
    if(nextNodeMatrix.empty()){
        initialiseSPMatrix();
        findShortestPath();
    }

    vector<int> path;
    if(nextNodeMatrix[u][v] == -1){
        return path;
    }
    path.push_back(u);
    while(nextNodeMatrix[u][v] != v){
        u = nextNodeMatrix[u][v];
        path.push_back(u);
    }
    path.push_back(v);
    return path;
}


