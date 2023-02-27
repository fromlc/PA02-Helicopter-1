//------------------------------------------------------------------------------
// Helicopter.cpp : class declaration
//------------------------------------------------------------------------------
#ifndef HELICOPTER_H
#define HELICOPTER_H

//------------------------------------------------------------------------------
// Helicopter
//------------------------------------------------------------------------------
class Helicopter {
private:
	int altitude;
	int distance;

public:
	// constructor
	Helicopter();

	// returns current altitude
	int getAltitude() const;
	// returns distance flown so far
	int getDistance() const;
	// puts altitude and distance in reference params
	void getPosition(int&, int&);

	// increases altitude by absolute passed value, returns current altitude
	int goUp(int);
	// decreases altitude by absolute passed value, returns current altitude
	int goDown(int);
	// increases distance by absolute passed value, returns distance flown so far
	int goForward(int);
	
	// resets altitude to 0
	void goLand();
};
#endif // HELICOPTER_H
