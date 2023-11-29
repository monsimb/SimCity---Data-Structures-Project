#include "pollution.h"
#include "functions.h"

PollutionManager::PollutionManager(vector<vector<char>> &cityMap) {
    vector<int> zero;       //empty vector for initialization
    row = col = cityMap[0].size();      //init dimensions

    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            zero.push_back(0);      //no pollution at start
        }
        tempPolMap.push_back(zero);     //adjust pollution maps to right size
        airPolMap.push_back(zero);
        lightPolMap.push_back(zero);
        soundPolMap.push_back(zero);
        zero.clear();       //empty temp vector before next loop
    }
}

void PollutionManager::spreadAirPol(vector<vector<char>> &zone, vector<vector<char>> &cityMap) {
    int pop = 0;
    for (int i = 0; i < cityMap.size(); i++) {
        for (int j = 0; j < cityMap[i].size(); j++) {
            if((zone[i][j] == 'I') && (cityMap[i][j] != 'I')) {        //if industrial zone and population is not 0
                pop = cityMap[i][j] - '0';      //convert char to int
                pop = pop - airPolMap[i][j];    //pollution value = change in population
                updateAdjacentPollution(cityMap, i, j, pop);
                tempPolMap[i][j] = pop;      //new pollution is equal to change in population
            }
        }
    }

    // Assigning temporary pollution values to the city cells and resetting temporary map
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            airPolMap[i][j] += tempPolMap[i][j];
            tempPolMap[i][j] = 0;  // Reset for the next time step
        }
    }
}

void PollutionManager::spreadLightPol(vector<vector<char>> &zone, vector<vector<char>> &cityMap) {
    int pop = 0;
    int indPop = 0;
    for (int i = 0; i < cityMap.size(); i++) {
        for (int j = 0; j < cityMap[i].size(); j++) {
            if(((zone[i][j] == 'A') && (cityMap[i][j] != 'A')) || ((zone[i][j] == 'H') && (cityMap[i][j] != 'H')) || ((zone[i][j] == 'C')  && (cityMap[i][j] != 'C'))) {   //if res or com and population is not 0
                pop = cityMap[i][j] - '0';      //convert char to int
                pop -= lightPolMap[i][j];    //pollution value = change in population
                updateAdjacentPollution(cityMap, i, j, pop);
                tempPolMap[i][j] = pop;      //temp pollution is equal to change in population
            }

            if((zone[i][j] == 'I') && (cityMap[i][j] != 'I')) {
                indPop = cityMap[i][j] - '0';      //convert char to int
                indPop = round(indPop/2);    //one pollution for every two population in industrial
                pop = indPop - lightPolMap[i][j];       //polVal = change in pop
                if(pop > 0) {
                    updateAdjacentPollution(cityMap, i, j, pop);
                    tempPolMap[i][j] = pop;      //temp pollution is equal to change in population
                }
            }
        }
    }

    // Assigning temporary pollution values to the city cells and resetting temporary map
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            lightPolMap[i][j] += tempPolMap[i][j];      //add changes in pollution to each cell to total polMap
            tempPolMap[i][j] = 0;  // Reset for the next time step
        }
    }
}
void PollutionManager::spreadSoundPol(vector<vector<char>> &zone, vector<vector<char>> &cityMap) {
    //Industrial: 1 pollution for every population
    //Commercial: 1 pollution for every 2 population
    //Residential: 1 pollution for every 3 population
    int pop = 0;
    int comPop = 0;
    int resPop = 0;
    for (int i = 0; i < cityMap.size(); i++) {
        for (int j = 0; j < cityMap[i].size(); j++) {
            if((zone[i][j] == 'I') && (cityMap[i][j] != 'I')) {        //if industrial zone and population is not 0
                pop = cityMap[i][j] - '0';      //convert char to int
                pop = pop - soundPolMap[i][j];    //pollution value = change in population
                updateAdjacentPollution(cityMap, i, j, pop);
                tempPolMap[i][j] = pop;      //new pollution is equal to change in population
            }

            if((zone[i][j] == 'C') && (cityMap[i][j] != 'C')) {
                comPop = cityMap[i][j] - '0';      //convert char to int
                comPop = round(comPop/2);    //one pollution for every two population in com
                pop = comPop - soundPolMap[i][j];       //polVal = change in pop
                if(pop > 0) {
                    updateAdjacentPollution(cityMap, i, j, pop);
                    tempPolMap[i][j] = pop;      //temp pollution is equal to change in population
                }
            }

            if(((zone[i][j] == 'A') && (cityMap[i][j] != 'A')) || ((zone[i][j] == 'H') && (cityMap[i][j] != 'H'))) {
                resPop = cityMap[i][j] - '0';      //convert char to int
                resPop = round(resPop/3);    //one pollution for every three population in res
                pop = resPop - soundPolMap[i][j];       //polVal = change in pop
                if(pop > 0) {
                    updateAdjacentPollution(cityMap, i, j, pop);
                    tempPolMap[i][j] = pop;      //temp pollution is equal to change in population
                }
            }
        }
    }

    // Assigning temporary pollution values to the city cells and resetting temporary map
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            soundPolMap[i][j] += tempPolMap[i][j];
            tempPolMap[i][j] = 0;  // Reset for the next time step
        }
    }
}

void PollutionManager::updateAdjacentPollution(vector<vector<char>> cityMap, int x, int y, int polVal) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if ((isValidPos(x+i, y+j, row, col)) && (!(i==0 && j==0)) && (polVal > 1)) {
                if((cityMap[x+i][y+j] != '1') && (cityMap[x+i][y+j] != '2') && (cityMap[x+i][y+j] != '3')) {
                    tempPolMap[x + i][y + j] += (polVal - 1);       //"One less unit of pollution per cell away from the source"
                }
            }
        }
    }
}

int PollutionManager::getAirPol() const {
    int airPol = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            airPol += airPolMap[i][j];
        }
    }
    return airPol;
}

int PollutionManager::getLightPol() const {
    int lightPol = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            lightPol += lightPolMap[i][j];
        }
    }
    return lightPol;
}

int PollutionManager::getSoundPol() const {
    int soundPol = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            soundPol += soundPolMap[i][j];
        }
    }
    return soundPol;
}

int PollutionManager::getTotalPollution() const {
    int totalPollution = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            totalPollution += airPolMap[i][j];
            totalPollution += lightPolMap[i][j];
            totalPollution += soundPolMap[i][j];
        }
    }
    return totalPollution;
}
