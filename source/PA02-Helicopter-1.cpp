//------------------------------------------------------------------------------
// PA02-Helicopter-1.cpp : app code for helicopter flight
// 
// Accepts commands U)p, D)own, F)orward, V)land, Q)uit
//      - Up increases altitude by ALTITUDE_GAIN feet
//      - Down decreases altitude by ALTITUDE_DROP feet
//			- Negative altitude can crash the helicopter,
//			- OR, if the resulting altitude is not lower than BUMPY_LANDING,
//				the app reports a bumpy landing and this counts as a landing.
//      - Forward increases distance flown by DISTANCE_GAIN yards
//      - Land resets altitude to 0
//      - Quit terminates the app
//		- Crashing the helicopter terminates the app
//------------------------------------------------------------------------------

#include "Helicopter.h"
#include "ansi_colors.h"

#include <iostream>

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
// debug mode reports negative altitude value after crash 
//#define LC_DEBUG

constexpr bool QUIT_FLYING = true;

constexpr int ALTITUDE_GAIN = 100;
constexpr int ALTITUDE_DROP = 51;
constexpr int DISTANCE_GAIN = 200;

constexpr int BUMPY_LANDING = -1;

const std::string APP_MENU =
"A)scend, D)escend, F)orward, V)land, Q)uit ? ";
const std::string HELO_NAME = "Huey";

constexpr char CMD_ASCEND = 'A';
constexpr char CMD_DESCEND = 'D';
constexpr char CMD_FORWARD = 'F';
constexpr char CMD_LAND = 'V';
constexpr char CMD_QUIT = 'Q';

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------
namespace fly
{
	Helicopter helo;
}

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
void initFlight();

char getPilotCommand();
bool doHeloCommand(char userCmd);

// begin command handlers
void heloUp();
bool heloDown();        // returns false on crash, true otherwise
void heloForward();
void heloLand();
void heloQuit();
// end command handlers

// bool parameter provides context for console output
void displayStatus(bool userQuit);

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main()
{
	// display app banner, instructions, status
	initFlight();

	bool keepFlying = true;
	while (keepFlying)
	{
		// loop until quit command
		keepFlying = doHeloCommand(getPilotCommand());

		// context-based console output
		displayStatus(keepFlying);

		// set distance flown to 0 when helicopter is on the ground
		if (!fly::helo.inFlight())
			fly::helo.resetDistance();
	}
	std::cout << COLOR_FG_YELLOW
		<< "Goodbye!\n\n"
		<< COLOR_RESET;
}

//------------------------------------------------------------------------------
// displays pilot instructions, initial status
//------------------------------------------------------------------------------
void initFlight()
{
	//#TODO make name random
	fly::helo.setName(HELO_NAME);

	std::cout << COLOR_FG_YELLOW;
	std::cout << "\nWelcome! You're flying a "
		<< fly::helo.getName() << " today.";
	std::cout << "\nControl your flight with these commands:\n\n";

	std::cout << COLOR_RESET << CMD_ASCEND << COLOR_FG_CYAN
		<< " increases altitude by " << ALTITUDE_GAIN << " feet,\n";
	std::cout << COLOR_RESET << CMD_DESCEND << COLOR_FG_CYAN
		<< " decreases altitude by " << ALTITUDE_DROP << " feet,\n";
	std::cout << COLOR_RESET << CMD_FORWARD << COLOR_FG_CYAN
		<< " flies forward " << DISTANCE_GAIN << " yards.\n";
	std::cout << COLOR_RESET << CMD_LAND << COLOR_FG_CYAN
		<< " lands and your " << fly::helo.getName() 
		<< " can take off again.\n";
	std::cout << COLOR_RESET << CMD_QUIT << COLOR_FG_CYAN
		<< " quits when you're done flying.\n\n";

	std::cout << COLOR_FG_YELLOW;
	std::cout << "Commands can be in upper or lower case.\n\n";

	std::cout << "If you drop too much altitude or quit in midair, ";
	std::cout << "your " << fly::helo.getName() << " will crash!\n\n";

	std::cout << COLOR_FG_CYAN
		<< "Starting " << fly::helo.getName() << " flight simulation.\n"
		<< COLOR_RESET;

	displayStatus(!QUIT_FLYING);
}

//------------------------------------------------------------------------------
// - puts user command in reference param
// - returns false on quit command, true otherwise
//------------------------------------------------------------------------------
char getPilotCommand()
{
	std::cout << COLOR_FG_CYAN << APP_MENU << COLOR_RESET;

	char cmd;
	std::cin >> cmd;
	return toupper(cmd);
}

//------------------------------------------------------------------------------
// - executes passed command
// - returns false on quit or crash, true otherwise
//------------------------------------------------------------------------------
bool doHeloCommand(char cmd)
{
	switch (cmd)
	{
	case CMD_ASCEND:    heloUp(); return true;
	case CMD_DESCEND:   return heloDown();
	case CMD_FORWARD:   heloForward(); return true;
	case CMD_LAND:      heloLand(); return true;
	case CMD_QUIT:      return false;
	}

	std::cout << COLOR_FG_YELLOW 
		<< "Sorry, I don't know that command.\n"
		<< COLOR_RESET;

	return true;
}

//------------------------------------------------------------------------------
// goes up
//------------------------------------------------------------------------------
void heloUp()
{
	// OO design tip

	// traditional getter/setter calls to change altitude:

	//int alt = fly::helo.getAltitude();
	//fly::helo.setAltitude(alt + ALTITUDE_GAIN);

	// Helicopter's goUp() member function changes altitude with one call :-)
	fly::helo.goUp(ALTITUDE_GAIN);
}

//------------------------------------------------------------------------------
// - goes down
// - returns false on crash, true otherwise
//------------------------------------------------------------------------------
bool heloDown()
{
	if (!fly::helo.getAltitude())
	{
		std::cout << COLOR_FG_YELLOW
			<< "You're already on the ground!\n"
			<< COLOR_RESET;

		return true;
	}
	fly::helo.goDown(ALTITUDE_DROP);

	return (fly::helo.getAltitude() >= BUMPY_LANDING);
}

//------------------------------------------------------------------------------
// goes forward
//------------------------------------------------------------------------------
void heloForward()
{
	if (!fly::helo.getAltitude())
		std::cout << COLOR_FG_YELLOW
		<< "You're still on the ground!\n"
		<< COLOR_RESET;

	else
		fly::helo.goForward(DISTANCE_GAIN);
}

//------------------------------------------------------------------------------
// lands
//------------------------------------------------------------------------------
void heloLand()
{
	if (!fly::helo.inFlight())
		std::cout << COLOR_FG_YELLOW
		<< "You're already on the ground!\n"
		<< COLOR_RESET;

	else
	{
		fly::helo.goLand();
		std::cout << "Nice landing!\n";
	}
}

//------------------------------------------------------------------------------
// - terminates flight
// - forces crash if helicopter is in the air
//------------------------------------------------------------------------------
void heloQuit()
{
	int altitude = fly::helo.getAltitude();

	if (altitude > 0)
		fly::helo.goDown(altitude - BUMPY_LANDING + 1);
}

//------------------------------------------------------------------------------
// - displays helicopter status and distance flown
//------------------------------------------------------------------------------
void displayStatus(bool keepFlying)
{
	int altitude = fly::helo.getAltitude();

	if (!keepFlying && altitude > 0)
	{
		std::cout << COLOR_FG_RED
			<< "You parachuted out and your helo crashed!\n"
			<< COLOR_RESET;

		// display correct altitude below
		altitude = -altitude;
	}
	else if (!keepFlying && altitude < BUMPY_LANDING)
	{
		std::cout << COLOR_FG_RED
			<< "You crashed!\n"
			<< COLOR_RESET;
	}
	else if (altitude < 0)
	{
		std::cout << COLOR_FG_YELLOW
			<< "Whoa! Bumpy landing!\n"
			<< COLOR_RESET;

		// this counts as a landing
		fly::helo.goLand();
	}

	std::cout << "Altitude: " << altitude << " feet\n";
	std::cout << "Distance flown since liftoff: " 
		<< fly::helo.getDistance() << " yards.\n";
	std::cout << "Total distance flown: " << fly::helo.getTotalDistance() << " yards.\n";
	std::cout << "Flight segments completed: " << fly::helo.getLegsFlown() << "\n\n";
}
