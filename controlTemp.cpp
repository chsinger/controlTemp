/*
 * controlTemp.cpp
 *
 *  Created on: Nov 7, 2012
 *      Author: christoph
 */


#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sstream>
//#include <vector>
#include <ctime>


extern "C" {
	#include <rrd.h>
}

#include "tempSensor.h"
#include "RCSwitch.h"

using namespace std;



void writeRrd (float temp1, float temp2, float temp3) {
	int rrd_argc=3;
	char *rrd_argv[rrd_argc];
	stringstream stream;
	rrd_argv[0]="update";
	rrd_argv[1]="/home/pi/stuff/readTemp/tempGrow.rrd";

	stream << "N:" << temp1 << ":" << temp2 << ":" << temp3 << ends;

	rrd_argv[2] = new char[stream.str().size()];
	strcpy(rrd_argv[2],stream.str().c_str());
	

 	int ret = rrd_update(rrd_argc,rrd_argv);

	stream.str("");
	stream.clear();

		delete[] rrd_argv[2];
}

string getTimestamp() {

	char date[256];
	time_t rawtime;
	struct tm *tmp;

	time (&rawtime);
	tmp = localtime(&rawtime);
	strftime(date, sizeof(date),"%Y/%m/%d %X", tmp);

	return date;

}

int main (void) {

	ofstream logfile;
	logfile.open ("controlTemp.log", ios::app);
	

	int onoff = 0;

	wiringPiSetup();
	RCSwitch heizmatte = RCSwitch();
	heizmatte.enableTransmit(1);

	float temp1, temp2, temp3;
//	vector<tempSensor> tempSensors;
	tempSensor sens1("28-000003c31d58"), sens2("28-000004071f35"),
							sens3("28-0000040743a0");

//	tempSensors.push_back(sens1);
//	tempSensors.push_back(sens2);
//	tempSensors.push_back(sens3);


	logfile << getTimestamp() << " Started control" << endl;

	while (1) {



		temp1 = sens1.getTemp();
		temp2 = sens2.getTemp();
		temp3 = sens3.getTemp();


/*		for (vector<tempSensor>::iterator it = tempSensors.begin(); it != tempSensors.end(); ++it ) {
			cout << it->getTemp() << endl;
		}		
*/

	writeRrd(temp1, temp2, temp3);

	if ( temp1 >= 30.50 ) { 
		heizmatte.switchOff("11111",3);
		if ( onoff == 1 ) {
			logfile << getTimestamp() << " Switched off at temperature: " << temp1 << endl;
			onoff = 0;
		}
	}	
	else if ( temp1 <= 30.00 ) { 
		heizmatte.switchOn("11111",3);
		if ( onoff == 0 ) {
			logfile << getTimestamp() << " Switched on at temperature: " << temp1 << endl;
			onoff = 1;
		}
	}	
		
		sleep(10);
	}



	logfile << getTimestamp() << " Stopped control" << endl;
	
	logfile.close();

}



