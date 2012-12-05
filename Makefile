controlTemp: controlTemp.cpp tempSensor.o tempSensor.h
	g++ -o controlTemp -Wall controlTemp.cpp tempSensor.o RCSwitch.o -L tempSensor.h -L RCSwitch.h -lrrd -l wiringPi
