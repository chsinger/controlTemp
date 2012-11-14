controlTemp: controlTemp.cpp tempSensor.o tempSensor.h
	g++ -o controlTemp -Wall controlTemp.cpp tempSensor.o -L tempSensor.h
