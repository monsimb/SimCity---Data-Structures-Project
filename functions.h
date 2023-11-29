#include <iostream>
#include <vector>
using namespace std;

/*isValidPos and checkAdjacent found at:
https://www.geeksforgeeks.org/find-all-adjacent-elements-of-given-element-in-a-2d-array-or-matrix/#
method 1
*/
bool isValidPos(int i, int j, int n, int m);
int checkAdjacentLet(vector<vector<char>> v, char ch, int i, int j);
int checkAdjacentNum(vector<vector<char>> v, int ch, int i, int j);
vector<vector<char>> zoneInit(vector<vector<char>> cityLayout);
