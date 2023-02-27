//------------------------------------------------------------------------------
// Helicopter.cpp : class definition
//------------------------------------------------------------------------------
#include "Helicopter.h"

#include <cstdlib>			// abs()

//------------------------------------------------------------------------------
// constructor
//------------------------------------------------------------------------------
Helicopter::Helicopter() { altitude = distance = 0; }

//------------------------------------------------------------------------------
// returns current altitude
//------------------------------------------------------------------------------
int Helicopter::getAltitude() const { return altitude; }

//------------------------------------------------------------------------------
// returns distance flown so far
//------------------------------------------------------------------------------
int Helicopter::getDistance() const { return distance; }

//------------------------------------------------------------------------------
// puts altitude and distance in reference parameters
//------------------------------------------------------------------------------
void Helicopter::getPosition(int& _altitude, int& _distance) {
	_altitude = altitude;
	_distance = distance;
}

//------------------------------------------------------------------------------
// - increases altitude by absolute passed value
// - returns current altitude 
//------------------------------------------------------------------------------
int Helicopter::goUp(int incAltitude) {
	altitude += abs(incAltitude);
	return altitude;
}

//------------------------------------------------------------------------------
// - decreases altitude by absolute passed value
// - returns current altitude 
//------------------------------------------------------------------------------
int Helicopter::goDown(int decAltitude) {
	if (altitude) {
		altitude -= abs(decAltitude);
	}
	return altitude;
}

//------------------------------------------------------------------------------
// - increases altitude by absolute passed value
// - returns distance flown so far
//------------------------------------------------------------------------------
int Helicopter::goForward(int incDistance) {
	distance += abs(incDistance);
	return distance;
}

//------------------------------------------------------------------------------
// resets altitude to 0
//------------------------------------------------------------------------------
void Helicopter::goLand() { altitude = 0; }
