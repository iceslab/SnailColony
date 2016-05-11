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


#endif /* HEADERS_INCLUDES_H_ */
