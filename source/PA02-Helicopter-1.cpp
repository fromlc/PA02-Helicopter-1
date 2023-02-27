//------------------------------------------------------------------------------
// PA02-Helicopter-1.cpp : app code for helicopter flight
// 
// Accepts commands U)p, D)own, F)orward, X)lands, Q)uit
//      - Up increases altitude by 100 feet
//      - Down decreases altitude by 101 feet
//      - Forward increases distance flown by 100 feet
//      - Land resets altitude to 0
//      - Quit terminates app
//------------------------------------------------------------------------------

#include "Helicopter.h"

#include <iostream>

//------------------------------------------------------------------------------
// using symbols
//------------------------------------------------------------------------------
using std::cin;
using std::cout;
using std::string;

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
constexpr int ALTITUDE_GAIN = 100;
constexpr int ALTITUDE_DROP = 101;
constexpr int DISTANCE_GAIN = 100;
constexpr int BUMPY_LANDING = -3;

const string APP_MENU = "U)p, D)own, F)orward, X)lands, Q)uit ? ";
const char CMD_UP = 'U';
const char CMD_DOWN = 'D';
const char CMD_FORWARD = 'F';
const char CMD_LAND = 'X';
const char CMD_QUIT = 'Q';

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------
namespace flight {
    Helicopter helo;
    bool crashed = false;
    bool leftGround = false;
    bool quit = false;
}

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
void initFlight();
char getPilotCommand();
void doHeloCommand(char);
void heloUp();
void heloDown();
void heloForward();
void heloLand();
void quitFlight();
void displayStatus();
bool heloCrashed(int);

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {
    initFlight();

    do {
        char cmd = getPilotCommand();
        doHeloCommand(cmd);
        displayStatus();
    } while (!flight::crashed && !flight::quit);

    cout << "\nGoodbye!\n\n";
}

//------------------------------------------------------------------------------
// displays pilot instructions, initial status
//------------------------------------------------------------------------------
void initFlight() {

    cout << "\nWelcome, helo pilot! Your Huey awaits your commands.\n\n";
    cout << "U)p increases altitude by " << ALTITUDE_GAIN << " feet,\n";
    cout << "D)own decreases altitude by " << ALTITUDE_DROP << " feet,\n";
    cout << "F)orward flies " << DISTANCE_GAIN << " yards.\n";
    cout << "X)lands sets altitude to 0 but your Huey can fly again.\n";
    cout << "Q)uit when you're done flying.\n\n";

    cout << "Commands can be upper or lower case.\n\n";

    cout << "If you drop too much altitude or Q)uit in midair, ";
    cout << "your Huey may crash!\n\n";

    cout << "Starting simulation. ";
    displayStatus();
}

//------------------------------------------------------------------------------
// - puts user command in reference param
// - returns false on quit command, true otherwise
//------------------------------------------------------------------------------
char getPilotCommand() {
    cout << "U)p, D)own, F)orward, X)lands, Q)uit ? ";

    char cmd;
    cin >> cmd;
    return toupper(cmd);
}

//------------------------------------------------------------------------------
// - executes passed command
// - returns command result: true on success, false on fail
//------------------------------------------------------------------------------
void doHeloCommand(char cmd) {
    switch (cmd) {
    case CMD_UP:        heloUp(); break;
    case CMD_DOWN:      heloDown(); break;
    case CMD_FORWARD:   heloForward(); break;
    case CMD_LAND:      heloLand(); break;
    case CMD_QUIT:      quitFlight(); break;
    }
}

//------------------------------------------------------------------------------
// goes up
//------------------------------------------------------------------------------
void heloUp() {
    flight::helo.goUp(ALTITUDE_GAIN);
}

//------------------------------------------------------------------------------
// goes down
//------------------------------------------------------------------------------
void heloDown() {
    if (!flight::helo.getAltitude()) {
        cout << "You're already on the ground! ";
        flight::leftGround = false;
    }
    flight::helo.goDown(ALTITUDE_DROP);
}

//------------------------------------------------------------------------------
// goes forward
//------------------------------------------------------------------------------
void heloForward() {
    if (!flight::helo.getAltitude()) {
        cout << "You're still on the ground. ";
    }
    else {
        flight::helo.goForward(DISTANCE_GAIN);
    }
}

//------------------------------------------------------------------------------
// lands
//------------------------------------------------------------------------------
void heloLand() {
    if (!flight::helo.getAltitude()) {
        cout << "You're already on the ground! ";
    }
    else {
        flight::helo.goLand();
    }
}

//------------------------------------------------------------------------------
// terminates flight with bumpy landing or crash
//------------------------------------------------------------------------------
void quitFlight() {
    int altitude = flight::helo.getAltitude();
 
    int drop = altitude / ALTITUDE_GAIN * ALTITUDE_DROP;
    flight::helo.goDown(drop);

    flight::quit = true;
}

//------------------------------------------------------------------------------
// displays helicopter status and position 
//------------------------------------------------------------------------------
void displayStatus() {
    int altitude, distance;
    flight::helo.getPosition(altitude, distance);

    if (!heloCrashed(altitude)) {
        altitude = flight::helo.getAltitude();
        if (flight::leftGround && !altitude) {
            cout << "Nice landing ;)";
            flight::leftGround = false;
        }
        else {
            cout << "Altitude is " << altitude << " feet,";
        }
    }
    cout << " Distance flown is " << distance << " yards.\n\n";
}

//------------------------------------------------------------------------------
// - handles crash conditions
// - updates helo altitude
// - returns true if helo crashed, false otherwise
//------------------------------------------------------------------------------
bool heloCrashed(int altitude) {

    if (altitude < 0) {
        if (altitude >= BUMPY_LANDING) {
            cout << "Bumpy landing! ";
            flight::helo.goLand();
            flight::crashed = false;
        }
        else {
            cout << "You crashed! ";
            flight::crashed = true;
        }

        cout << "You dropped " << abs(altitude) << " feet too many. ";
    }
    return flight::crashed;
}