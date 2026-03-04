//-----------------------------------------------------------
// colors.h
//
// ANSI escape codes for console text and background colors
//-----------------------------------------------------------
#pragma once

// 8: ANSI escape sequences for 8 foreground colors and 8 for background colors
#define COLOR_COUNT			8

// ANSI escape sequences for console text foreground colors
#define COLOR_BLACK_1		1
#define COLOR_RED_2			2
#define COLOR_GREEN_3		3
#define COLOR_YELLOW_4		4
#define COLOR_BLUE_5		5
#define COLOR_MAGENTA_6		6
#define COLOR_CYAN_7		7
#define COLOR_WHITE_8		8

// ANSI escape sequences for console text foreground colors
#define COLOR_FG_BLACK		"\u001b[30m"
#define COLOR_FG_RED		"\u001b[31m"
#define COLOR_FG_GREEN		"\u001b[32m"
#define COLOR_FG_YELLOW		"\u001b[33m"
#define COLOR_FG_BLUE		"\u001b[34m"
#define COLOR_FG_MAGENTA	"\u001b[35m"
#define COLOR_FG_CYAN		"\u001b[36m"
#define COLOR_FG_WHITE		"\u001b[37m"

// ANSI escape sequences for console text background colors
#define COLOR_BG_BLACK		"\u001b[40m"
#define COLOR_BG_RED		"\u001b[41m"
#define COLOR_BG_GREEN		"\u001b[42m"
#define COLOR_BG_YELLOW		"\u001b[43m"
#define COLOR_BG_BLUE		"\u001b[44m"
#define COLOR_BG_MAGENTA	"\u001b[45m"
#define COLOR_BG_CYAN		"\u001b[46m"
#define COLOR_BG_WHITE		"\u001b[47m"

// ANSI escape sequence for setting default console text foreground and background colors
#define COLOR_RESET			"\u001b[0m"

