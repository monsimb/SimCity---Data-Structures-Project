#include <iostream>
#include <vector>
#include "residential.h"
#include "functions.h"
using namespace std;

void updateRes(vector<vector<char>> &cityLayout, vector<vector<char>> zoneLayout, int &availWorkers)
{ 
	int c, l;	//column, row
	for(l = 0; l < zoneLayout.size(); l++)
    {
	    for(c = 0; c < zoneLayout[l].size(); c++) 
		{
            if(zoneLayout[l][c] == 'A') 
            { //Updating apartment cells
                if ((cityLayout[l][c] == 'A') && (checkAdjacentLet(cityLayout, 'T', l, c) >= 1)) 
                {
                        cityLayout[l][c] = '1';
                        availWorkers += 3;
		                return;
                }
                else if ((cityLayout[l][c] == 'A') && (checkAdjacentNum(cityLayout, 1, l, c) >= 1))
		        { //updates cell from 'R' to 1 if adjacent to 1 cells of value that is at least 'T' or 1
                    cityLayout[l][c] = '1';
                    availWorkers += 3;
                	return;
                }        
                else if ((cityLayout[l][c] == '1') && (checkAdjacentNum(cityLayout, 1, l, c) >= 2))
                { //updates cell from 1 to 2 if adjacent to 2 cells of value that is at least 1
                    cityLayout[l][c] = '2';
                    availWorkers += 3;
		            return;
                }
                else if ((cityLayout[l][c] == '2') && (checkAdjacentNum(cityLayout, 2, l, c) >= 3))
                { //updates cell from 2 to 3 if adjacent to 3 cells of value that is at least 2, which lets the top 2 corner cells update past 2
                     cityLayout[l][c] = '3';
                    availWorkers += 3;
		            return;
                }
            }
            if(zoneLayout[l][c] == 'H') //Updating house cells
            {
                if (cityLayout[l][c] == 'H' && checkAdjacentLet(cityLayout, 'T', l, c) >= 1) 
				{
                    cityLayout[l][c] = '1';
                    availWorkers += 1;
		            return;
                }
                else if (cityLayout[l][c] == 'H' && checkAdjacentNum(cityLayout, 1, l, c) >= 1) 
		        { //updates cell from 'R' to 1 if adjacent to 1 cells of value that is at least 'T' or 1
                    cityLayout[l][c] = '1';
                    availWorkers += 1;
		            return;
                }         
                else if (cityLayout[l][c] == '1' && checkAdjacentNum(cityLayout, 1, l, c) >= 2)
                { //updates cell from 1 to 2 if adjacent to 2 cells of value that is at least 1
                    cityLayout[l][c] = '2';
                    availWorkers += 1;
		            return;
                }
                else if (cityLayout[l][c] == '2' && checkAdjacentNum(cityLayout, 2, l, c) >= 3)
                { //updates cell from 2 to 3 if adjacent to 3 cells of value that is at least 2, which lets the bottom 2 corner cells update past 2
                    cityLayout[l][c] = '3';
                    availWorkers += 1;
		            return;
                }
                else if (cityLayout[l][c] == '3' && checkAdjacentNum(cityLayout, 3, l, c) >= 4)
                { //updates cell from 3 to 4 if adjacent to 4 cells of value that is at least 3
                    cityLayout[l][c] = '4';
                    availWorkers += 1;
		            return;
                }
                else if (cityLayout[l][c] == '3' && checkAdjacentNum(cityLayout, 4, l, c) >= 3)
                { //updates bottom corner cells from 3 to 4 if adjacent to 3 cells of value that is at least 4
                    cityLayout[l][c] = '4';
                    availWorkers += 1;
		            return;
                }
                else if (cityLayout[l][c] == '4' && checkAdjacentNum(cityLayout, 4, l, c) >= 5)
                { //updates cell from 4 to 5 if adjacent to 5 cells of value that is at least 4
                    cityLayout[l][c] = '5';
                    availWorkers += 1;
		            return;
                }          
            }
        }
    }
}
/*
In order to add more depth to the functionality of the code in project 2, I needed to alter the rules a bit for the cells to grow.
In the original project it was impossible for a cell in residential to grow to 4 or 5 given the adjacency rules set in project 1.
To fix this issue for project 2, especially now that we had to account for apartment cell growth I tweaked the number of adjacent cells to cause growth.
For the apartment functionality, each 'A' cell was an apartment complex rather than a single apartment, which is why workers grow by 3 instead of 1.
Which would mean that when an apartment complex is full, it would have 9 workers as opposed to 3. Each 'H' cell represents a single house.
This means that every member of the house is an available worker. We will assume each member is an adult for the sake of child labor laws.
*/