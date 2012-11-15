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
#include <rrd.h>

#include "tempSensor.h"

using namespace std;


int main (void) {
	
	char* rrd_argv[3];
	int rrd_argc=3;
	int rrd_ret;
	float temp1, temp2, temp3;

	tempSensor sens1("28-000003c31d58"), sens2("28-000004071f35"),
							sens3("28-0000040743a0");

	while (1) {

		temp1 = sens1.getTemp();
		temp2 = sens2.getTemp();
		temp3 = sens3.getTemp();


		rrd_argv[0]="update";
//		rrd_argv[1]="tempGrow.rrd";
//		rrd_argv[2]="N:temp1:temp2:temp3";

		rrd_ret = rrd_update(rrd_argc,rrd_argv);

		cout << "Temp1: " << temp1 << " Temp2: " << temp2
			<< " Temp3: " << temp3 << endl;
		
		sleep(5);
	}

}



