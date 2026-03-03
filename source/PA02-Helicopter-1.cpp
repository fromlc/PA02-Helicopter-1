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
// constants
//------------------------------------------------------------------------------
constexpr int ALTITUDE_GAIN = 100;
constexpr int ALTITUDE_DROP = 51;
constexpr int DISTANCE_GAIN = 200;

const std::string APP_MENU =
    "A)scend, D)escend, F)orward, V)land, Q)uit ? ";
const std::string HELO_NAME = "Huey";

constexpr char CMD_ASCEND   = 'A';
constexpr char CMD_DESCEND  = 'D';
constexpr char CMD_FORWARD  = 'F';
constexpr char CMD_LAND     = 'V';
constexpr char CMD_QUIT     = 'Q';

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------
namespace fly
{
    Helicopter helo;
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

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() 
{
    initFlight();

    while (!fly::quit)
    {
        doHeloCommand(getPilotCommand());
        displayStatus();
    }
    std::cout << "Goodbye!\n\n";
}

//------------------------------------------------------------------------------
// displays pilot instructions, initial status
//------------------------------------------------------------------------------
void initFlight() 
{
    //#TODO make name random
    fly::helo.setName(HELO_NAME);

    std::cout << "\nWelcome! You're flying a " 
        << fly::helo.getName() << " today.";
    std::cout << "\nYour flight simulation awaits.\n";
    std::cout << "\nControl your flight with these commands:\n\n";
    std::cout << "'" << CMD_ASCEND << "' increases altitude by " 
        << ALTITUDE_GAIN << " feet,\n";
    std::cout << "'" << CMD_DESCEND << "' decreases altitude by "
        << ALTITUDE_DROP << " feet,\n";
    std::cout << "'" << CMD_FORWARD << "' flies forward "
        << DISTANCE_GAIN << " yards.\n";
    std::cout << "'" << CMD_LAND << "' lands and your " 
        << fly::helo.getName() << " can take off again.\n";
    std::cout << "'" << CMD_QUIT << "' quits when you're done flying.\n\n";

    std::cout << "Commands can be in upper or lower case.\n\n";

    std::cout << "If you drop too much altitude or quit in midair, ";
    std::cout << "your " << fly::helo.getName() << " will crash!\n\n";

    std::cout << "Starting " << fly::helo.getName() << " flight simulation.\n";
    displayStatus();
}

//------------------------------------------------------------------------------
// - puts user command in reference param
// - returns false on quit command, true otherwise
//------------------------------------------------------------------------------
char getPilotCommand() 
{
    std::cout << APP_MENU;

    char cmd;
    std::cin >> cmd;
    return toupper(cmd);
}

//------------------------------------------------------------------------------
// - executes passed command
// - returns command result: true on success, false on fail
//------------------------------------------------------------------------------
void doHeloCommand(char cmd) 
{
    switch (cmd) 
    {
    case CMD_ASCEND:    heloUp(); break;
    case CMD_DESCEND:   heloDown(); break;
    case CMD_FORWARD:   heloForward(); break;
    case CMD_LAND:      heloLand(); break;
    case CMD_QUIT:      quitFlight(); break;
    default:            std::cout << "Sorry, I don't know that command.\n";
    }
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

    // for correct status output
    fly::leftGround = true;
}

//------------------------------------------------------------------------------
// goes down
//------------------------------------------------------------------------------
void heloDown() 
{
    if (!fly::helo.getAltitude()) 
        std::cout << "You're already on the ground!\n";

    else
        fly::helo.goDown(ALTITUDE_DROP);
}

//------------------------------------------------------------------------------
// goes forward
//------------------------------------------------------------------------------
void heloForward() 
{
    if (!fly::helo.getAltitude()) 
        std::cout << "You're still on the ground!\n";

    else
        fly::helo.goForward(DISTANCE_GAIN);
}

//------------------------------------------------------------------------------
// lands
//------------------------------------------------------------------------------
void heloLand() 
{
    if (!fly::helo.getAltitude()) 
        std::cout << "You're already on the ground!\n";

    else
    {
        fly::helo.goLand();
        std::cout << "Nice landing!\n";
        fly::leftGround = false;
    }
}

//------------------------------------------------------------------------------
// terminates flight with crash
//------------------------------------------------------------------------------
void quitFlight() 
{
    int altitude = fly::helo.getAltitude();
    
    // force a crash if helicopter is in the air
    if (altitude > 0)
    {
        fly::quit = true;
        fly::helo.goDown(altitude + 1);
    }
    fly::quit = true;
}

//------------------------------------------------------------------------------
// - displays helicopter status and distance flown
// - if helicopter has landed, reset distance flown to 0
//------------------------------------------------------------------------------
void displayStatus()
{
    int altitude = fly::helo.getAltitude();

    if (altitude < 0)
    {
        if (fly::quit)
            std::cout << "You parachuted out and your helo crashed!\n";
        else
        {
            std::cout << "You crashed!\n";
            fly::quit = true;
        }
    }
    
    std::cout << "Altitude: " << altitude << " feet\n";
    std::cout << "Distance flown: " << fly::helo.getDistance() << " yards.\n\n";

    if (!fly::leftGround)
        fly::helo.resetDistance();
}
