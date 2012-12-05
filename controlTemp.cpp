/*
 * controlTemp.cpp
 *
 *  Created on: Nov 7, 2012
 *      Author: christoph
 */


#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <vector>


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
//	rrd_argv[0]= new char[6];
//	strcpy(rrd_argv[0],"update\0");
	rrd_argv[0]="update";
//	rrd_argv[1]= new char[36];
//	strcpy(rrd_argv[1],"/home/pi/stuff/readTemp/tempGrow.rrd\0");
	rrd_argv[1]="/home/pi/stuff/readTemp/tempGrow.rrd";

	stream << "N:" << temp1 << ":" << temp2 << ":" << temp3 << ends;

	rrd_argv[2] = new char[stream.str().size()];
	strcpy(rrd_argv[2],stream.str().c_str());
	

 	int ret = rrd_update(rrd_argc,rrd_argv);
//	cout << ret << " " <<rrd_argv[0] << " " << rrd_argv[1] << " " <<  "String: " << rrd_argv[2] << endl;

	stream.str("");
	stream.clear();

//	for ( int i = 0; i < rrd_argc; i++)
//		delete[] rrd_argv[i];			

		delete[] rrd_argv[2];
}

int main (void) {

	wiringPiSetup();
	RCSwitch heizmatte = RCSwitch();
	heizmatte.enableTransmit(1);

	float temp1, temp2, temp3;
	vector<tempSensor> tempSensors;
	tempSensor sens1("28-000003c31d58"), sens2("28-000004071f35"),
							sens3("28-0000040743a0");

	tempSensors.push_back(sens1);
	tempSensors.push_back(sens2);
	tempSensors.push_back(sens3);


	while (1) {



		temp1 = sens1.getTemp();
		temp2 = sens2.getTemp();
		temp3 = sens3.getTemp();

/*
		if ( sens1.getLastTemp() != 0.0 && ( temp1 < sens1.getLastTemp() - 5 || temp1 > sens1.getLastTemp() + 5 )) { 
			cout << "Before: Temp1: " << temp1 << " Last-Temp: " << sens1.getLastTemp() << endl;
			temp1 = sens1.getLastTemp();
			sens1.setLastTemp(temp1);
			cout << "After:  Temp1: " << temp1 << " Last-Temp: " << sens1.getLastTemp() << endl;
		} 
		if ( sens2.getLastTemp() != 0.0 && ( temp2 < sens2.getLastTemp() - 5 || temp2 > sens2.getLastTemp() + 5 )) { 
			cout << "Before: Temp2: " << temp2 << " Last-Temp: " << sens2.getLastTemp() << endl;
			temp2 = sens2.getLastTemp();
			sens2.setLastTemp(temp2);
			cout << "After:  Temp2: " << temp1 << " Last-Temp: " << sens2.getLastTemp() << endl;
		} 
		if ( sens3.getLastTemp() != 0.0 && ( temp3 < sens3.getLastTemp() - 5 || temp3 > sens3.getLastTemp() + 5 )) { 
			cout << "Before: Temp3: " << temp3 << " Last-Temp: " << sens3.getLastTemp() << endl;
			temp3 = sens3.getLastTemp();
			sens3.setLastTemp(temp3);
			cout << "After:  Temp3: " << temp3 << " Last-Temp: " << sens3.getLastTemp() << endl;
		} 
*/


/*		cout << "Temp1: " << temp1 << " Temp2: " << temp2
			<< " Temp3: " << temp3 << " Ret: " <<  endl;
*/	
/*		for (vector<tempSensor>::iterator it = tempSensors.begin(); it != tempSensors.end(); ++it ) {
			cout << it->getTemp() << endl;
		}		
*/

	writeRrd(temp1, temp2, temp3);

	if ( temp1 >= 28 ) 
		heizmatte.switchOff("11111",3);
	else if ( temp1 <= 26 ) 
		heizmatte.switchOn("11111",3);
		


		sleep(1);
	}

}



