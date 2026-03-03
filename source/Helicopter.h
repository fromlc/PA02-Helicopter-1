//------------------------------------------------------------------------------
// Helicopter.cpp : class declaration
//------------------------------------------------------------------------------
#ifndef HELICOPTER_H
#define HELICOPTER_H

#include <string>

//------------------------------------------------------------------------------
// Helicopter
//------------------------------------------------------------------------------
class Helicopter 
{
private:
	int altitude;
	int distance;
	std::string name;

public:
	// constructor
	Helicopter();

	// returns current altitude
	int getAltitude() const;

	// returns distance flown so far
	int getDistance() const;

	// puts altitude and distance in reference params
	void getPosition(int&, int&);

	// returns true if altitude > 0, false otherwise
	bool inFlight();

	// returns reference to helo name string
	const std::string& getName() const;
	// sets helo name string
	void setName(const std::string&);

	// increases altitude by absolute passed value, returns current altitude
	int goUp(int);
	// decreases altitude by absolute passed value, returns current altitude
	int goDown(int);
	// increases distance by absolute passed value, returns distance flown so far
	int goForward(int);
	
	// resets altitude to 0
	void goLand();

	// resets distance to 0
	void resetDistance();
};
#endif // HELICOPTER_H
