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

const string APP_MENU = "U)p, D)own, F)orward, X)lands, Q)uit ? ";
const char CMD_UP = 'U';
const char CMD_DOWN = 'D';
const char CMD_FORWARD = 'F';
const char CMD_LAND = 'X';
const char CMD_QUIT = 'Q';

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------
Helicopter g_helo;
bool g_crashed = false;

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
bool getHeloCommand(char&);
bool doHeloCommand(char);
bool heloUp();
bool heloDown();
bool heloForward();
bool heloLand();
void displayStatus();

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {

    cout << "\nWelcome, helo pilot! Your Huey awaits your commands.\n\n";
    cout << "Up increases altitude by " << ALTITUDE_GAIN << " feet,\n";
    cout << "Down decreases altitude by " << ALTITUDE_DROP << " feet,\n";
    cout << "Forward flies " << DISTANCE_GAIN << " yards.\n\n";

    char cmd;   // user command

    while (!g_crashed && getHeloCommand(cmd)) {
        doHeloCommand(cmd);
        displayStatus();
    }

    cout << "\nGoodbye!\n\n";
}

//------------------------------------------------------------------------------
// - puts user command in reference param
// - returns false on quit command, true otherwise
//------------------------------------------------------------------------------
bool getHeloCommand(char& cmd) {

    cout << "U)p, D)own, F)orward, X)lands, Q)uit ? ";
    cin >> cmd;
    cmd = toupper(cmd);

    return (cmd == CMD_QUIT) ? false : true;
}

//------------------------------------------------------------------------------
// - executes passed command
// - returns command result: true on success, false on fail
//------------------------------------------------------------------------------
bool doHeloCommand(char cmd) {
    switch (cmd) {
    case CMD_UP:        return heloUp();
    case CMD_DOWN:      return heloDown();
    case CMD_FORWARD:   return heloForward();
    case CMD_LAND:      return heloLand();
    }

    return true;
}

//------------------------------------------------------------------------------
// goes up
//------------------------------------------------------------------------------
bool heloUp() { 
    g_helo.goUp(ALTITUDE_GAIN);
    return true;
}

//------------------------------------------------------------------------------
// goes down
//------------------------------------------------------------------------------
bool heloDown() {
    if (!g_helo.getAltitude()) {
        cout << "You're already on the ground! ";
        return true;
    }
    if (g_helo.goDown(ALTITUDE_DROP) > 0) {
        return true;
    }
    g_crashed = true;
    return false;
}

//------------------------------------------------------------------------------
// goes forward
//------------------------------------------------------------------------------
bool heloForward() { 
    if (!g_helo.getAltitude()) {
        cout << "You're still on the ground. ";
        return false;
    }

    g_helo.goForward(DISTANCE_GAIN); 
    return true;  
}

//------------------------------------------------------------------------------
// lands
//------------------------------------------------------------------------------
bool heloLand() {
    if (!g_helo.getAltitude()) {
        cout << "You're already on the ground! ";
    }
    else {
        g_helo.goLand();
    }
    return true;
}

//------------------------------------------------------------------------------
// displays helicopter status and position 
//------------------------------------------------------------------------------
void displayStatus() {
    int altitude, distance;
    g_helo.getPosition(altitude, distance);

    if (altitude < 0) {
        cout << "You crashed!";
    }
    else if (altitude == 0) {
        cout << "Nice landing ;)";
    }
    else {
        cout << "Altitude is " << altitude << " feet,";
    }
    cout << " Distance flown is " << distance << " yards.\n\n";
}
