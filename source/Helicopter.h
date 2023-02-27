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
	Helicopter();				// constructor

	void getPos(int&, int&);	// put altitude and distance in reference params
	void goUp(int);				// increase altitude by absolute passed value
	void goDown(int);			// decrease altitude by absolute passed value
	void goForward(int);		// increase distance by absolute passed value
	void goLand();				// reset altitude to 0
};
#endif // HELICOPTER_H
