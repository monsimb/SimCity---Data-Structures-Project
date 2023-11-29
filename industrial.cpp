#include <iostream>
#include <vector>
#include "functions.h"
#include "industrial.h"
using namespace std;

void updateInd(vector<vector<char>> &cityLayout, vector<vector<char>> zoneLayout, int &availWorkers, int &availGoods) 
{
    int c, r; // column, row
    for (c = 0; c < zoneLayout.size(); c++) 
    {
        for (r = 0; r < zoneLayout[c].size(); r++) 
	    {
            if ((zoneLayout[c][r] == 'I') && (availWorkers >= 2))   //updates cell from 1 to 2 if adjacent to 2 cells of value that is at least 1
            {
                if ((cityLayout[c][r] == '1') && (checkAdjacentNum(cityLayout, 1, c, r) >= 2)) 
                {
                    cityLayout[c][r] = '2';
                    availWorkers -= 2;
                    availGoods += 1;
		    return;
                } 
                else if ((cityLayout[c][r] == '2') && (checkAdjacentNum(cityLayout, 2, c, r) >= 4))     //updates cell from 2 to 3 if adjacent to 4 cells of value that is at least 2
                {
                    cityLayout[c][r] = '3';
                    availWorkers -= 2;
                    availGoods += 1;
		    return;
                } 
                else if (cityLayout[c][r] == 'I' && (checkAdjacentLet(cityLayout, 'T', c, r) >= 1))   //updates cell from 'I' to 1 if adjacent to 1 cells of value that is at least 'T' or 1
                {
                    cityLayout[c][r] = '1';
                    availWorkers -= 2;
                    availGoods += 1;
		    return;
                }
                else if(cityLayout[c][r] == 'I' && (checkAdjacentNum(cityLayout, 1, c, r) >= 1))
                {
                    cityLayout[c][r] = '1';
                    availWorkers -= 2;
                    availGoods += 1;
		    return;
                }
            }
        }
    }
}
