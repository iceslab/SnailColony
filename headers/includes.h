/*
 * includes.h
 *
 *  Created on: 9 maj 2016
 *      Author: user
 */

#ifndef HEADERS_INCLUDES_H_
#define HEADERS_INCLUDES_H_


#include <pthread.h>
#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

enum ColorPair
{
	DEFAULT = 0,
	GREEN,
	BROWN,

	RED,
	BLUE,
	MAGENTA,
	CYAN,
	BLACK,
	WHITE,

	FIRST_SNAIL_COLOR = RED,
	LAST_SNAIL_COLOR = WHITE

};

enum SnailState
{
	DEAD,
	ALIVE,
	HIDDEN
};

inline string snailStateToString(SnailState state)
{
	string stateString = "";
	switch(state)
	{
		case DEAD:
			stateString = "DEAD";
			break;
		case ALIVE:
			stateString = "ALIVE";
			break;
		case HIDDEN:
			stateString = "HIDDEN";
			break;
		default:
			break;
	}

	return stateString;
}

#endif /* HEADERS_INCLUDES_H_ */
