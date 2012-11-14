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

	tempSensor sens1, sens2("28-000004071f35");
	sens1.setId("28-000003c31d58");

	cout << "Temp1: " << sens1.getTemp() << endl;
	cout << "Temp2: " << sens2.getTemp() << endl;

}



