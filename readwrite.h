#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

string readFile(string fname,int line);
void readLog(string fname, int step);
vector<vector<char>> readVector(string fname);
vector<vector<char>> readVectorLog(string fname,int step);
void writeFile(string fname,vector<vector <char>>, int timeStep);
