/*
 * CommonUtils.cpp
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */
#include "../headers/CommonUtils.h"

const int CommonUtils::statusBarHeight = 10;

bool CommonUtils::initLibrary()
{
	bool retVal = false;
	srand(time(nullptr));

	if(NULL != initscr())
	{
		retVal = initColors();
		cbreak();
		refresh();
	}

	return retVal;
}

bool CommonUtils::initWindows(Map* &map, StatusBar* &statusBar)
{
	bool retVal = false;

	wborder(stdscr, '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0');
	refresh();

	int height = 0, width = 0;
	int lines = 0, columns = 0;
	int startY = 1, startX = 1;

	getmaxyx(stdscr, lines, columns);

	width = columns - 2;
	if(width > 0)
	{
		height = lines - 2 - statusBarHeight;

		if(height > 0)
		{
			map = new Map(height, width, startX, startY);
			refresh();

			startY += height;
			height = statusBarHeight;

			statusBar = new StatusBar(height, width, startX, startY);
			refresh();

			retVal = true;
		}
	}

	return retVal;
}

bool CommonUtils::initColors()
{
	bool retVal = false;

	if(has_colors() == TRUE)
	{
		start_color();
		init_pair(GREEN, COLOR_BLACK, COLOR_GREEN);
		init_pair(BROWN, COLOR_BLACK, COLOR_YELLOW);
		init_pair(RED, COLOR_BLACK, COLOR_RED);
		init_pair(BLUE, COLOR_BLACK, COLOR_BLUE);
		init_pair(MAGENTA, COLOR_BLACK, COLOR_MAGENTA);
		init_pair(CYAN, COLOR_BLACK, COLOR_CYAN);
		init_pair(BLACK, COLOR_WHITE, COLOR_BLACK);
		init_pair(WHITE, COLOR_BLACK, COLOR_WHITE);
		retVal = true;
	}

	return retVal;
}



