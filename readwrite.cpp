#include <iostream>
#include <fstream>
#include <vector>
#include "readwrite.h"
using namespace std;

// can be improved by handling open, fail in as class set-up

string readFile(string fname, int line){	
	fstream fin;
	string val;
	int dIndx;

    fin.open( fname, ios::in | ios::out );
	
	if(fin.fail())									// check that file opens properly
	{
		cout << "Config file open failed." << endl;
		exit(1);
	}
	if (fin.is_open()){
		getline(fin, val);
		if (line>0){
			for(int i=0; i<line; i++){
				getline(fin,val);
				val.erase(0,i);
			}
		}
		dIndx = val.find(":");
		if(dIndx != -1) {
			val.erase(0, dIndx + 1);
		}
	

	}

	fin.close();

	return val;	
}

void readLog(string fname, int step){		// std cap on coord of 30
	fstream fin;
	string val;				// line being read
	int dIndx;
	
	fin.open( fname, ios::in | ios::out );
	
	if(fin.fail())					// check that file opens properly
	{
		cout << fname <<" file open failed." << endl;
		exit(1);
	}
	
	if (fin.is_open()){				// if it opened ok
		while (true){
			getline(fin, val);		// read from file to find the right step

			if (val == "Time Step: " + to_string(step)){	// Checks for the right time step

				while (true){
					cout<<val<<endl;
					getline(fin,val);
				
					if (val == "") break;					// Break at end of time	
				}
			}

			if (fin.eof()) break;							// If time step is not in file, break loop
		}
	}
	fin.close();
}

vector<vector<char>> readVectorLog(string fname,int step){
	ifstream fin;
	string val;						// line being read
	vector<char> temp;				// temp vector to hold each line
	vector<vector<char>> cells;		// 2d vector to represent cells

    fin.open( fname, ios::in | ios::out );
	
	if(fin.fail())									// check that file opens properly
	{
		cout << "Config file open failed." << endl;
		exit(1);
	}

	if (fin.is_open()){
		while (true){
			getline(fin,val);
			if (val == "Time Step: " + to_string(step)){	// Checks for the right time step				
				while (true){	
					getline(fin,val);
					for(int i=0; i<val.length(); i++) {
						if(val[i] != ',') {
							temp.push_back(val[i]);		// add character to temp vector
						}
					}
					cells.push_back(temp);		// add first row to 2d vector
					temp.clear();				// reset temp vector for next row

					if(val == "") break;
				}
				break;
			}


		}
	}
	fin.close();
	return cells;

}

vector<vector<char>> readVector(string fname){
	ifstream fin;
	string currLine;				// line being read
	vector<char> temp;				// temp vector to hold each line
	vector<vector<char>> cells;		// 2d vector to represent cells


    fin.open( fname, ios::in | ios::out );
	
	if(fin.fail())									// check that file opens properly
	{
		cout << "Config file open failed." << endl;
		exit(1);
	}
	
	while(!fin.eof()) {
		getline(fin, currLine);						// get first row
		for(int i=0; i<currLine.length(); i++) {
			if(currLine[i] != ',') {
				temp.push_back(currLine[i]);		// add character to temp vector
			}
		}
		
		cells.push_back(temp);		// add first row to 2d vector
		temp.clear();				// reset temp vector for next row
	}
	fin.close();
	return cells;
}

void writeFile(string fname,vector<vector <char>> lines,int timeStep){
	ofstream fin;
	string line;
	
	if (timeStep == 0){		// clear file for new run
		fin.open( fname, ios::out | ios::trunc );
	}
	else{
		fin.open( fname, ios::app);
	}

	if(fin.fail())									// check that file opens properly
	{
		ofstream fin(fname);
	}
	

	fin<<"Time Step: "<<timeStep<<endl;
	for (int l=0; l<lines.size()-1;l++){
		for (int c=0;c<=lines.size()-2;c++){
			line = line+" "+(lines[l][c]);
		}
		fin<<line<<endl;
		line = "";
	}
	fin<<endl;
	fin.close();


}
