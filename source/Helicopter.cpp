//------------------------------------------------------------------------------
// Helicopter.cpp : class definition
//------------------------------------------------------------------------------
#include "Helicopter.h"

#include <cstdlib>			// abs()

//------------------------------------------------------------------------------
// constructor
//------------------------------------------------------------------------------
Helicopter::Helicopter()
	: altitude(0)
	, distance(0)
	, totalDistance(0)
	, legsFlown(0)
{ }

//------------------------------------------------------------------------------
// returns current altitude
//------------------------------------------------------------------------------
int Helicopter::getAltitude() const { return altitude; }

//------------------------------------------------------------------------------
// returns distance flown so far
//------------------------------------------------------------------------------
int Helicopter::getDistance() const { return distance; }

//------------------------------------------------------------------------------
// returns total distance flown
//------------------------------------------------------------------------------
int Helicopter::getTotalDistance() const { return totalDistance; }

//------------------------------------------------------------------------------
// puts altitude and distance in reference parameters
//------------------------------------------------------------------------------
void Helicopter::getPosition(int& _altitude, int& _distance)
{
	_altitude = altitude;
	_distance = distance;
}

//------------------------------------------------------------------------------
// returns flight segments completed
//------------------------------------------------------------------------------
int Helicopter::getLegsFlown() const { return legsFlown; }

//------------------------------------------------------------------------------
// returns true if altitude > 0, false otherwise
//------------------------------------------------------------------------------
bool Helicopter::inFlight() { return altitude > 0; }

//------------------------------------------------------------------------------
// returns reference to helo name string
//------------------------------------------------------------------------------
const std::string& Helicopter::getName() const { return name; }

//------------------------------------------------------------------------------
// sets helo name string
//------------------------------------------------------------------------------
void Helicopter::setName(const std::string& heloName) { name = heloName; };

//------------------------------------------------------------------------------
// - increases altitude by absolute passed value
// - returns current altitude 
//------------------------------------------------------------------------------
int Helicopter::goUp(int incAltitude)
{
	altitude += abs(incAltitude);
	return altitude;
}

//------------------------------------------------------------------------------
// - decreases altitude by absolute passed value
// - returns current altitude 
//------------------------------------------------------------------------------
int Helicopter::goDown(int decAltitude)
{
	if (altitude) {
		altitude -= abs(decAltitude);
	}
	return altitude;
}

//------------------------------------------------------------------------------
// - increases altitude by absolute passed value
// - returns distance flown so far
//------------------------------------------------------------------------------
int Helicopter::goForward(int incDistance)
{
	incDistance = abs(incDistance);
	
	distance += incDistance;

	// track total distance flown
	totalDistance += incDistance;

	return distance;
}

//------------------------------------------------------------------------------
// resets altitude to 0
//------------------------------------------------------------------------------
void Helicopter::goLand() { altitude = 0; legsFlown++; }

//------------------------------------------------------------------------------
// resets distance to 0
//------------------------------------------------------------------------------
void Helicopter::resetDistance() { distance = 0; }

//------------------------------------------------------------------------------
// adds distance flown since liftoff to total distance flown
//------------------------------------------------------------------------------
void Helicopter::updateTotalDistance(int legDist) { totalDistance += legDist; }
