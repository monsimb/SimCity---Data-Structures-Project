#include <iostream>
#include <vector>
#include "functions.h"
#include "commercial.h"
using namespace std;

void updateCom(vector<vector<char>> &cityLayout, vector<vector<char>> zoneLayout, int &availWorkers, int &availGoods) 
{
    int c, r; // column, row
    for (c = 0; c < zoneLayout.size(); c++) 
    {
        for (r = 0; r < zoneLayout[c].size(); r++) 
	    {
            if (zoneLayout[c][r] == 'C' && availWorkers >= 1 && availGoods >= 1) 
            {
                if (cityLayout[c][r] == 'C' && ((checkAdjacentLet(cityLayout, 'T', c, r) >= 1) || (checkAdjacentNum(cityLayout, 1, c, r)  >= 1)))     //updates cell from 'C' to 1 if adjacent to 1 cells of value that is at least 1 or 'T'
                {
                    cityLayout[c][r] = '1';
                    availWorkers -= 1;
                    availGoods -= 1;
		            return;
                } 
                else if ((cityLayout[c][r] == '1') && (checkAdjacentNum(cityLayout, 1, c, r) >= 2))     //updates cell from 1 to 2 if adjacent to 2 cells of value that is at least 1
                { 
                    cityLayout[c][r] = '2';
                    availWorkers -= 1;
                    availGoods -= 1;
		            return;
                }
                else if ((cityLayout[c][r] == '2') && (checkAdjacentNum(cityLayout, 1, c, r) >= 3))     //updates cell from 2 to 3 if adjacent to 3 cells of value that is at least 2
                { 
                    cityLayout[c][r] = '3';
                    availWorkers -= 1;
                    availGoods -= 1;
		            return;
                }
            }
        }
    }
}

/*
This city has grown significantly since last time. More people are settling in houses, and now we have apartment complexes. To keep up with the needs of the peopl, we needed to create more jobs.
We want this city to be self reliant so therefore, we have to grow our commercial branch a little bit. In this version we have implemented a way for commercial to now grow to 3!
*/