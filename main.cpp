#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <vector>
#include "residential.h"
#include "industrial.h"
#include "commercial.h"
#include "pollution.h"
#include "functions.h"
#include "readwrite.h"
#include "zoom.h"
using namespace std;

int main()
{
    string config;
    vector<vector<char>> cells;		// 2d vector to represent cells

    cout << "Input name of configuration file: ";	// prompt for config file name
	getline(cin, config);
    
    string regFile;			// region file name
	string maxSteps;		// max time steps of simulation
	string refRate;			// refresh rate

    regFile = readFile(config,0);
   	maxSteps = readFile(config,1);
    refRate = readFile(config,2);
    cells = readVector(regFile);
	
	int max = stoi(maxSteps);		// max time steps after conversion
	int rate = stoi(refRate);		// refresh rate after conversion
	
	//initialize reference zones
	vector<vector<char>> zones = zoneInit(cells);
	int timeStep = 0;	//keeps track of current time step
	int availWorkers = 0;	//tracks available workers
	int availGoods = 0;		//tracks available goods

	PollutionManager pol(cells);		//pollution tracker
	
	//grow city
	while(timeStep <= max) {		//while max time steps has not been reached
		system("clear");		//clear screen for animation
		//output layout for each time step
		cout << "Time Step: " << timeStep << endl;
		for(unsigned i=0; i<cells.size(); i++) {
			for(unsigned j=0; j<cells[i].size(); j++) {
				cout << cells[i][j] << " ";
			}
			cout << endl;
		}
		cout << "Available Workers: " << availWorkers << endl;
		cout << "Available Goods: " << availGoods << endl;

		updateRes(cells, zones, availWorkers);		//update residential zones if possible
		updateCom(cells, zones, availWorkers, availGoods); 		//update commercial zones if possible
		updateInd(cells, zones, availWorkers, availGoods);		//update ind zones if possible
		writeFile("log.txt", cells, timeStep);		// log
		timeStep++;		//increment time step
		sleep(1);		//for animation
	}
	
	pol.spreadAirPol(zones, cells);		//update pollution
	pol.spreadLightPol(zones, cells);	
	pol.spreadSoundPol(zones, cells);

	cout << endl << "*************************" << endl;
	cout << "Pollution Counts: " << endl;
	cout << "Air: " << pol.getAirPol() << endl;
	cout << "Light: " << pol.getLightPol() << endl;
	cout << "Sound: " << pol.getSoundPol() << endl;
	//cout << "Total: " << pol.getTotalPollution() << endl;
	cout << "*************************" << endl << endl;

	while (timeStep != -1){								// look at specific timestep
		int xS;
		int yS;	// start x, y
		int xE;
		int yE;	// end x, y

		vector<vector<char>> zoomZone;

		cout << "Which time step to look at:" << endl;
		cin >> timeStep;
		readLog("log.txt", timeStep);					// read map at timestep from log
		cout << endl;

		if (timeStep != -1) {
			cout << ("Enter '-1' to exit.") << endl;
			
			cout << "Take a closer look? Insert two coordinate x y" << endl;
			cout << "Start coord: ";
			cin >> xS;
			cin >> yS;

			cout << "End Coord: ";
			cin >> xE;
			cin >> yE;

			zoomZone = zoom(xS,yS,xE,yE,timeStep);

			// pol.spreadAirPol(_,_);		//update pollution
			// cout << "Air: " << pol.getAirPol() << endl;
			
			
			// call polution for that time step
			// break it down to be within bounds
			// is this an ok amount of pollution?
			// compare it to average pollution 
		}

	
	}

	return 0;
}



