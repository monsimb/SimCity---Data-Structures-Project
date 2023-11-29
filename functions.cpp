#include <iostream>
#include <cctype>
#include <vector>
#include "functions.h"
using namespace std;

/*isValidPos and checkAdjacent found at:
https://www.geeksforgeeks.org/find-all-adjacent-elements-of-given-element-in-a-2d-array-or-matrix/#
method 1
*/
bool isValidPos(int i, int j, int n, int m) {
    if ((i >= 0) && (j >= 0) && (i < n) && (j < m)) {
        return true;
	}
    return false;
}

// Function that returns all adjacent elements
int checkAdjacentLet(vector<vector<char>> v, char ch, int i, int j) {
    // Size of given 2d vector
    int m, n;
    m = n = v[0].size();	//dimensions
 
    //counter to track number of cells with desired char
	int count = 0;

    // Checking for all the possible adjacent positions
	for(int x = -1; x <= 1; x++) {
		for(int y = -1; y <= 1; y++) {
			if((!(x==0 && y==0)) && (isValidPos(i+x, j+y, n, m))) {
				if(v[i+x][j+y] == ch) {
					count++;
				}
			}
		}
	}

	return count;	//return number of cells with char
}

int checkAdjacentNum(vector<vector<char>> v, int ch, int i, int j) {		//same as above function, just 
    // Size of given 2d vector
	int m, n;
    m = n = v[0].size();	//dimensions
	int num = 0;		//variable to store converted char
 
    //counter to track number of cells with desired char
	int count = 0;

	for(int x = -1; x <= 1; x++) {
		for(int y = -1; y <= 1; y++) {
			if((!(x==0 && y==0)) && (isValidPos(i+x, j+y, n, m))) {
				if(isdigit(v[i+x][j+y])) {
					num = v[i+x][j+y] - '0';		//convert to int
					if(num >= ch) {		//comparing with given int
						count++;
					}
				}
			}
		}
	}

	return count;	//return number of cells with char
}


vector<vector<char>> zoneInit(vector<vector<char>> cityLayout) {		//init map to track zones
	vector<vector<char>> zoneLayout;					//zone layout
	vector<char> temp;
	
	for (unsigned l = 0; l < cityLayout.size(); l++){				// l = line
		for (unsigned c = 0; c < cityLayout[l].size(); c++){     	// c = column 
			if (cityLayout[l][c] == 'A' || cityLayout[l][c] == 'H' || cityLayout[l][c] == 'C' || cityLayout[l][c] == 'I') {
				temp.push_back(cityLayout[l][c]);					//add letter to zone layout
			}
			else {
				temp.push_back('_');				// blank space if not a zoned cell
			}
		}
		zoneLayout.push_back(temp);
		temp.clear();
	}

	return zoneLayout;
}

/*NOT USED YET. SAVING FOR LATER*/
// void checkGrowth(vector<vector<char>> cityLayout, vector<vector<char>> zoneLayout, int availWorkers, int availGoods) {
// 	bool comGrowth = false;
// 	bool indGrowth = false;
// 	bool resGrowth = false;

// 	vector<int> x, y, adj;
// 	int pop, nextPop;
// 	int cx, cy, cadj, ix, iy, iadj, rx, ry, radj;		//coords for where growth will occur
// 	for(int r = 0; r < zoneLayout.size(); r++) {
// 		for(int c = 0; c < zoneLayout[r].size(); c++) {
// 			//Res Check
// 			if(zoneLayout[r][c] == 'R')
//             {
//                 if((cityLayout[r][c] == '1') && (checkAdjacentNum(cityLayout, 1, r, c) >= 2)) {
//                     resGrowth = true;
// 					x.push_back(r);
// 					y.push_back(c);
// 					adj.push_back(checkAdjacentNum(cityLayout, 1, r, c));
//                 }
//                 cout << "checking for 3 if" << endl;
//                 if ((cityLayout[r][c] == '2') && (checkAdjacentNum(cityLayout, 2, r, c) >= 4)) {
//                     resGrowth = true;
// 					x.push_back(r);
// 					y.push_back(c);
// 					adj.push_back(checkAdjacentNum(cityLayout, 1, r, c));
//                 }
//                 cout << "checking for 4 if" << endl;
//                 if ((cityLayout[r][c] == '3') && (checkAdjacentNum(cityLayout, 3, r, c) >= 6)) {
// 					resGrowth = true;
// 					x.push_back(r);
// 					y.push_back(c);
// 					adj.push_back(checkAdjacentNum(cityLayout, 1, r, c));
//                 }
//                 cout << "checking for 5 if" << endl;
//                 if ((cityLayout[r][c] == '4') && (checkAdjacentNum(cityLayout, 4, r, c) >= 8)) {
//                     resGrowth = true;
// 					x.push_back(r);
// 					y.push_back(c);
// 					adj.push_back(checkAdjacentNum(cityLayout, 1, r, c));
//                 }
//                 else if((checkAdjacentLet(cityLayout, 'T', r, c) >= 1) || (checkAdjacentNum(cityLayout, 1, r, c) >= 1)) {
//                     resGrowth = true;
// 					x.push_back(r);
// 					y.push_back(c);
// 					adj.push_back(checkAdjacentNum(cityLayout, 1, r, c));
//                 }
//             }
// 		}
// 	}

// 	for(int i = 0; i < x.size()-1; i++) {
// 		//find population
// 		if(cityLayout[x[i]][y[i]] != 'R') {
// 			pop = cityLayout[x[i]][y[i]] - '0';
// 		}
// 		if(cityLayout[x[i+1]][y[i+1]] != 'R') {
// 			nextPop = cityLayout[x[i+1]][y[i+1]] - '0';
// 		}
		
// 		//find cell with higher population
// 		if(pop < nextPop) {
// 			x.erase(x.begin() + i);
// 			y.erase(y.begin() + i);
// 		}
// 		else if(nextPop < pop) {
// 			x.erase(x.begin() + i + 1);
// 			y.erase(y.begin() + i + 1);
// 		}
		
// 		//find cell with greater adjacent population
// 		if(adj[i] > adj[i+1]) {
// 			x.erase(x.begin() + i + 1);
// 			y.erase(y.begin() + i + 1);
// 		}
// 		else if(adj[i] < adj[i + 1]) {
// 			x.erase(x.begin() + i);
// 			y.erase(y.begin() + i);
// 		}

// 		//find cell with smaller y coordinate
// 		if(y[i] > y[i+1]) {
// 			x.erase(x.begin() + i);
// 			y.erase(y.begin() + i);
// 		}
// 		else if(y[i + 1] > y[i]) {
// 			x.erase(x.begin() + i + 1);
// 			y.erase(y.begin() + i + 1);
// 		}

// 		//find cell with smaller x coordinate
// 		if(x[i] > x[i+1]) {
// 			x.erase(x.begin() + i);
// 			y.erase(y.begin() + i);
// 		}
// 		else if(x[i + 1] > x[i]) {
// 			x.erase(x.begin() + i + 1);
// 			y.erase(y.begin() + i + 1);
// 		}
// 	}
// 	rx = x[0]; ry = y[0];		//only one element should be left in vectors, save as residential coords
// 	radj = adj[0];
// 	x.clear();
// 	y.clear();
// 	adj.clear();
			
// 	for(int r = 0; r < zoneLayout.size(); r++) {
// 		for(int c = 0; c < zoneLayout[r].size(); c++) {
// 			//Ind Check
// 			if((zoneLayout[r][c] == 'I') && (availWorkers >= 2)) {		//if industrial zone and at least 2 avail workers
// 				if((cityLayout[r][c] == '1') && (checkAdjacentNum(cityLayout, 1, r, c) >= 2)) {		//grow if pop 1 and at least 2 adjacent cells with pop >= 1
// 					indGrowth = true;
// 					x.push_back(r);
// 					y.push_back(c);
// 					adj.push_back(checkAdjacentNum(cityLayout, 1, r, c));
// 				}
// 				if((cityLayout[r][c] == '2') && (checkAdjacentNum(cityLayout, 2, r, c)) >= 4) {	//grow if pop 2 and at least 4 adjacent cells with pop >= 2
// 					indGrowth = true;
// 					x.push_back(r);
// 					y.push_back(c);
// 					adj.push_back(checkAdjacentNum(cityLayout, 1, r, c));
// 				}
// 				else if((checkAdjacentLet(cityLayout, 'T', r, c) >= 1) || (checkAdjacentNum(cityLayout, 1, r, c)  >= 1)) {		//grow if next to powerline or at least one cell with at least pop 1
// 					indGrowth = true;
// 					x.push_back(r);
// 					y.push_back(c);
// 					adj.push_back(checkAdjacentNum(cityLayout, 1, r, c));
// 				}
// 			}
// 		}
// 	}

// 	for(int i = 0; i < x.size()-1; i++) {
// 		//find population
// 		if(cityLayout[x[i]][y[i]] != 'R') {
// 			pop = cityLayout[x[i]][y[i]] - '0';
// 		}
// 		if(cityLayout[x[i+1]][y[i+1]] != 'R') {
// 			nextPop = cityLayout[x[i+1]][y[i+1]] - '0';
// 		}
		
// 		//find cell with higher population
// 		if(pop < nextPop) {
// 			x.erase(x.begin() + i);
// 			y.erase(y.begin() + i);
// 		}
// 		else if(nextPop < pop) {
// 			x.erase(x.begin() + i + 1);
// 			y.erase(y.begin() + i + 1);
// 		}
		
// 		//find cell with greater adjacent population
// 		if(adj[i] > adj[i+1]) {
// 			x.erase(x.begin() + i + 1);
// 			y.erase(y.begin() + i + 1);
// 		}
// 		else if(adj[i] < adj[i + 1]) {
// 			x.erase(x.begin() + i);
// 			y.erase(y.begin() + i);
// 		}

// 		//find cell with smaller y coordinate
// 		if(y[i] > y[i+1]) {
// 			x.erase(x.begin() + i);
// 			y.erase(y.begin() + i);
// 		}
// 		else if(y[i + 1] > y[i]) {
// 			x.erase(x.begin() + i + 1);
// 			y.erase(y.begin() + i + 1);
// 		}

// 		//find cell with smaller x coordinate
// 		if(x[i] > x[i+1]) {
// 			x.erase(x.begin() + i);
// 			y.erase(y.begin() + i);
// 		}
// 		else if(x[i + 1] > x[i]) {
// 			x.erase(x.begin() + i + 1);
// 			y.erase(y.begin() + i + 1);
// 		}
// 	}
// 	ix = x[0]; iy = y[0];		//only one element should be left in vector, save as ind coords
// 	iadj = adj[0];
// 	x.clear();
// 	y.clear();
// 	adj.clear();

// 	for(int r = 0; r < zoneLayout.size(); r++) {
// 		for(int c = 0; c < zoneLayout[r].size(); c++) {
// 			//Com Check
// 			if((zoneLayout[c][r] == 'C') && (availWorkers >= 1) && (availGoods >= 1)) {		//grow if in com zone and there are avail workers and goods
// 				if((cityLayout[r][c] == '1') && (checkAdjacentNum(cityLayout, 1, r, c) >= 2)) {		//grow if pop = 1 and at least 2 adjacent cells with pop >=1
// 					comGrowth = true;
// 					x.push_back(r);
// 					y.push_back(c);
// 					adj.push_back(checkAdjacentNum(cityLayout, 1, r, c));
// 				}
// 				else if((checkAdjacentLet(cityLayout, 'T', r, c) >= 1) || (checkAdjacentNum(cityLayout, 1, r, c)  >= 1)) {		//grow if powerline or at least one cell with pop 1 nearby
// 					comGrowth = true;
// 					x.push_back(r);
// 					y.push_back(c);
// 					adj.push_back(checkAdjacentNum(cityLayout, 1, r, c));
// 				}
// 			}
// 		}
// 	}

// 	for(int i = 0; i < x.size()-1; i++) {
// 		//find population
// 		if(cityLayout[x[i]][y[i]] != 'R') {
// 			pop = cityLayout[x[i]][y[i]] - '0';
// 		}
// 		if(cityLayout[x[i+1]][y[i+1]] != 'R') {
// 			nextPop = cityLayout[x[i+1]][y[i+1]] - '0';
// 		}
		
// 		//find cell with higher population
// 		if(pop < nextPop) {
// 			x.erase(x.begin() + i);
// 			y.erase(y.begin() + i);
// 		}
// 		else if(nextPop < pop) {
// 			x.erase(x.begin() + i + 1);
// 			y.erase(y.begin() + i + 1);
// 		}
		
// 		//find cell with greater adjacent population
// 		if(adj[i] > adj[i+1]) {
// 			x.erase(x.begin() + i + 1);
// 			y.erase(y.begin() + i + 1);
// 		}
// 		else if(adj[i] < adj[i + 1]) {
// 			x.erase(x.begin() + i);
// 			y.erase(y.begin() + i);
// 		}

// 		//find cell with smaller y coordinate
// 		if(y[i] > y[i+1]) {
// 			x.erase(x.begin() + i);
// 			y.erase(y.begin() + i);
// 		}
// 		else if(y[i + 1] > y[i]) {
// 			x.erase(x.begin() + i + 1);
// 			y.erase(y.begin() + i + 1);
// 		}

// 		//find cell with smaller x coordinate
// 		if(x[i] > x[i+1]) {
// 			x.erase(x.begin() + i);
// 			y.erase(y.begin() + i);
// 		}
// 		else if(x[i + 1] > x[i]) {
// 			x.erase(x.begin() + i + 1);
// 			y.erase(y.begin() + i + 1);
// 		}
// 	}
// 	cx = x[0]; cy = y[0];		//only one element should be left in vector, save as com coords
// 	cadj = adj[0];
// 	x.clear();
// 	y.clear();
// 	adj.clear();


// 	if(comGrowth && indGrowth) {	//commercial always grows over industrial
// 		indGrowth = false;
// 	}

// 	int rPop, iPop, cPop;
// 	rPop = iPop = cPop = 0;
// 	//find population of all zones that want to grow
// 	if(resGrowth) {
// 		if(cityLayout[rx][ry] != 'R') {
// 			rPop = cityLayout[rx][ry] - '0';
// 		}
// 	}
// 	if(indGrowth) {
// 		if(cityLayout[ix][iy] != 'I') {
// 			iPop = cityLayout[ix][iy] - '0';
// 		}
// 	}
// 	if(comGrowth) {
// 		if(cityLayout[cx][cy] != 'C') {
// 			cPop = cityLayout[cx][cy] - '0';
// 		}
// 	}

// 	//cells with higher population will grow first
// 	if(cPop > rPop && resGrowth && comGrowth) {
// 		resGrowth = false;
// 	}
// 	else if(rPop > cPop && resGrowth && comGrowth) {
// 		comGrowth = false;
// 	}

// 	if(iPop > rPop && resGrowth && indGrowth) {
// 		resGrowth = false;
// 	}
// 	else if(rPop > iPop && resGrowth && indGrowth) {
// 		indGrowth = false;
// 	}

// 	//greater adjacent population will grow
// 	if(cadj > radj && resGrowth && comGrowth) {
// 		resGrowth = false;
// 	}
// 	else if(radj > cadj && resGrowth && comGrowth) {
// 		comGrowth = false;
// 	}
// 	if(iadj > radj && resGrowth && indGrowth) {

// 	}
// 	else if(radj > iadj && resGrowth && indGrowth) {

// 	}

// 	//smaller y coordinates grow
// 	if(ry < cy && resGrowth && comGrowth) {
// 		comGrowth = false;
// 	}
// 	else if(cy < ry && resGrowth && comGrowth) {
// 		resGrowth = false;
// 	}
// 	if(ry < iy && resGrowth && indGrowth) {
// 		indGrowth = false;
// 	}
// 	else if(iy < ry && resGrowth && indGrowth) {
// 		resGrowth = false;
// 	}

// 	//smaller x coordinates grow
// 	if(rx < cx && resGrowth && comGrowth) {
// 		comGrowth = false;
// 	}
// 	else if(cx < rx && resGrowth && comGrowth) {
// 		resGrowth = false;
// 	}
// 	if(rx < ix && resGrowth && indGrowth) {
// 		indGrowth = false;
// 	}
// 	else if(ix < rx && resGrowth && indGrowth) {
// 		resGrowth = false;
// 	}
// }