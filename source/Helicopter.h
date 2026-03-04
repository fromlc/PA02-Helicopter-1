//------------------------------------------------------------------------------
// Helicopter.h : class declaration
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
	int totalDistance;
	int legsFlown;
	std::string name;

public:
	// constructor
	Helicopter();

	// returns current altitude
	int getAltitude() const;

	// returns distance flown since liftoff
	int getDistance() const;

	// puts altitude and distance in reference params
	void getPosition(int& y, int& x);

	// returns total distance flown
	int getTotalDistance() const;

	// returns flight segments completed
	int getLegsFlown() const;


	// returns true if altitude > 0, false otherwise
	bool inFlight();

	// returns reference to helo name string
	const std::string& getName() const;
	// sets helo name string
	void setName(const std::string& heloName);

	// increases altitude by absolute passed value, returns current altitude
	int goUp(int y);
	// decreases altitude by absolute passed value, returns current altitude
	int goDown(int y);
	// increases distance by absolute passed value, returns distance flown so far
	int goForward(int x);
	
	// resets altitude to 0
	void goLand();

	// resets distance flown since liftoff to 0
	void resetDistance();

	// adds distance flown since liftoff to total distance flown
	void updateTotalDistance(int leg);
};
#endif // HELICOPTER_H
