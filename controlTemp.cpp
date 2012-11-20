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


extern "C" {
	#include <rrd.h>
}

#include "tempSensor.h"

using namespace std;


int main (void) {

	int rrd_argc=4;
	char *rrd_argv[rrd_argc];
	float temp1, temp2, temp3;
	int ret;
	stringstream stream;

	tempSensor sens1("28-000003c31d58"), sens2("28-000004071f35"),
							sens3("28-0000040743a0");

	while (1) {


		rrd_argv[0]="update";
		rrd_argv[1]="/home/pi/stuff/readTemp/tempGrow.rrd";

		temp1 = sens1.getTemp();
		temp2 = sens2.getTemp();
		temp3 = sens3.getTemp();

		if ( sens1.getLastTemp() != 0.0 && ( temp1 < sens1.getLastTemp() - 5 || temp1 > sens1.getLastTemp() + 5 )) { 
			temp1 = sens1.getLastTemp();
		} 
		if ( sens2.getLastTemp() != 0.0 && ( temp2 < sens2.getLastTemp() - 5 || temp2 > sens2.getLastTemp() + 5 )) { 
			temp2 = sens2.getLastTemp();
		} 
		if ( sens3.getLastTemp() != 0.0 && ( temp3 < sens3.getLastTemp() - 5 || temp3 > sens3.getLastTemp() + 5 )) { 
			temp3 = sens3.getLastTemp();
		} 

		stream << "N:" << temp1 << ":" << temp2 << ":" << temp3;

		rrd_argv[2] = new char[stream.str().size()];
		
		strcpy(rrd_argv[2],stream.str().c_str());

		ret = rrd_update(rrd_argc,rrd_argv);

/*		cout << "Temp1: " << temp1 << " Temp2: " << temp2
			<< " Temp3: " << temp3 << " Ret: " << ret << " Stream: " << rrd_argv[2] <<  endl;
*/
		stream.str("");
		stream.clear();

		free(rrd_argv[2]);			

		sleep(60);
	}

}



