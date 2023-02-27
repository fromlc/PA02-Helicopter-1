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
// put altitude and distance in reference parameters
//------------------------------------------------------------------------------
void Helicopter::getPos(int& _altitude, int& _distance) {
	_altitude = altitude;
	_distance = distance;
}

//------------------------------------------------------------------------------
// increase altitude by absolute passed value
//------------------------------------------------------------------------------
void Helicopter::goUp(int incAltitude) { altitude += abs(incAltitude); }

//------------------------------------------------------------------------------
// decrease altitude by absolute passed value
//------------------------------------------------------------------------------
void Helicopter::goDown(int decAltitude) { altitude += abs(decAltitude); }

//------------------------------------------------------------------------------
// increase altitude by absolute passed value
//------------------------------------------------------------------------------
void Helicopter::goForward(int incDistance) { distance += abs(incDistance); }

//------------------------------------------------------------------------------
// reset altitude to 0
//------------------------------------------------------------------------------
void Helicopter::goLand() { altitude = 0; }
