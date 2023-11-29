#ifndef POLLUTION_MANAGER_H
#define POLLUTION_MANAGER_H

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class PollutionManager {
public:
    PollutionManager(vector<vector<char>> &cityMap);		//constructor
    void spreadAirPol(vector<vector<char>> &zone, vector<vector<char>> &cityMap);
    void spreadLightPol(vector<vector<char>> &zone, vector<vector<char>> &cityMap);
    void spreadSoundPol(vector<vector<char>> &zone, vector<vector<char>> &cityMap);
    int getAirPol() const;    //returns sound pollution
    int getLightPol() const;    //returns light pollution
    int getSoundPol() const;    //returns air pollution
    int getTotalPollution() const;      //returns total pollution

private:
    vector<vector<int>> airPolMap;
    vector<vector<int>> lightPolMap;
    vector<vector<int>> soundPolMap;
    vector<vector<int>> tempPolMap;  // Temporary map to handle pollution spread

    int row;    //store dimensions to avoid calling .size() for every loop
    int col;

    void updateAdjacentPollution(vector<vector<char>> cityMap, int x, int y, int polVal);      //checks for adjacent cell pollution updates
};

#endif
