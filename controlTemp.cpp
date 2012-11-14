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

#include "tempSensor.h"

using namespace std;


int main (void) {

	tempSensor sens1("28-000003c31d58"), sens2("28-000004071f35"),
							sens3("28-0000040743a0");

	while (1) {

		cout << "Temp1: " << sens1.getTemp() << " Temp2: " << sens2.getTemp()
			<< " Temp3: " << sens3.getTemp() << endl;
		sleep(5);
	}

}



